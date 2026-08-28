# Build Guide

HexView is written in **C++23** and leverages **CMake** along with **vcpkg** for dependency management.

## Prerequisites

Before building the project, ensure you have the following installed on your system:

1. **C++23 Compatible Compiler**:
   - Windows: MSVC 19.44+ (Visual Studio 2022)
   - Linux: GCC 14+ or Clang 17+
2. **[CMake](https://cmake.org/)** (Version 3.20 or higher)
3. **[vcpkg](https://vcpkg.io/)**: Configured and accessible in your environment.

## Dependencies

The project relies on the following libraries (automatically fetched by vcpkg via `vcpkg.json`):
- `fmt`: For fast, safe string formatting.
- `gtest`: Google Test for unit testing.
- `benchmark`: Google Benchmark for performance testing.

## Building the Project

We provide CMake presets to simplify the configuration process across different platforms.

### Windows (MSVC)

```bash
# 1. Configure the project for Release mode
cmake --preset msvc-release

# 2. Build the project
cmake --build out/build/msvc-release --config Release
```

### Linux (GCC / Clang)

```bash
# 1. Configure the project
cmake --preset gcc-release
# Or for Clang: cmake --preset clang-release

# 2. Build the project
cmake --build out/build/gcc-release --config Release
```

Once the build completes successfully, the compiled `hexview` executable will be located in the `out/bin/Release` directory.

## Customizing the Build

You can customize the build behavior by passing variables to CMake during the configuration step. Alternatively, these are defined in `cmake/modules/options.cmake`.

| Option | Default | Description |
|--------|---------|-------------|
| `ENABLE_TEST` | `ON` | Compiles unit and integration tests. |
| `ENABLE_BENCHMARK` | Auto | Compiles benchmarks. Defaults to `ON` in Release builds, `OFF` in Debug. |
| `ENABLE_WARNING` | `ON` | Enables strict compiler warnings (`-Wall -Wextra` / `/W4`). |
| `ENABLE_SANITIZE` | `ON` | Enables ASan/UBSan memory sanitizers (compiler-dependent). |
| `ENABLE_CLANG_FORMAT`| `ON` | Integrates `clang-format` into the build step. |
| `ENABLE_CLANG_TIDY` | `ON` | Integrates static analysis via `clang-tidy`. |
