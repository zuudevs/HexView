# Contributing to HexView

First off, thank you for considering contributing to HexView! It's people like you that make open-source software great.

## Development Workflow

1. **Fork the repository** and clone it locally.
2. **Create a feature branch** (`git checkout -b feature/amazing-feature`).
3. **Write your code**. Ensure you follow modern C++23 standards.
4. **Format and lint** your code.
5. **Write and run tests** to ensure no regressions were introduced.
6. **Commit and push** your changes.
7. **Open a Pull Request** against the `main` branch.

## Code Style & Linting

HexView maintains strict code quality standards:
- **Formatting**: We use `clang-format`. Please ensure your editor is configured to format on save, or run the CMake format target.
- **Linting**: We use `clang-tidy`. The build system will automatically flag warnings if `ENABLE_CLANG_TIDY=ON`.

Please fix any static analysis warnings before submitting your Pull Request.

## Running Tests

HexView employs two types of testing: Unit Tests (via Google Test) and Integration Tests (via CTest regex matching).

To run the test suite, you should build the project in **Debug** mode:

```bash
# Configure and build
cmake --preset msvc-debug
cmake --build out/build/msvc-debug

# Run all tests
ctest --test-dir out/build/msvc-debug --output-on-failure -C Debug
```

## Running Benchmarks

If you are modifying performance-critical paths (like File I/O or hex string conversions), you must verify that throughput has not degraded.

Benchmarks **must** be run in **Release** mode to produce accurate results:

```bash
# Configure and build in Release
cmake --preset msvc-release
cmake --build out/build/msvc-release --config Release

# Run benchmark suite
ctest --test-dir out/build/msvc-release -C Release -R Benchmark
```
