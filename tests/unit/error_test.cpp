#include <gtest/gtest.h>

#include <HexView/error.hpp>

using namespace zuu::hexview;

TEST(ErrorTest, ErrorMessage) {
	EXPECT_STREQ(ResolveError(Error::None), "No error");
	EXPECT_STREQ(ResolveError(Error::PathNotFound), "Path does not exist");
	EXPECT_STREQ(ResolveError(Error::PathNotFile), "Path does not refer to a regular file");
	EXPECT_STREQ(ResolveError(Error::InvalidPath), "Invalid path");
	EXPECT_STREQ(ResolveError(Error::InvalidSyntax), "Invalid syntax command");
	EXPECT_STREQ(ResolveError(Error::FileOpenFailed), "Failed to open file");
	EXPECT_STREQ(ResolveError(Error::LengthOutOfRange), "Length value must between 1 and 255");
	EXPECT_STREQ(ResolveError(Error::LengthInvalid), "Length value must exact number");
	EXPECT_STREQ(ResolveError(Error::MissingFilePath), "File path is required");
	EXPECT_STREQ(ResolveError(Error::MissingLengthValue), "Length value is required");
	EXPECT_STREQ(ResolveError(Error::Unknown), "Unknown error");
}

TEST(ErrorTest, DiagnosticMessage) {
    ErrorDiagnostic default_diag(Error::PathNotFound);
    EXPECT_STREQ(default_diag.message(), "Path does not exist");
    EXPECT_EQ(default_diag.code(), Error::PathNotFound);

    ErrorDiagnostic custom_diag(Error::Unknown, "Permission denied");
    EXPECT_STREQ(custom_diag.message(), "Permission denied");
    EXPECT_EQ(custom_diag.code(), Error::Unknown);
}