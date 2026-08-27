if(ENABLE_TEST)
	include("${CMAKE_SOURCE_DIR}/cmake/third_party/google-test.cmake")
endif()

function(add_test_target name)
	if(ENABLE_TEST)
		add_executable(${name} ${ARGN})
		target_link_libraries(${name} 
			PRIVATE 
				GTest::gtest_main
				${PROJECT_NAME}::core
		)
		target_include_directories(${name} PRIVATE "${CMAKE_SOURCE_DIR}/internal")
		gtest_discover_tests(${name})
	endif()
endfunction()