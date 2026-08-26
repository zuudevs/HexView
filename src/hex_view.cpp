#include <HexView/error.hpp>
#include <HexView/version.hpp>

#include <cstdio>
#include <print>

#include <file_stream.hpp>
#include <hex_view.hpp>
#include <view_config.hpp>
#include <view_task.hpp>

namespace zuu::hexview {

HexView::HexView() noexcept = default;

void HexView::printHelp() const noexcept {
    std::println("HexView - A Modern C++ Hexadecimal File Viewer");
    std::println("Usage:");
    std::println("  hexview [options] [command]");
    std::println("");
    std::println("Commands:");
    std::println("  -vw, --view <filepath> [options]    View the hexadecimal content of a file");
    std::println("");
    std::println("Options for --view:");
    std::println("  --offset                            Display byte offset column on the left");
    std::println("  --ascii                             Display ASCII representation column on the right");
    std::println("");
    std::println("General Options:");
    std::println("  -h, --help                          Display this help message and exit");
    std::println("  -v, --version                       Display version information and exit");
}

void HexView::printVersion() const noexcept {
    std::println("HexView");
    std::println("--------------------");
    std::println("Version {}", version);
    std::println("Author {}", author);
    std::println("Source {}", repository_url);
}

void HexView::view(ViewTask vwtask) const noexcept {
	if ((vwtask.conf & ViewConfig::Offset) != ViewConfig::None) {
		std::print("{:<8} | ", "offset");
	}

	for(auto i = 0; i < 8; i++) {
		std::print("{:<2} ", i);
	}

	std::print("| ");

	if ((vwtask.conf & ViewConfig::Ascii) != ViewConfig::None) {
		std::print("{:<8} | ", "ascii");
	}

	std::println("");

	FileStream fst;
	if (fst.open(vwtask.filepath)) {
		while (true) {
			auto chunk = fst.getChunk();

			if ((vwtask.conf & ViewConfig::Offset) != ViewConfig::None) {
				std::print("{:<8} | ", fst.getOffset());
			}

			for (const auto& b : chunk) {
				std::print("{:X}", b);
			}

			std::print(" | ");

			if ((vwtask.conf & ViewConfig::Offset) != ViewConfig::None) {
				for (const auto& ch : chunk) {
					std::print("{}", static_cast<char>(ch));
				}
			}

			std::println("|");
		}
	}
}

void HexView::printError(Error errc) const noexcept {
	std::println(stderr, "Error: {}", ResolveError(errc));
}

void HexView::exec(std::span<char*> args) const noexcept {
	if (args.size() < 2) {
		return printHelp();
	}

	auto pos = 2;

	if (args[pos] == "--help" || args[pos] == "-h") {
		return printHelp();
	}

	if (args[pos] == "--version" || args[pos] == "-v") {
		return printVersion();
	}

	ViewConfig vwconf{ViewConfig::Hex};
	ViewTask vwtask;

	if (args[pos] == "--view" || args[pos] == "-vw") {
		pos++;
		while (pos < args.size()) {
			if (args[pos] == "--offset") {
				vwconf |= ViewConfig::Offset;
			} else if (args[pos] == "--ascii") {
				vwconf |= ViewConfig::Ascii;
			} else if (vwtask.filepath.empty()) {
				vwtask.filepath = args[pos];
			} else {
				return printError(Error::InvalidSyntax);
			}
			pos++;
		}
	}

	vwtask.conf = vwconf;
	return view(vwtask);
}

} // namespace zuu::hexview