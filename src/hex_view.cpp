#include <HexView/error.hpp>
#include <HexView/macros.hpp>
#include <HexView/version.hpp>


#include <charconv>
#include <cstdint>
#include <cstdio>
#include <cstring>
#include <span>
#include <string>
#include <string_view>

#include <commands.hpp>
#include <file_stream.hpp>

#ifndef NDEBUG
    #include <system_error>
#endif

#include <view_config.hpp>

#include <HexView/hex_view.hpp>

namespace {

[[nodiscard]] inline bool is_4_bytes_numeric(std::string_view str) noexcept {
	if (str.empty() || str.size() > 4) {
    	return false;
	}

	if (str.size() == 1 && static_cast<std::uint8_t>(str[0] - '0') > 9) {
		return false;
	}

	constexpr std::uint32_t kBytesZero4 = 0x30303030;
	constexpr std::uint32_t kBytesNine4 = 0x39393939;

	std::uint32_t block{kBytesZero4};

	std::memcpy(&block, str.data(), str.size());

	constexpr std::uint32_t kBytesLow4 = 0x01010101;
	constexpr std::uint32_t kBytesHigh4 = 0x80808080;

	constexpr std::uint32_t kBytesMax4 = kBytesHigh4 - kBytesNine4 - kBytesLow4;

	std::uint32_t left = block - kBytesZero4;
	std::uint32_t right = block + kBytesMax4;
	return ((left | right) & kBytesHigh4) == 0;
}

} // namespace

namespace zuu::hexview {

HexView::HexView() noexcept : view_config(ViewConfig::Hex) {}

void
    HexView::print_help() const noexcept {
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
    HexView::print_version() const noexcept {
    PRINTLN("HexView");
    PRINTLN("--------------------");
    PRINTLN("Version {}", version);
    PRINTLN("Author {}", author);
    PRINTLN("Source {}", repository_url);
}

void
    HexView::view() noexcept {
    if ((view_config & ViewConfig::Offset) != ViewConfig::None) {
        PRINT("{:<8} | ", "offset");
    }

    for (std::size_t i = 0; i < bytes_per_line; ++i) {
        PRINT("{:02X} ", i);
    }

    if ((view_config & ViewConfig::Ascii) != ViewConfig::None) {
        PRINT("| ascii");
    }

    PRINTLN("");
    if ((view_config & ViewConfig::Offset) != ViewConfig::None) {
        PRINT("----------");
    }

    PRINT("{}", std::string(bytes_per_line * 3, '-'));

    PRINT("--");
    if ((view_config & ViewConfig::Ascii) != ViewConfig::None) {
        PRINT("-------");
    }
    PRINTLN("");

    FileStream fst;

    auto res = fst.open(filepath);
    if (!res) {
        return print_error(res.error());
    }

    while (true) {
        const auto chunk = fst.getChunk(bytes_per_line);

        if (chunk.empty()) {
            break;
        }

        const auto row_offset = fst.getOffset();

        if ((view_config & ViewConfig::Offset) != ViewConfig::None) {
            PRINT("{:08X} | ", row_offset);
        }

        for (const auto byte : chunk) {
            PRINT("{:02X} ", static_cast<unsigned int>(byte));
        }

        for (std::size_t i = chunk.size(); i < bytes_per_line; ++i) {
            PRINT("   ");
        }

        if ((view_config & ViewConfig::Ascii) != ViewConfig::None) {
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
    HexView::print_error(const ErrorDiagnostic& errc) const noexcept {
    PRINTLN_ERROR("Error: {}", errc.message());
}

void
    HexView::exec(std::span<char*> args) noexcept {
#ifndef NDEBUG
    PRINTLN_ERROR("[{}] args size: {}\n", __FILE__, args.size());
#endif

    if (args.size() < 2) {
        return print_help();
    }

    auto pos = 1;

    if (args[pos] == kCmdHelp || args[pos] == kCmdHelpAbrv) {
        return print_help();
    }

    if (args[pos] == kCmdVersion || args[pos] == kCmdVersionAbrv) {
        return print_version();
    }

    if (args[pos] == kCmdShow || args[pos] == kCmdShowAbrv) {
        pos++;
        while (pos < args.size()) {
            if (args[pos] == kCmdShowOptOffset) {
                if ((view_config & ViewConfig::Offset) != ViewConfig::None) {
                    return print_error(Error::InvalidSyntax);
                }
                view_config |= ViewConfig::Offset;
            } else if (args[pos] == kCmdShowOptAscii) {
                if ((view_config & ViewConfig::Ascii) != ViewConfig::None) {
                    return print_error(Error::InvalidSyntax);
                }
                view_config |= ViewConfig::Ascii;
            } else if (args[pos] == kCmdShowOptLength) {
                if ((view_config & ViewConfig::Length) != ViewConfig::None) {
                    return print_error(Error::InvalidSyntax);
                }
                pos++;
                if (pos >= args.size()) {
                    return print_error(Error::MissingLengthValue);
                }

				if (!is_4_bytes_numeric(args[pos])) {
					return print_error(Error::LengthInvalid);
				}

                std::int64_t val{};
                auto str = std::string_view(args[pos]);
                auto [ptr, ec] = std::from_chars(str.data(), str.data() + str.size(), val);

                if (ec != std::errc() || ptr != str.data() + str.size()) {
                    return print_error(Error::InvalidSyntax);
                }

                if (val <= 0 || val > UINT8_MAX) {
                    return print_error(Error::LengthOutOfRange);
                }

                view_config |= ViewConfig::Length;
                bytes_per_line = val;
            } else if (filepath.empty() && args[pos][0] != '-') {
                filepath = args[pos];
            } else {
                return print_error(Error::InvalidSyntax);
            }
            pos++;
        }

        if (filepath.empty()) {
            return print_error(Error::MissingFilePath);
        }

        return view();
    }

    return print_error(Error::InvalidSyntax);
}

} // namespace zuu::hexview
