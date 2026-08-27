#include <HexView/error.hpp>
#include <HexView/version.hpp>

#include <charconv>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <print>
#include <span>
#include <string_view>

#include <commands.hpp>
#include <file_stream.hpp>

#ifndef NDEBUG
	#include <system_error>
#endif

#include <view_config.hpp>

#include <HexView/hex_view.hpp>

namespace {

using namespace zuu::hexview;

static inline ViewConfig vw_config{ViewConfig::Hex};
static inline std::string_view filepath;
static inline std::uint8_t bytes_per_line{8};

} // namespace

namespace zuu::hexview {

HexView::HexView() NOEXCEPT = default;

void
    HexView::printHelp() const NOEXCEPT {
    std::println("HexView - A Modern C++ Hexadecimal File Viewer");
    std::println("Usage:");
    std::println("  hexview [options] [command]");
    std::println("");
    std::println("Commands:");
    std::println("  -vw, --view <filepath> [options]    View the hexadecimal content of a file");
    std::println("");
    std::println("Options for --view:");
    std::println("  --offset                            Display byte offset column on the left");
    std::println(
        "  --ascii                             Display ASCII representation column on the right");
    std::println("");
    std::println("General Options:");
    std::println("  -h, --help                          Display this help message and exit");
    std::println("  -v, --version                       Display version information and exit");
}

void
    HexView::printVersion() const NOEXCEPT {
    std::println("HexView");
    std::println("--------------------");
    std::println("Version {}", version);
    std::println("Author {}", author);
    std::println("Source {}", repository_url);
}

void
    HexView::view() const NOEXCEPT {
    if ((vw_config & ViewConfig::Offset) != ViewConfig::None) {
        std::print("{:<8} | ", "offset");
    }

    for (std::size_t i = 0; i < bytes_per_line; ++i) {
        std::print("{:02X} ", i);
    }

    if ((vw_config & ViewConfig::Ascii) != ViewConfig::None) {
        std::print("| ascii");
    }

    std::println();
    if ((vw_config & ViewConfig::Offset) != ViewConfig::None) {
        std::print("----------");
    }

	if ((vw_config & ViewConfig::Length) != ViewConfig::None) {
		for (auto i = 0; i < bytes_per_line; ++i) {
			std::print("---");
		}
	} else {
		std::print("------------------------");
	}

    std::print("--");
    if ((vw_config & ViewConfig::Ascii) != ViewConfig::None) {
        std::print("-------");
    }
    std::println();

    FileStream fst;

    if (!fst.open(filepath)) {
        return;
    }

    while (true) {
        const auto chunk = fst.getChunk(bytes_per_line);

        if (chunk.empty()) {
            break;
        }

        const auto row_offset = fst.getOffset();

        if ((vw_config & ViewConfig::Offset) != ViewConfig::None) {
            std::print("{:08X} | ", row_offset);
        }

        for (const auto byte : chunk) {
            std::print("{:02X} ", static_cast<unsigned int>(byte));
        }

        for (std::size_t i = chunk.size(); i < bytes_per_line; ++i) {
            std::print("   ");
        }

        if ((vw_config & ViewConfig::Ascii) != ViewConfig::None) {
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

void
    HexView::printError(Error errc) const NOEXCEPT {
    std::println(stderr, "Error: {}", ResolveError(errc));
}

void
    HexView::exec(std::span<char*> args) const NOEXCEPT {
#ifndef NDEBUG
    std::println(stderr, "[{}] args size: {}\n", __FILE_NAME__, args.size());
#endif

    if (args.size() < 2) {
        return printHelp();
    }

    auto pos = 1;

    if (args[pos] == kCmdHelp || args[pos] == kCmdHelpAbrv) {
        return printHelp();
    }

    if (args[pos] == kCmdVersion || args[pos] == kCmdVersionAbrv) {
        return printVersion();
    }

    if (args[pos] == kCmdShow || args[pos] == kCmdShowAbrv) {
        pos++;
        while (pos < args.size()) {
            if (args[pos] == kCmdShowOptOffset && (vw_config & ViewConfig::Offset) == ViewConfig::None) {
                vw_config |= ViewConfig::Offset;
            } else if (args[pos] == kCmdShowOptAscii && (vw_config & ViewConfig::Ascii) == ViewConfig::None) {
                vw_config |= ViewConfig::Ascii;
            } else if (args[pos] == kCmdShowOptLength && (vw_config & ViewConfig::Length) == ViewConfig::None) {
				pos++;
				std::int64_t val{};
				auto str = std::string_view(args[pos]);
				auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), val);
				
				if (ec != std::errc()) {
					return printError(Error::InvalidSyntax);	
				}

                vw_config |= ViewConfig::Length;
				bytes_per_line = val;
            } else if (filepath.empty()) {
                filepath = args[pos];
            } else {
                return printError(Error::InvalidSyntax);
            }
            pos++;
        }

        return view();
    }

	return printError(Error::InvalidSyntax);
}

} // namespace zuu::hexview