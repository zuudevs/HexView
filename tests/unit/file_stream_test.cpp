#include <gtest/gtest.h>
#include <file_stream.hpp>

#include <fstream>
#include <filesystem>
#include <string>

using namespace zuu::hexview;

class FileStreamTest : public ::testing::Test {
protected:
    std::string test_file = "dummy_test_file.bin";

    void SetUp() override {
        std::ofstream dummy(test_file, std::ios::binary);
        // Write exactly 5 bytes
        dummy.write("ABCDE", 5);
        dummy.close();
    }
    
    void TearDown() override {
        if (std::filesystem::exists(test_file)) {
            std::filesystem::remove(test_file);
        }
    }
};

TEST_F(FileStreamTest, OpenValidFile) {
    FileStream fs;
    auto res = fs.open(test_file);
    EXPECT_TRUE(res.has_value());
}

TEST_F(FileStreamTest, OpenInvalidFile) {
    FileStream fs;
    auto res = fs.open("this_file_does_not_exist_123.bin");
    EXPECT_FALSE(res.has_value());
    EXPECT_EQ(res.error(), Error::PathNotFound);
}

TEST_F(FileStreamTest, GetChunkCorrectSize) {
    FileStream fs;
    ASSERT_TRUE(fs.open(test_file).has_value());
    
    // File is 5 bytes. Ask for 3 bytes.
    auto chunk = fs.getChunk(3);
    EXPECT_EQ(chunk.size(), 3);
    EXPECT_EQ(chunk[0], 'A');
    EXPECT_EQ(chunk[1], 'B');
    EXPECT_EQ(chunk[2], 'C');
    EXPECT_EQ(fs.getOffset(), 3);
    
    // Ask for 8 bytes, should only get remaining 2 bytes.
    auto chunk2 = fs.getChunk(8);
    EXPECT_EQ(chunk2.size(), 2);
    EXPECT_EQ(chunk2[0], 'D');
    EXPECT_EQ(chunk2[1], 'E');
    EXPECT_EQ(fs.getOffset(), 5);
    
    // Ask for more, should return empty
    auto chunk3 = fs.getChunk(8);
    EXPECT_TRUE(chunk3.empty());
}

TEST_F(FileStreamTest, EmptyFile) {
    std::string empty_file = "empty_test_file.bin";
    std::ofstream dummy(empty_file, std::ios::binary);
    dummy.close();
    
    FileStream fs;
    ASSERT_TRUE(fs.open(empty_file).has_value());
    
    auto chunk = fs.getChunk(8);
    EXPECT_TRUE(chunk.empty());
    
    fs.close();
    std::filesystem::remove(empty_file);
}
