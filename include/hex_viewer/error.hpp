#pragma once

#include <cstdint>

namespace zuu::hexviewer {

enum class Error : uint8_t {
	None,
	// will expand here!

	Unknown = 255
};

constexpr const char* ResolveError(Error err) noexcept {
	switch (err) {
		case Error::None: return "Everything is alright";
		// will expand here!
		
		case Error::Unknown:
		default: return "Unknown Error";
	}
}

} // namespace zuu::hexviewer