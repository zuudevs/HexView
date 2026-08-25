#pragma once

#include <cstdint>

namespace zuu::hexview {

enum class Error : std::uint8_t {
	None,
	// TODO: Will expand here!

	Unknown = 255
};

constexpr const char* ResolveError(Error err) noexcept {
	switch (err) {
		case Error::None: return "No Error";
		// TODO: Will expand here!
		
		case Error::Unknown:
		default: return "Unknown Error";
	}
}

} // namespace zuu::hexview