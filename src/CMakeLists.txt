file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS "*.cpp")

add_library(core ${SRCS})

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS core)

target_include_directories(core
	PUBLIC
		${CMAKE_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_SOURCE_DIR}/internal
)