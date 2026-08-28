# Testing & Benchmarking Strategy

HexView enforces robust verification at multiple layers to ensure both stability and performance.

## 1. Unit Testing (Google Test)
Located in `tests/unit/`, these tests validate individual class boundaries.
- **FileStream Tests**: Verifies behavior against valid, missing, and empty files.
- **HexView Tests**: Validates that bad CLI inputs (e.g., out-of-bounds length, non-numeric strings) do not cause segmentation faults or crashes.
- **Error Tests**: Asserts that `ErrorDiagnostic` properly manages memory and strings.

## 2. Integration Testing (CTest)
Located in `tests/integration/`, these tests treat the compiled `hexview.exe` as a black box.
Instead of complicated Python wrappers, we use **CMake's CTest Regex matching** (`PASS_REGULAR_EXPRESSION`).
- A dummy binary file is generated during CMake config.
- The compiled binary is invoked with various flags (e.g., `--show dummy.bin --offset`).
- `stdout` and `stderr` are piped into regex checks to guarantee the correct layout and error messages are printed.

## 3. Benchmarking (Google Benchmark)
Located in `benchmarks/`, these tests are isolated to `Release` configurations.
- **File I/O Throughput**: Measures the `Bytes/s` capabilities of `FileStream::getChunk` using varying block sizes to ensure disk operations hit gigabyte-level throughput speeds.
