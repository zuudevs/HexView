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
	#define PRINTLN(...) fmt::println(__VA_ARGS__)
#else
	#include <print>

	#define PRINT(...) std::print(__VA_ARGS__)
	#define PRINTLN(...) std::println(__VA_ARGS__)
#endif