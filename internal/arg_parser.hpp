#pragma once

#include <hex_viewer/error.hpp>

#include <iostream>
#include <string_view>

namespace zuu::hexviewer {

class ArgParser {
private:
	std::string_view args;
	Error err{Error::None};

public:
	ArgParser(std::string_view args) noexcept
	 : args(args) {}

	void help() const noexcept {
		if (hasError()) {
			std::cout << "Error: " << ResolveError(err) << '\n';
		}

		std::cout << "Usage:\n";
		std::cout << "  hv <OPTION> [FILE]\n";

		std::cout << "Option:\n";
		std::cout << "  --help, -h\tuse to show command use";
	}

	void show() const noexcept {
		// todo
	}

	[[nodiscard]] bool hasError() const noexcept { return err != Error::None; }
};

} // namespace zuu::hexviewer