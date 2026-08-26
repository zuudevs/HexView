#pragma once

#include <span>
#include <string_view>

namespace zuu::hexview {

class HexView {
public:
	HexView() noexcept;

	void printHelp() const noexcept;
	void printVersion() const noexcept;
	void view() const noexcept;
	void exec(std::span<std::string_view> args) const noexcept;
};

} // namespace zuu::hexview