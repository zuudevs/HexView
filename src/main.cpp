#include <HexView/hex_view.hpp>

namespace zhv = zuu::hexview;

int
    main(int argc, char* argv[]) {
#ifndef NDEBUG
    PRINTLN(stderr, "[{}] args size: {}", __FILE__, argc);
    PRINTLN(stderr, "args:");
    for (auto i = 0; i < argc; i++) {
        PRINTLN(stderr, "{:>2}. {}", (i + 1), argv[i]);
    }
    PRINTLN(stderr);
#endif
    zhv::HexView hv;
    hv.exec(std::span(argv, argv + argc));

    return 0;
}