#pragma once

#include <cstdint>
#include <string>

namespace zuu::hexview {

enum class Error : std::uint8_t {
    None,

    PathNotFound,
    PathNotFile,
    InvalidPath,
    InvalidSyntax,
    FileOpenFailed,
	LengthOutOfRange,
	LengthInvalid,
	MissingFilePath,
	MissingLengthValue,
	DuplicateShowOption,

    // TODO: Add more errors here.

    Unknown = 255
};

[[nodiscard]] constexpr const char*
ResolveError(Error error) noexcept {
    switch (error) {
        case Error::None: return "No error";
        case Error::PathNotFound: return "Path does not exist";
        case Error::PathNotFile: return "Path does not refer to a regular file";
        case Error::InvalidPath: return "Invalid path";
        case Error::InvalidSyntax: return "Invalid syntax command";
        case Error::FileOpenFailed: return "Failed to open file";
        case Error::LengthOutOfRange: return "Length value must between 1 and 255";
        case Error::LengthInvalid: return "Length value must exact number";
        case Error::MissingFilePath: return "File path is required";
        case Error::MissingLengthValue: return "Length value is required";
        case Error::DuplicateShowOption: return "show option input is duplicated";
        case Error::Unknown:
        default: return "Unknown error";
    }
}

class ErrorDiagnostic {
private:
	Error errc;
	std::string msg;

public:
	ErrorDiagnostic(Error errc) noexcept
	 : errc(errc), msg() {}

	ErrorDiagnostic(Error errc, std::string msg)
	 : errc(errc), msg(std::move(msg)) {}

	[[nodiscard]] const char* message() const noexcept {
		if (msg.empty()) {
			return ResolveError(errc);
		}
		return msg.c_str();
	}

	[[nodiscard]] Error code() const noexcept {
		return errc;
	}
};

} // namespace zuu::hexview