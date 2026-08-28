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
    HexView() noexcept;

    void
        exec(std::span<char*> args) noexcept;

  private:
	std::uint8_t bytes_per_line{default_bytes_per_line};
    ViewConfig view_config;
	std::string_view filepath;

    void
        print_error(const ErrorDiagnostic& errc) const noexcept;
    void
        print_help() const noexcept;
    void
        print_version() const noexcept;
    void
        view() noexcept;
};

} // namespace zuu::hexview
