add_test_target(error_test
	${CMAKE_CURRENT_SOURCE_DIR}/unit/error_test.cpp
)

add_test_target(file_stream_test
	${CMAKE_CURRENT_SOURCE_DIR}/unit/file_stream_test.cpp
)

add_test_target(hex_view_test
	${CMAKE_CURRENT_SOURCE_DIR}/unit/hex_view_test.cpp
)

add_test_target(commands_test
	${CMAKE_CURRENT_SOURCE_DIR}/unit/commands_test.cpp
)

add_custom_target(unit_tests)
add_dependencies(unit_tests
	error_test
	file_stream_test
	hex_view_test
	commands_test
)