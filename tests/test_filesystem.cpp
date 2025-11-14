#include <gtest/gtest.h>
#include "../src/filesystem.h"

// Add more tests as needed
TEST(FilesystemTest, WriteReadFileContent) {
    const std::string filename = "test_temp_file.bin";
    const std::vector<uint8_t> write_data = {1, 2, 3, 4, 5};
    std::vector<uint8_t> read_data;

    // Write data to file
    {
        Filesystem fs;
        ASSERT_TRUE(fs.open(filename));
        ASSERT_TRUE(fs.write(write_data));
        fs.close();
    }

    // Read data from file
    {
        Filesystem fs;
        ASSERT_TRUE(fs.open(filename));
        ASSERT_TRUE(fs.read(read_data));
        ASSERT_EQ(write_data, read_data);
    }

    // Cleanup
    ::remove(filename.c_str());
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}
