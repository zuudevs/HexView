# Command-Line Interface Reference

HexView provides a clean, Unix-style command-line interface for inspecting binary files.

## Basic Usage

```bash
hexview --show <filepath> [options]
# Alternatively using short-hands
hexview -s <filepath> [options]
```

## Supported Flags

| Flag | Abbreviation | Description |
|------|--------------|-------------|
| `--help` | `-h` | Prints the help message and exits. |
| `--version` | `-v` | Prints the version information and exits. |
| `--show` | `-s` | Specifies the target file to open and display. |
| `--offset` | | Adds a byte offset column to the left of the hex output. |
| `--ascii` | | Adds an ASCII character representation column to the right. |
| `--length` | | Specifies how many bytes to print per line (Min: 1, Max: 255). Default is 8. |

## Examples

### 1. Simple Output
Display a file with the default 8 bytes per line:
```bash
hexview --show file.bin
```

### 2. Full Verbosity
Display the offset, hex, and ASCII characters side-by-side:
```bash
hexview -s file.bin --offset --ascii
```

### 3. Custom Line Length
Read 16 bytes per line:
```bash
hexview -s file.bin --offset --ascii --length 16
```
