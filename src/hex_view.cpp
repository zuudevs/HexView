#include <HexView/error.hpp>
#include <HexView/version.hpp>

#include <cstdio>
#include <print>

#include <file_stream.hpp>
#include <view_config.hpp>
#include <view_task.hpp>

#include <HexView/hex_view.hpp>

namespace {

namespace zhv = zuu::hexview;

static inline zhv::ViewTask vw_task;

} // namespace

namespace zuu::hexview {

HexView::HexView() NOEXCEPT = default;

void HexView::printHelp() const NOEXCEPT {
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

void HexView::printVersion() const NOEXCEPT {
    std::println("HexView");
    std::println("--------------------");
    std::println("Version {}", version);
    std::println("Author {}", author);
    std::println("Source {}", repository_url);
}

void HexView::view() const NOEXCEPT {
	if ((vw_task.conf & ViewConfig::Offset) != ViewConfig::None) {
        std::print("{:<8} | ", "offset");
    }

    for (std::size_t i = 0; i < 8; ++i) {
        std::print("{:02X} ", i);
    }

    if ((vw_task.conf & ViewConfig::Ascii) != ViewConfig::None) {
        std::print("| ascii");
    }

    std::println();
	if ((vw_task.conf & ViewConfig::Offset) != ViewConfig::None) {
        std::print("----------");
    }
	std::print("-------------------------");
	if ((vw_task.conf & ViewConfig::Ascii) != ViewConfig::None) {
        std::print("-------");
    }
	std::println();

    FileStream fst;

    if (!fst.open(vw_task.filepath)) {
        return;
    }

    while (true) {
        const auto chunk = fst.getChunk();

        if (chunk.empty()) {
            break;
        }

        const auto row_offset = fst.getOffset();

        if ((vw_task.conf & ViewConfig::Offset) != ViewConfig::None) {
            std::print("{:08X} | ", row_offset);
        }

        for (const auto byte : chunk) {
            std::print("{:02X} ", static_cast<unsigned int>(byte));
        }

        for (std::size_t i = chunk.size(); i < 8; ++i) {
            std::print("   ");
        }

        if ((vw_task.conf & ViewConfig::Ascii) != ViewConfig::None) {
            std::print("| ");

            for (const auto byte : chunk) {
                const auto ch = static_cast<unsigned char>(byte);

                if (ch >= 0x20 && ch <= 0x7E) {
                    std::print("{}", static_cast<char>(ch));
                } else {
                    std::print(".");
                }
            }
        }

        std::println();
    }
}

void HexView::printError(Error errc) const NOEXCEPT {
	std::println(stderr, "Error: {}", ResolveError(errc));
}

void HexView::exec(std::span<char*> args) const NOEXCEPT {

#ifdef NDEBUG
	std::println(stderr, "[{}] args size: {}\n", __FILE_NAME__, args.size());
#endif

	if (args.size() < 2) {
		return printHelp();
	}

	auto pos = 1;

	if (args[pos] == std::string("--help") || args[pos] == std::string("-h")) {
		return printHelp();
	}

	if (args[pos] == std::string("--version") || args[pos] == std::string("-v")) {
		return printVersion();
	}

	ViewConfig vwconf{ViewConfig::Hex};

	if (args[pos] == std::string("--view") || args[pos] == std::string("-vw")) {
		pos++;
		while (pos < args.size()) {
			if (args[pos] == std::string("--offset")) {
				vwconf |= ViewConfig::Offset;
			} else if (args[pos] == std::string("--ascii")) {
				vwconf |= ViewConfig::Ascii;
			} else if (vw_task.filepath.empty()) {
				vw_task.filepath = args[pos];
			} else {
				return printError(Error::InvalidSyntax);
			}
			pos++;
		}

		vw_task.conf = vwconf;
		return view();
	}

	std::println(stderr, "Error: Command syntax is invalid\n");
	return printHelp();
}

} // namespace zuu::hexview