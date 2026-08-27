add_test_target(error_test
	${CMAKE_CURRENT_SOURCE_DIR}/unit/error/main.cpp
)

add_custom_target(unit_tests)
add_dependencies(unit_tests
	error_test
)