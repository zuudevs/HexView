#pragma once

#ifndef NDEBUG
    #define NOEXCEPT
#else
    #define NOEXCEPT noexcept
#endif

#ifdef __GNUC__
    #include <fmt/core.h>
    #include <fmt/std.h>

    #define PRINT(...) fmt::print(__VA_ARGS__)
    #define PRINTLN(...) _FMT_PRINTLN_SELECT(__VA_ARGS__)(__VA_ARGS__)
	
    #define _FMT_PRINTLN_SELECT(...) _FMT_CHOOSER(__VA_ARGS__, _FMT_PLN_MANY, _FMT_PLN_MANY, _FMT_PLN_ONE, _FMT_PLN_ZERO)
    #define _FMT_CHOOSER(_1, _2, _3, N, ...) N

    #define _FMT_PLN_ZERO()       fmt::print("\n")
    #define _FMT_PLN_ONE(arg)     _FMT_HANDLE_ONE(arg)
    #define _FMT_PLN_MANY(fmt, ...) fmt::println(fmt, __VA_ARGS__)

    #inline helper atau makro penanganan tunggal:
    #define _FMT_HANDLE_ONE(arg) \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wpointer-arith\"") \
        _Generic(&(arg), \
            FILE**                : fmt::print(arg, "\n"), \
            std::ostream*         : fmt::print(arg, "\n"), \
            default               : fmt::println("{}", arg) \
        ) \
        _Pragma("GCC diagnostic pop")

#else
    #include <print>

    #define PRINT(...) std::print(__VA_ARGS__)
    #define PRINTLN(...) std::println(__VA_ARGS__)
#endif