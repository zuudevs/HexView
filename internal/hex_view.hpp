#pragma once

#include <HexView/error.hpp>
#include <view_task.hpp>

#include <span>
#include <string_view>

namespace zuu::hexview {

class HexView {
public:
	HexView() noexcept;

	void exec(std::span<char*> args) const noexcept;

private:
	void printError(Error errc) const noexcept;
	void printHelp() const noexcept;
	void printVersion() const noexcept;
	void view(ViewTask vwtask) const noexcept;
};

} // namespace zuu::hexview