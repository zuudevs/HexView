#pragma once

#include <HexView/error.hpp>

#include <cstddef>
#include <cstdint>
#include <expected>
#include <filesystem>
#include <fstream>
#include <span>
#include <vector>
#include <HexView/macros.hpp>

namespace zuu::hexview {

class FileStream {
  public:
    FileStream() NOEXCEPT = default;
    FileStream(const FileStream&) NOEXCEPT = delete;
    FileStream(FileStream&&) NOEXCEPT = default;
    FileStream&
        operator=(const FileStream&) NOEXCEPT = delete;
    FileStream&
        operator=(FileStream&&) NOEXCEPT = default;
    ~FileStream() NOEXCEPT;

    std::expected<void, Error>
        open(std::string_view filepath) NOEXCEPT;
    void
        close() NOEXCEPT;
    [[nodiscard]] std::span<std::uint8_t>
        getChunk(std::size_t bytes_per_line) NOEXCEPT;
    [[nodiscard]] std::uint64_t
        getOffset() const NOEXCEPT;

  private:
    using Path = std::filesystem::path;

    std::ifstream file;
    std::vector<std::uint8_t> buffer;
    std::uint64_t offset{};
    std::size_t size{};

    [[nodiscard]] std::expected<Path, Error>
        ResolvePath(std::string_view filepath) const NOEXCEPT;
    void
        clear() NOEXCEPT;
};

} // namespace zuu::hexview