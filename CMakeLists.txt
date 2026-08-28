cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "HexView")
set(PROJECT_VERSION 1.0.0)
set(PROJECT_DESCRIPTION "Custom Hex Viewer implementation using C++. Developed as part of an exploration of low-level programming to analyze byte streams and binary structures of various file formats.")
set(PROJECT_AUTHOR "zuudevs")
set(PROJECT_REPOSITORY_URL "https://github.com/${PROJECT_AUTHOR}/${PROJECT_NAME}.git")

include("cmake/tools/vcpkg.cmake")

project(
	${PROJECT_NAME}
	VERSION ${PROJECT_VERSION}
	DESCRIPTION ${PROJECT_DESCRIPTION}
	LANGUAGES CXX
)

include("cmake/modules/config.cmake")
include("cmake/modules/options.cmake")

add_subdirectory(${CMAKE_SOURCE_DIR}/cmake/templates)
add_subdirectory(${CMAKE_SOURCE_DIR}/src)

if(ENABLE_CLANG_TIDY)
	include(cmake/tools/clang-tidy.cmake)
endif()

if(ENABLE_CLANG_FORMAT)
	include(cmake/tools/clang-format.cmake)
endif()

if(ENABLE_TEST)
	include("cmake/modules/testing.cmake")
	add_subdirectory(${CMAKE_SOURCE_DIR}/tests)
endif()

if(ENABLE_BENCHMARK)
	include("cmake/modules/benchmark.cmake")
	add_subdirectory(${CMAKE_SOURCE_DIR}/benchmarks)
endif()

message("Project Name: ${PROJECT_NAME}")
message("Project Version: ${PROJECT_VERSION}")
message("C++ Standard: ${CMAKE_CXX_STANDARD}")
message("Build Type: ${CMAKE_BUILD_TYPE}")
