#include <gtest/gtest.h>
#include <commands.hpp>
#include <span>

using namespace zuu::hexview;

constexpr char kCmdHelpTest[] = {'-', '-', 'h', 'e', 'l', 'p'};
constexpr char kCmdHelpAbrvTest[] = {'-', 'h'};
constexpr char kCmdVersionTest[] = {'-', '-', 'v', 'e', 'r', 's', 'i', 'o', 'n'};
constexpr char kCmdVersionAbrvTest[] = {'-', 'v'};
constexpr char kCmdShowTest[] = {'-', '-', 's', 'h', 'o', 'w'};
constexpr char kCmdShowAbrvTest[] = {'-', 's'};
constexpr char kCmdShowOptOffsetTest[] = {'-', '-', 'o', 'f', 'f', 's', 'e', 't'};
constexpr char kCmdShowOptAsciiTest[] = {'-', '-', 'a', 's', 'c', 'i', 'i'};
constexpr char kCmdShowOptLengthTest[] = {'-', '-', 'l', 'e', 'n', 'g', 't', 'h'};

TEST(CommandTest, CommandEqualityCheck) {
	EXPECT_EQ(kCmdHelp, "--help");
	EXPECT_EQ(kCmdHelpAbrv, "-h");
	EXPECT_EQ(kCmdVersion, "--version");
	EXPECT_EQ(kCmdVersionAbrv, "-v");
	EXPECT_EQ(kCmdShow, "--show");
	EXPECT_EQ(kCmdShowAbrv, "-s");
	EXPECT_EQ(kCmdShowOptOffset, "--offset");
	EXPECT_EQ(kCmdShowOptAscii, "--ascii");
	EXPECT_EQ(kCmdShowOptLength, "--length");

	EXPECT_NE(kCmdHelpTest, "--help");
	EXPECT_NE(kCmdHelpAbrvTest, "-h");
	EXPECT_NE(kCmdVersionTest, "--version");
	EXPECT_NE(kCmdVersionAbrvTest, "-v");
	EXPECT_NE(kCmdShowTest, "--show");
	EXPECT_NE(kCmdShowAbrvTest, "-s");
	EXPECT_NE(kCmdShowOptOffsetTest, "--offset");
	EXPECT_NE(kCmdShowOptAsciiTest, "--ascii");
	EXPECT_NE(kCmdShowOptLengthTest, "--length");

	EXPECT_NE(kCmdHelp, kCmdHelpTest);
	EXPECT_NE(kCmdHelpAbrv, kCmdHelpAbrvTest);
	EXPECT_NE(kCmdVersion, kCmdVersionTest);
	EXPECT_NE(kCmdVersionAbrv, kCmdVersionAbrvTest);
	EXPECT_NE(kCmdShow, kCmdShowTest);
	EXPECT_NE(kCmdShowAbrv, kCmdShowAbrvTest);
	EXPECT_NE(kCmdShowOptOffset, kCmdShowOptOffsetTest);
	EXPECT_NE(kCmdShowOptAscii, kCmdShowOptAsciiTest);
	EXPECT_NE(kCmdShowOptLength, kCmdShowOptLengthTest);
}