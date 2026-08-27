#pragma once

#include <HexView/error.hpp>
#include <HexView/macros.hpp>

#include "view_config.hpp"

#include <span>
#include <string_view>

namespace zuu::hexview {

class HexView {
  public:
    static inline ViewConfig vw_config{ViewConfig::Hex};
	static inline std::string_view filepath;
	static inline std::uint8_t bytes_per_line{8};
    HexView() NOEXCEPT;

    void
        exec(std::span<char*> args) const NOEXCEPT;

  private:
    void
        printError(Error errc) const NOEXCEPT;
    void
        printHelp() const NOEXCEPT;
    void
        printVersion() const NOEXCEPT;
    void
        view() const NOEXCEPT;
};

} // namespace zuu::hexview