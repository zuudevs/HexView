#pragma once

#include <cstdint>

namespace zuu::hexview {

enum class Error : std::uint8_t {
	None,
	PathIsNotExist,
	IsNotFile,
	InvalidPath,
	CantOpenFile,
	// TODO: Will expand here!

	Unknown = 255
};

constexpr const char* ResolveError(Error err) noexcept {
	switch (err) {
		case Error::None: return "No Error";
		case Error::PathIsNotExist: return "Path is not Exist";
		case Error::IsNotFile: return "Path is not file type";
		case Error::InvalidPath: return "Invalid path format";
		case Error::CantOpenFile: return "Can't open file";
		// TODO: Will expand here!

		case Error::Unknown:
		default: return "Unknown Error";
	}
}

} // namespace zuu::hexview