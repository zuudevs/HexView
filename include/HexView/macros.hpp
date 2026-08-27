#pragma once

#ifndef NDEBUG
    #define NOEXCEPT
#else
    #define NOEXCEPT noexcept
#endif

#if defined(__cpp_lib_print) && __cpp_lib_print >= 202207L
	#include <print>

    #define PRINT(...) std::print(stdout, __VA_ARGS__)
    #define PRINTLN(...) std::println(stdout, __VA_ARGS__)
    #define PRINT_ERROR(...) std::print(stderr, __VA_ARGS__)
    #define PRINTLN_ERROR(...) std::println(stderr, __VA_ARGS__)
#else
    #include <fmt/core.h>

    #define PRINT(...) fmt::print(stdout, __VA_ARGS__)
    #define PRINTLN(...) fmt::println(stdout, __VA_ARGS__)
    #define PRINT_ERROR(...) fmt::print(stderr, __VA_ARGS__)
    #define PRINTLN_ERROR(...) fmt::println(stderr, __VA_ARGS__)
#endif