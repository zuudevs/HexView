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

TEST(HexViewTest, NoCrashOnInvalidLengthValue) {
    HexView hv;
    char arg0[] = "hexview";
    char arg1[] = "-s";
    char arg2[] = "dummy.bin";
    char arg3[] = "--length";
    char arg4[] = "300"; // Out of range (> 255)
    std::vector<char*> args = {arg0, arg1, arg2, arg3, arg4};
    
    // Should detect out of range and return error gracefully
    EXPECT_NO_THROW(hv.exec(args));
    
    char arg4_neg[] = "-5";
    args[4] = arg4_neg;
    EXPECT_NO_THROW(hv.exec(args));
    
    char arg4_zero[] = "0";
    args[4] = arg4_zero;
    EXPECT_NO_THROW(hv.exec(args));
}
