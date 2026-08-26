#pragma once

#include "HexView/error.hpp"

#include <cstdint>
#include <expected>

#include <file_stream.hpp>
#include <filesystem>
#include <ios>
#include <span>

#ifdef ENABLE_EXCEPTION
#include <system_error>
#endif

namespace fs = std::filesystem;

namespace zuu::hexview {

FileStream::~FileStream() NOEXCEPT {
	close();
}

std::expected<void, Error> FileStream::open(std::string_view filepath) NOEXCEPT {
	auto res = ResolvePath(filepath);
	if (!res) {
		return std::unexpected{res.error()};
	}

	clear();
	file.open(*res, std::ios::binary | std::ios::ate);

	if (!file.is_open()) {
		return std::unexpected{Error::FileOpenFailed};
	}

	auto sz = file.tellg();

	if (sz == -1) {
        file.close();
        return std::unexpected{Error::FileOpenFailed};
    }

	file.seekg(0, std::ios::beg);

	size = sz;

	return {};
}

void FileStream::close() NOEXCEPT {
	if (file.is_open()) {
		return file.close();
	}
}

std::span<std::uint8_t> FileStream::getChunk(std::size_t bytes_per_line) NOEXCEPT {
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

std::expected<FileStream::Path, Error> FileStream::ResolvePath(std::string_view filepath) const NOEXCEPT {
	if (filepath.empty()) {
		return std::unexpected{Error::InvalidPath};
	}

	Path path(filepath);

	if (!fs::exists(path)) {
		return std::unexpected{Error::PathNotFound};
	}

	if (!fs::is_regular_file(path)) {
		return std::unexpected{Error::PathNotFile};
	}

#ifdef ENABLE_EXCEPTION
	std::error_code errc{};
	path = fs::canonical(path, errc);

	if (errc) {
		throw std::system_error(errc, errc.message());
	}
#else
	path = fs::canonical(path);
#endif

	return fs::absolute(path).lexically_normal();
}

void FileStream::clear() NOEXCEPT {
	file.clear();
	offset = 0;
	buffer.clear();
}

} // namespace zuu::hexview