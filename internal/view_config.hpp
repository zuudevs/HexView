#pragma once

#include <cstdint>

namespace zuu::hexview {

enum class ViewConfig : std::uint8_t {
	None    = 0,
	Hex	    = None,
	Offset	= 1 << 0,
	Ascii	= 1 << 1,
	Length  = 1 << 2
};

constexpr ViewConfig operator|(ViewConfig lhs, ViewConfig rhs) noexcept {
	return static_cast<ViewConfig>(static_cast<std::uint8_t>(lhs) | static_cast<std::uint8_t>(rhs));
}

constexpr ViewConfig operator&(ViewConfig lhs, ViewConfig rhs) noexcept {
	return static_cast<ViewConfig>(static_cast<std::uint8_t>(lhs) & static_cast<std::uint8_t>(rhs));
}

constexpr ViewConfig operator^(ViewConfig lhs, ViewConfig rhs) noexcept {
	return static_cast<ViewConfig>(static_cast<std::uint8_t>(lhs) ^ static_cast<std::uint8_t>(rhs));
}

constexpr ViewConfig operator~(ViewConfig val) noexcept {
	return static_cast<ViewConfig>(~static_cast<std::uint8_t>(val));
}

constexpr ViewConfig& operator|=(ViewConfig& lhs, ViewConfig rhs) noexcept {
	lhs = lhs | rhs;
	return lhs;
}

constexpr ViewConfig& operator&=(ViewConfig& lhs, ViewConfig rhs) noexcept {
	lhs = lhs & rhs;
	return lhs;
}

constexpr ViewConfig& operator^=(ViewConfig& lhs, ViewConfig rhs) noexcept {
	lhs = lhs ^ rhs;
	return lhs;
}

} // namespace zuu::hexview