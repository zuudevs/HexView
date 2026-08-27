#include "commands.hpp"
#include <gtest/gtest.h>

#include <HexView/error.hpp>

using namespace zuu::hexview;

TEST(error_handling, error_message) {
	EXPECT_STREQ(ResolveError(Error::None), "No error");
	EXPECT_STREQ(ResolveError(Error::PathNotFound), "Path does not exist");
	EXPECT_STREQ(ResolveError(Error::PathNotFile), "Path does not refer to a regular file");
	EXPECT_STREQ(ResolveError(Error::InvalidPath), "Invalid path");
	EXPECT_STREQ(ResolveError(Error::InvalidSyntax), "Invalid syntax command");
	EXPECT_STREQ(ResolveError(Error::FileOpenFailed), "Failed to open file");
	EXPECT_STREQ(ResolveError(Error::LengthOutOfRange), "Length value must between 1 and 255");
	EXPECT_STREQ(ResolveError(Error::MissingFilePath), "File path is required");
	EXPECT_STREQ(ResolveError(Error::Unknown), "Unknown error");
}