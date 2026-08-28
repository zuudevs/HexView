#include <gtest/gtest.h>
#include <HexView/hex_view.hpp>

#include <vector>

using namespace zuu::hexview;

TEST(HexViewTest, NoCrashOnEmptyArgs) {
    HexView hv;
    std::vector<char*> args;
    // Should print help and return
    EXPECT_NO_THROW(hv.exec(args));
}

TEST(HexViewTest, NoCrashOnOutOfBoundsLength) {
    HexView hv;
    char arg0[] = "hexview";
    char arg1[] = "--show";
    char arg2[] = "dummy.bin";
    char arg3[] = "--length";
    std::vector<char*> args = {arg0, arg1, arg2, arg3};
    
    // Should detect out of bounds and return invalid syntax gracefully
    EXPECT_NO_THROW(hv.exec(args));
}

bool is_4_bytes_numeric_test(std::string_view str) noexcept {
	if (str.empty() || str.size() > 4) {
    	return false;
	}

	if (str.size() == 1 && static_cast<std::uint8_t>(str[0] - '0') > 9) {
		return false;
	}

	constexpr std::uint32_t kBytesZero4 = 0x30303030;
	constexpr std::uint32_t kBytesNine4 = 0x39393939;

	std::uint32_t block{kBytesZero4};

	std::memcpy(&block, str.data(), str.size());

	constexpr std::uint32_t kBytesLow4 = 0x01010101;
	constexpr std::uint32_t kBytesHigh4 = 0x80808080;

	constexpr std::uint32_t kBytesMax4 = kBytesHigh4 - kBytesNine4 - kBytesLow4;

	std::uint32_t left = block - kBytesZero4;
	std::uint32_t right = block + kBytesMax4;
	return ((left | right) & kBytesHigh4) == 0;
}

TEST(HexViewTest, NoCrashOnInvalidLengthValue) {
    HexView hv;
    char arg0[] = "hexview";
    char arg1[] = "-s";
    char arg2[] = "dummy.bin";
    char arg3[] = "--length";
    char arg4[] = "300"; // Out of range (> 255)
    std::vector<char*> args = {arg0, arg1, arg2, arg3, arg4};

	EXPECT_EQ(is_4_bytes_numeric_test("9999"), true);
	EXPECT_EQ(is_4_bytes_numeric_test("999"), true);
	EXPECT_EQ(is_4_bytes_numeric_test("9"), true);
	EXPECT_EQ(is_4_bytes_numeric_test(""), false);
	EXPECT_EQ(is_4_bytes_numeric_test("9a"), false);
	EXPECT_EQ(is_4_bytes_numeric_test("-9"), false);
    
    // Should detect out of range and return error gracefully
    EXPECT_NO_THROW(hv.exec(args));
    
    char arg4_neg[] = "-5";
    args[4] = arg4_neg;
    EXPECT_NO_THROW(hv.exec(args));
    
    char arg4_zero[] = "0";
    args[4] = arg4_zero;
    EXPECT_NO_THROW(hv.exec(args));
}