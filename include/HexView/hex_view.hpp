#pragma once

#include <HexView/error.hpp>
#include <HexView/macros.hpp>

#include <cstdint>
#include <span>
#include <string_view>

namespace zuu::hexview {
    
enum class ViewConfig : std::uint8_t;

class HexView {
  public:
	static constexpr std::uint8_t default_bytes_per_line = 8;
    HexView() NOEXCEPT;

    void
        exec(std::span<char*> args) NOEXCEPT;

  private:
	std::uint8_t bytes_per_line{default_bytes_per_line};
    ViewConfig vw_config;
	std::string_view filepath;

    void
        printError(Error errc) const NOEXCEPT;
    void
        printHelp() const NOEXCEPT;
    void
        printVersion() const NOEXCEPT;
    void
        view() NOEXCEPT;
};

} // namespace zuu::hexview