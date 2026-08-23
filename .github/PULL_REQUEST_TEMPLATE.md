## Summary

<!-- Briefly describe what this pull request changes and why. -->

## Changes

<!-- List the main changes introduced by this PR. -->

- 
- 
- 

## Type of Change

- [ ] `feat` — New feature
- [ ] `fix` — Bug fix
- [ ] `perf` — Performance improvement
- [ ] `refactor` — Internal code restructuring
- [ ] `test` — Add or update tests
- [ ] `docs` — Documentation change
- [ ] `build` — Build system or dependency change
- [ ] `ci` — CI/CD change
- [ ] `chore` — Maintenance task
- [ ] `breaking` — Breaking API, ABI, or behavioral change

## Related Issues

<!-- Example: Closes #123 -->

N/A

## Implementation Details

<!--
Explain important implementation decisions.

Consider mentioning:
- algorithms
- data structures
- memory ownership
- object lifetime
- allocation behavior
- SIMD/platform-specific behavior
- API/ABI implications
- important trade-offs
-->

N/A

## API / ABI Impact

- [ ] No public API changes
- [ ] Public API added
- [ ] Public API modified
- [ ] Public API removed
- [ ] ABI may be affected
- [ ] Not applicable

<!-- Describe the impact when applicable. -->

## Performance Impact

- [ ] No expected performance impact
- [ ] Performance improvement
- [ ] Performance regression is possible
- [ ] Benchmark required
- [ ] Not applicable

<!--
If performance-sensitive code changed, provide benchmark results.

Example:

Before:
Benchmark_ParseSmall    120 ns

After:
Benchmark_ParseSmall     95 ns

Improvement: ~20.8%
-->

## Testing

### Tests Added / Updated

- [ ] Unit tests
- [ ] Integration tests
- [ ] Fuzz tests
- [ ] Regression tests
- [ ] No new tests required

### Verification

- [ ] Debug build succeeds
- [ ] Release build succeeds
- [ ] Unit tests pass
- [ ] Integration tests pass
- [ ] Fuzz target builds
- [ ] Relevant fuzzing executed
- [ ] Benchmarks executed
- [ ] `clang-format` passes
- [ ] `clang-tidy` passes

### Test Commands

```shell

```

## Platform / Compiler Verification

### Operating System

* [ ] Windows
* [ ] Linux
* [ ] macOS
* [ ] Other

### Compiler

* [ ] Clang
* [ ] GCC
* [ ] MSVC
* [ ] Apple Clang
* [ ] Other

## Build System / Dependencies

* [ ] No build-system changes
* [ ] `CMakeLists.txt` changed
* [ ] CMake module changed
* [ ] CMake preset changed
* [ ] `vcpkg.json` changed
* [ ] Third-party dependency added
* [ ] Third-party dependency updated

<!-- Explain dependency or build changes if applicable. -->

## Documentation

* [ ] Documentation updated
* [ ] Examples updated
* [ ] Comments updated where necessary
* [ ] No documentation changes required

## Breaking Changes

<!--
Describe any source, binary, behavioral, configuration,
or build-system incompatibility introduced by this PR.

Write "None" if there are no breaking changes.
-->

None.

## Checklist

* [ ] The change is focused on a single concern.
* [ ] The code follows the project's coding conventions.
* [ ] Public headers expose only intended API.
* [ ] Internal implementation details remain outside the public API.
* [ ] No unnecessary allocations or copies were introduced.
* [ ] Object lifetime and ownership are well-defined.
* [ ] Undefined behavior has been considered.
* [ ] Error handling follows the project's conventions.
* [ ] Tests cover relevant behavior and edge cases.
* [ ] Performance-sensitive changes are benchmarked when appropriate.
* [ ] Documentation is updated when behavior or API changes.
* [ ] Generated or build artifacts are not included in the commit.

## Additional Notes

<!--
Anything reviewers should know that does not fit above.

Examples:
- known limitations
- follow-up work
- intentionally deferred changes
- design considerations
-->

N/A