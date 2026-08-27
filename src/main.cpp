#include <HexView/hex_view.hpp>

namespace zhv = zuu::hexview;

int
    main(int argc, char* argv[]) {
#ifndef NDEBUG
    PRINTLN_ERROR("[{}] args size: {}", __FILE__, argc);
    PRINTLN_ERROR("args:");
    for (auto i = 0; i < argc; i++) {
        PRINTLN_ERROR("{:>2}. {}", (i + 1), argv[i]);
    }
    PRINTLN();
#endif
    zhv::HexView hv;
    hv.exec(std::span(argv, argv + argc));

    return 0;
}