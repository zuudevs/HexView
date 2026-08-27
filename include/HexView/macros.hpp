#pragma once

#ifndef NDEBUG
    #define NOEXCEPT
#else
    #define NOEXCEPT noexcept
#endif

#if defined(__cpp_lib_print) && __cpp_lib_print >= 202207L
	#include <print>

    #define PRINT(...) std::print(__VA_ARGS__)
    #define PRINTLN(...) std::println(__VA_ARGS__)
#else
    #include <fmt/core.h>
	
    #define PRINT(...)   fmt::print(__VA_ARGS__)
    #define PRINTLN(...) fmt::println(__VA_ARGS__)
#endif