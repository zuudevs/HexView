#pragma once

#include <cstdint>

namespace zuu::hexview {

enum class Error : std::uint8_t {
    None,

    PathNotFound,
    PathNotFile,
    InvalidPath,
    InvalidSyntax,
    FileOpenFailed,
	NegativeLength,
	MissingFilePath,

    // TODO: Add more errors here.

    Unknown = 255
};

[[nodiscard]] constexpr const char*
ResolveError(Error error) noexcept {
    switch (error) {
        case Error::None:
            return "No error";

        case Error::PathNotFound:
            return "Path does not exist";

        case Error::PathNotFile:
            return "Path does not refer to a regular file";

        case Error::InvalidPath:
            return "Invalid path";

        case Error::InvalidSyntax:
            return "Invalid syntax command";

        case Error::FileOpenFailed:
            return "Failed to open file";

        case Error::NegativeLength:
            return "Length value must greater than 0";

        case Error::MissingFilePath:
            return "File path is required";

        case Error::Unknown:
        default:
            return "Unknown error";
    }
}

} // namespace zuu::hexview