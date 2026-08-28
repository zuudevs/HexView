cmake_minimum_required(VERSION 3.20)

set(PROJECT_NAME "HexView")
set(PROJECT_VERSION 0.6.0)
set(PROJECT_DESCRIPTION "Implementasi Hex Viewer kustom menggunakan C++. Dikembangkan sebagai bagian dari eksplorasi pemrograman tingkat rendah untuk menganalisis byte stream dan struktur biner dari berbagai format file.")
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