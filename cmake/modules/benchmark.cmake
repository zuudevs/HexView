if(ENABLE_BENCHMARK)
	include(${CMAKE_SOURCE_DIR}/cmake/third_party/google-benchmark.cmake)
endif()
	
function(add_benchmark_target name)
	if(ENABLE_BENCHMARK)
		add_executable(${name} ${ARGN})
		target_link_libraries(${name} 
			PRIVATE 
				benchmark::benchmark_main
				${PROJECT_NAME}::core
		)
        # Exclude benchmark from default build in Debug configurations
        set_target_properties(${name} PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD_Debug 1)
        
        # Only add to CTest if not in Debug configuration
        add_test(NAME Benchmark.${name} 
                 COMMAND ${name}
                 CONFIGURATIONS Release RelWithDebInfo MinSizeRel)
	endif()
endfunction()