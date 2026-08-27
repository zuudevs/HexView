#include "commands.hpp"
#include <gtest/gtest.h>

#include <HexView/error.hpp>

using namespace zuu::hexview;

TEST(error_handling, error_message) {
	EXPECT_EQ(ResolveError(Error::None), "No error");
	EXPECT_EQ(ResolveError(Error::PathNotFound), "Path does not exist");
	EXPECT_EQ(ResolveError(Error::PathNotFile), "Path does not refer to a regular file");
	EXPECT_EQ(ResolveError(Error::InvalidPath), "Invalid path");
	EXPECT_EQ(ResolveError(Error::InvalidSyntax), "Invalid syntax command");
	EXPECT_EQ(ResolveError(Error::FileOpenFailed), "Failed to open file");
	EXPECT_EQ(ResolveError(Error::NegativeLength), "Length value must greater than 0");
	EXPECT_EQ(ResolveError(Error::MissingFilePath), "File path is required");
	EXPECT_EQ(ResolveError(Error::Unknown), "Unknown error");
}