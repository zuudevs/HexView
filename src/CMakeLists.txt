add_library(core
    ${CMAKE_CURRENT_SOURCE_DIR}/file_stream.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/hex_view.cpp
)

add_library(${PROJECT_NAME}::core ALIAS core)

target_include_directories(core
    PUBLIC
        "${CMAKE_SOURCE_DIR}/include"
    PRIVATE
        "${CMAKE_SOURCE_DIR}/internal"
)

add_executable(hexview
     ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

target_link_libraries(hexview
    PRIVATE
        ${PROJECT_NAME}::core
)