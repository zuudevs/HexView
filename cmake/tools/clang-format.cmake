find_program(CLANG_FORMAT_EXE NAMES clang-format)

if(CLANG_FORMAT_EXE)
	function(add_clang_format_target target)
		get_target_property(TARGET_SOURCES ${target} SOURCES)

		add_custom_target(format
			COMMAND ${CLANG_FORMAT_EXE} -i -style=file ${TARGET_SOURCES}
			COMMENT "Formatting ${target} source files with clang-format"
		)

		add_custom_target(format-check
			COMMAND ${CLANG_FORMAT_EXE} --dry-run --Werror -style=file ${TARGET_SOURCES}
			COMMENT "Checking ${target} source formatting"
		)
	endfunction()
endif()