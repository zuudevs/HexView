find_package(fmt CONFIG REQUIRED)

if(NOT fmt_FOUND)
	include(FetchContent)
	FetchContent_Declare(
		fmt
		GIT_REPOSITORY https://github.com/fmtlib/fmt.git
		GIT_TAG        12.2.0
	)
	FetchContent_MakeAvailable(fmt)
endif()