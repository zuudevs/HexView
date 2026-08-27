#pragma once

#include <string_view>

namespace zuu::hexview {

constexpr std::string_view kCmdHelp = "--help";
constexpr std::string_view kCmdHelpAbrv = "-h";
constexpr std::string_view kCmdVersion = "--version";
constexpr std::string_view kCmdVersionAbrv = "-v";
constexpr std::string_view kCmdShow = "--show";
constexpr std::string_view kCmdShowAbrv = "-s";
constexpr std::string_view kCmdShowOptOffset = "--offset";
constexpr std::string_view kCmdShowOptAscii = "--ascii";
constexpr std::string_view kCmdShowOptLength = "--length";

} // namespace zuu::hexview