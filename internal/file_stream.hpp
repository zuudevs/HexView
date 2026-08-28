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
    FileStream() noexcept = default;
    FileStream(const FileStream&) noexcept = delete;
    FileStream(FileStream&&) noexcept = default;
    FileStream&
        operator=(const FileStream&) noexcept = delete;
    FileStream&
        operator=(FileStream&&) noexcept = default;
    ~FileStream() noexcept;

    std::expected<void, ErrorDiagnostic>
        open(std::string_view filepath) noexcept;
    void
        close() noexcept;
    [[nodiscard]] std::span<std::uint8_t>
        getChunk(std::size_t bytes_per_line) noexcept;
    [[nodiscard]] std::uint64_t
        getOffset() const noexcept;

  private:
    using Path = std::filesystem::path;

    std::ifstream file;
    std::vector<std::uint8_t> buffer;
    std::uint64_t offset{};
    std::size_t size{};

    [[nodiscard]] std::expected<Path, ErrorDiagnostic>
        ResolvePath(std::string_view filepath) const noexcept;
    void
        clear() noexcept;
};

} // namespace zuu::hexview
