#include <HexView/error.hpp>
#include <HexView/macros.hpp>
#include <HexView/version.hpp>


#include <charconv>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <span>
#include <string_view>

#include <commands.hpp>
#include <file_stream.hpp>

#ifndef NDEBUG
    #include <system_error>
#endif

#include <view_config.hpp>

#include <HexView/hex_view.hpp>

namespace zuu::hexview {

HexView::HexView() NOEXCEPT : vw_config(ViewConfig::Hex) {}

void
    HexView::printHelp() const NOEXCEPT {
    PRINTLN("HexView - A Modern C++ Hexadecimal File Viewer");
    PRINTLN("Usage:");
    PRINTLN("  hexview [options] [command]");
    PRINTLN("");
    PRINTLN("Commands:");
    PRINTLN("  -s, --show <filepath> [options]    Show the hexadecimal content of a file");
    PRINTLN("");
    PRINTLN("Options for --show:");
    PRINTLN("  --offset                            Display byte offset column on the left");
    PRINTLN(
        "  --ascii                             Display ASCII representation column on the right");
    PRINTLN("");
    PRINTLN("General Options:");
    PRINTLN("  -h, --help                          Display this help message and exit");
    PRINTLN("  -v, --version                       Display version information and exit");
}

void
    HexView::printVersion() const NOEXCEPT {
    PRINTLN("HexView");
    PRINTLN("--------------------");
    PRINTLN("Version {}", version);
    PRINTLN("Author {}", author);
    PRINTLN("Source {}", repository_url);
}

void
    HexView::view() NOEXCEPT {
    if ((vw_config & ViewConfig::Offset) != ViewConfig::None) {
        PRINT("{:<8} | ", "offset");
    }

    for (std::size_t i = 0; i < bytes_per_line; ++i) {
        PRINT("{:02X} ", i);
    }

    if ((vw_config & ViewConfig::Ascii) != ViewConfig::None) {
        PRINT("| ascii");
    }

    PRINTLN("");
    if ((vw_config & ViewConfig::Offset) != ViewConfig::None) {
        PRINT("----------");
    }

    if ((vw_config & ViewConfig::Length) != ViewConfig::None) {
        for (auto i = 0; i < bytes_per_line; ++i) {
            PRINT("---");
        }
    } else {
        PRINT("------------------------");
    }

    PRINT("--");
    if ((vw_config & ViewConfig::Ascii) != ViewConfig::None) {
        PRINT("-------");
    }
    PRINTLN("");

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
            PRINT("{:08X} | ", row_offset);
        }

        for (const auto byte : chunk) {
            PRINT("{:02X} ", static_cast<unsigned int>(byte));
        }

        for (std::size_t i = chunk.size(); i < bytes_per_line; ++i) {
            PRINT("   ");
        }

        if ((vw_config & ViewConfig::Ascii) != ViewConfig::None) {
            PRINT("| ");

            for (const auto byte : chunk) {
                const auto ch = static_cast<unsigned char>(byte);

                if (ch >= 0x20 && ch <= 0x7E) {
                    PRINT("{}", static_cast<char>(ch));
                } else {
                    PRINT(".");
                }
            }
        }

        PRINTLN("");
    }
}

void
    HexView::printError(Error errc) const NOEXCEPT {
    PRINTLN(stderr, "Error: {}", ResolveError(errc));
}

void
    HexView::exec(std::span<char*> args) NOEXCEPT {
#ifndef NDEBUG
    PRINTLN(stderr, "[{}] args size: {}\n", __FILE__, args.size());
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
            if (args[pos] == kCmdShowOptOffset &&
                (vw_config & ViewConfig::Offset) == ViewConfig::None) {
                vw_config |= ViewConfig::Offset;
            } else if (args[pos] == kCmdShowOptAscii &&
                       (vw_config & ViewConfig::Ascii) == ViewConfig::None) {
                vw_config |= ViewConfig::Ascii;
            } else if (args[pos] == kCmdShowOptLength &&
                       (vw_config & ViewConfig::Length) == ViewConfig::None) {
                pos++;
                if (pos >= args.size()) {
                    return printError(Error::InvalidSyntax);
                }
                std::int64_t val{};
                auto str = std::string_view(args[pos]);
                auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), val);

                if (ec != std::errc()) {
                    return printError(Error::InvalidSyntax);
                }

                if (val <= 0 || val > UINT8_MAX) {
                    return printError(Error::LengthOutOfRange);
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

        if (filepath.empty()) {
            return printError(Error::MissingFilePath);
        }

        return view();
    }

    return printError(Error::InvalidSyntax);
}

} // namespace zuu::hexview