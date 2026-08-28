# HexView

![Build Status](https://github.com/zuudevs/cpp_hex_viewer/actions/workflows/project-configuration.yml/badge.svg)

HexView is a modern, fast, and exception-safe Command-Line Hexadecimal File Viewer written in **C++23**. Developed as an exploration into low-level byte stream analysis, it is designed to securely parse and format binary data at gigabyte-per-second throughputs.

## Features
- **High Performance**: Achieves up to ~1.2 GiB/s I/O read throughput on modern SSDs.
- **Zero-Exception Policy**: Relies heavily on C++23 `std::expected` and `std::error_code` for robust, crash-free error handling.
- **Configurable Views**: Supports byte offsets, customizable line lengths, and ASCII column mapping.
- **Cross-Platform**: Natively supports Windows (MSVC) and Linux (GCC/Clang) via CMake and vcpkg.

## Quick Start

```bash
# Clone the repository
git clone https://github.com/zuudevs/cpp_hex_viewer.git
cd cpp_hex_viewer

# Configure and Build (Release mode)
cmake --preset msvc-release
cmake --build out/build/msvc-release --config Release

# Run the viewer
./out/bin/Release/hexview.exe --show path/to/file.bin --offset --ascii --length 16
```

## Documentation

For deep-dive documentation, please refer to the following guides:
- 📖 [Build Instructions](BUILD.md)
- 🤝 [Contributing Guide](CONTRIBUTING.md)
- 🏗️ [Architecture Overview](docs/architecture.md)
- 🚀 [CLI Reference](docs/cli_reference.md)
- 🧪 [Testing & Benchmarks](docs/testing_and_benchmarking.md)

## License
This project is licensed under the [MIT License](LICENSE).