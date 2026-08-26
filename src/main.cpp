#include <hex_view.hpp>

namespace zhv = zuu::hexview;

int main(int argc, char* argv[]) {
	zhv::HexView hv;
	hv.exec(std::span(argv, argv + argc));

	return 0;
}