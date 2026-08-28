#include <HexView/error.hpp>

#include <cstdint>
#include <expected>

#include <file_stream.hpp>
#include <filesystem>
#include <ios>
#include <span>

#ifndef NDEBUG
    #include <system_error>
#endif

namespace fs = std::filesystem;

namespace zuu::hexview {

FileStream::~FileStream() noexcept {
    close();
}

std::expected<void, ErrorDiagnostic>
    FileStream::open(std::string_view filepath) noexcept {
    auto res = ResolvePath(filepath);
    if (!res) {
        return std::unexpected{res.error()};
    }

    clear();
    file.open(*res, std::ios::binary | std::ios::ate);

    if (!file.is_open()) {
        return std::unexpected{ErrorDiagnostic(Error::FileOpenFailed)};
    }

    auto sz = file.tellg();

    if (sz == -1) {
        file.close();
        return std::unexpected{ErrorDiagnostic(Error::FileOpenFailed, "tellg() failed to get file size")};
    }

    file.seekg(0, std::ios::beg);

    size = sz;

    return {};
}

void
    FileStream::close() noexcept {
    if (file.is_open()) {
        return file.close();
    }
}

std::span<std::uint8_t>
    FileStream::getChunk(std::size_t bytes_per_line) noexcept {
    auto remaining = size - offset;

    if (remaining == 0) {
        return std::span<std::uint8_t>{};
    }

    auto chunk = (bytes_per_line > remaining ? remaining : bytes_per_line);

    buffer.resize(chunk);

    if (file.read(reinterpret_cast<char*>(buffer.data()), static_cast<std::streamsize>(chunk))) {
        offset += chunk;

        return std::span{buffer};
    }

    return std::span<std::uint8_t>{};
}

std::uint64_t
    FileStream::getOffset() const noexcept {
    return offset;
}

std::expected<FileStream::Path, ErrorDiagnostic>
    FileStream::ResolvePath(std::string_view filepath) const noexcept {
    if (filepath.empty()) {
        return std::unexpected{ErrorDiagnostic(Error::InvalidPath)};
    }

    Path path(filepath);
    std::error_code ec;

    if (!fs::exists(path, ec) || ec) {
        if (ec) return std::unexpected{ErrorDiagnostic(Error::Unknown, ec.message())};
        return std::unexpected{ErrorDiagnostic(Error::PathNotFound)};
    }

    if (!fs::is_regular_file(path, ec) || ec) {
        if (ec) return std::unexpected{ErrorDiagnostic(Error::Unknown, ec.message())};
        return std::unexpected{ErrorDiagnostic(Error::PathNotFile)};
    }

    path = fs::canonical(path, ec);
    if (ec) {
        return std::unexpected{ErrorDiagnostic(Error::Unknown, ec.message())};
    }

    path = fs::absolute(path, ec);
    if (ec) {
        return std::unexpected{ErrorDiagnostic(Error::Unknown, ec.message())};
    }

    return path.lexically_normal();
}

void
    FileStream::clear() noexcept {
    file.clear();
    offset = 0;
    buffer.clear();
}

} // namespace zuu::hexview
