# Generate a dummy binary file to be read by the hexview executable during tests
set(DUMMY_FILE "${CMAKE_CURRENT_BINARY_DIR}/integration_dummy.bin")
file(WRITE ${DUMMY_FILE} "Integration Test Data 12345")

# Helper macro to quickly define integration tests
macro(add_integration_test name expected_regex)
    add_test(NAME Integration.${name} COMMAND hexview ${ARGN})
    set_tests_properties(Integration.${name} PROPERTIES PASS_REGULAR_EXPRESSION "${expected_regex}")
endmacro()

# --- Test Cases ---

# 1. Basic Commands
add_integration_test(Help "HexView - A Modern C.. Hexadecimal File Viewer" --help)
add_integration_test(HelpShort "HexView - A Modern C.. Hexadecimal File Viewer" -h)
add_integration_test(Version "Version" --version)

# 2. Syntax & Error Handling
add_integration_test(EmptyArgs "HexView - A Modern C.. Hexadecimal File Viewer" )
add_integration_test(InvalidCommand "Error: Invalid command-line syntax" --not_a_cmd)
add_integration_test(ShowMissingFile "Error: File path is required" --show)
add_integration_test(ShowFileNotFound "Error: Path does not exist" --show non_existent_file.bin)
add_integration_test(DuplicateFlags "Error: Invalid command-line syntax" --show "${DUMMY_FILE}" --offset --offset)

# 3. Functional Data Output
# Tests reading the dummy file. 'I' 'n' 't' 'e' 'g' 'r' 'a' 't' 'i' 'o' 'n' translates to Hex: 49 6E 74 65 67 72 61 74 69 6F 6E
add_integration_test(ShowValidFile "49 6E 74 65 67 72 61 74" --show "${DUMMY_FILE}")

# 4. Functional Output Formatting (Flags)
# Checks if the '--offset' and '--ascii' flags correctly render the columns in the output
add_integration_test(ShowValidFileFlags "offset .* ascii" --show "${DUMMY_FILE}" --offset --ascii)
add_integration_test(CustomLength "---" --show "${DUMMY_FILE}" --length 16)
