#include <benchmark/benchmark.h>
#include <file_stream.hpp>
#include <fstream>
#include <filesystem>
#include <vector>
#include <string>

using namespace zuu::hexview;

static void SetupDummyFile(const std::string& path, size_t size) {
    if (!std::filesystem::exists(path) || std::filesystem::file_size(path) != size) {
        std::ofstream ofs(path, std::ios::binary);
        std::vector<char> data(1024, 'A');
        for (size_t i = 0; i < size / 1024; ++i) {
            ofs.write(data.data(), data.size());
        }
    }
}

static void BM_FileStreamRead(benchmark::State& state) {
    const std::string filepath = "assets/samples/benchmark_dummy.bin";
    size_t file_size = 10 * 1024 * 1024; // 10 MB
    SetupDummyFile(filepath, file_size);

    size_t chunk_size = state.range(0);

    for (auto _ : state) {
        FileStream fs;
        auto res = fs.open(filepath);
        if (!res) {
            state.SkipWithError("Failed to open file");
            break;
        }

        while (true) {
            auto chunk = fs.getChunk(chunk_size);
            if (chunk.empty()) break;
            benchmark::DoNotOptimize(chunk.data());
        }
    }
    state.SetBytesProcessed(state.iterations() * file_size);
}
// Test reading with 16 bytes (default), 4KB, and 64KB chunks
BENCHMARK(BM_FileStreamRead)->RangeMultiplier(16)->Range(16, 65536);

