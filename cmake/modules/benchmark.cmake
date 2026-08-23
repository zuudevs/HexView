if(ENABLE_BENCHMARK)
	include(${CMAKE_SOURCE_DIR}/cmake/third_party/google-benchmark.cmake)
endif()
	
function(add_benchmark_target name)
	if(ENABLE_BENCHMARK)
		add_executable(${name} ${ARGN})
		target_link_libraries(${name} 
			PRIVATE 
				benchmark::benchmark_main
				${PROJECT_NAME}::${PROJECT_NAME}
		)
	endif()
endfunction()