#pragma once

#include <HexView/error.hpp>
#include <HexView/macros.hpp>

#include <span>

namespace zuu::hexview {

class HexView {
  public:
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