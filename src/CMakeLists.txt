add_library(core
	${CMAKE_CURRENT_SOURCE_DIR}/file_stream.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/hex_view.cpp
	${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

add_library(${PROJECT_NAME}::${PROJECT_NAME} ALIAS core)

target_include_directories(core
	PUBLIC
		${CMAKE_SOURCE_DIR}/include
	PRIVATE
		${CMAKE_SOURCE_DIR}/internal
)