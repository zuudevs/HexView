#include <HexView/hex_view.hpp>
#ifndef NDEBUG
	#ifdef __GNUC__
		#include <fmt/core.h>
		#include <fmt/std.h>
	#else
		#include <print>
	#endif
#endif

namespace zhv = zuu::hexview;

int
    main(int argc, char* argv[]) {
#ifndef NDEBUG
    std::println(stderr, "[{}] args size: {}", __FILE__, argc);
    std::println(stderr, "args:");
    for (auto i = 0; i < argc; i++) {
        std::println(stderr, "{:>2}. {}", (i + 1), argv[i]);
    }
    std::println(stderr);
#endif
    zhv::HexView hv;
    hv.exec(std::span(argv, argv + argc));

    return 0;
}