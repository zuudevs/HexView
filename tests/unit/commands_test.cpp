#include <gtest/gtest.h>
#include <commands.hpp>

using namespace zuu::hexview;

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
}