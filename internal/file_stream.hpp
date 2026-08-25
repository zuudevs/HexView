#pragma once

#include <HexView/error.hpp>

#include <cstddef>
#include <cstdint>
#include <filesystem>
#include <fstream>
#include <vector>

namespace zuu::hexview {

class FileStream final {
public:
	FileStream() noexcept;
	FileStream(const FileStream&) noexcept;
	FileStream(FileStream&&) noexcept;
	FileStream& operator=(const FileStream&) noexcept;
	FileStream& operator=(FileStream&&) noexcept;
	~FileStream() noexcept;

	bool open(std::string_view filepath) noexcept;
	void close() noexcept;
	const uint8_t* const getChunk(std::size_t bytes_per_line = 8) noexcept;
	[[nodiscard]] bool hasError() const noexcept;

private:
	using Path = std::filesystem::path;

	std::ifstream file;
	std::vector<std::uint8_t> buffer;
	std::uint64_t offset;
	std::size_t size;
	Error error;

	[[nodiscard]] Path ResolvePath(std::string_view filepath) const noexcept;
};

} // namespace zuu::hexview