#pragma once

#include "HexView/error.hpp"

#include <expected>

#include <file_stream.hpp>
#include <filesystem>

#ifdef ENABLE_EXCEPTION
#include <system_error>
#endif

namespace fs = std::filesystem;

namespace zuu::hexview {

bool FileStream::open(std::string_view filepath) NOEXCEPT {
	
}

void FileStream::close() NOEXCEPT {

}

const uint8_t* const FileStream::getChunk(std::size_t bytes_per_line) NOEXCEPT {

}

std::expected<FileStream::Path, Error> FileStream::ResolvePath(std::string_view filepath) const NOEXCEPT {
	if (filepath.empty()) {
		return std::unexpected{Error::InvalidPath};
	}

	Path path(filepath);

	if (!fs::exists(path)) {
		return std::unexpected{Error::PathIsNotExist};
	}

	if (!fs::is_regular_file(path)) {
		return std::unexpected{Error::PathIsNotExist};
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

} // namespace zuu::hexview