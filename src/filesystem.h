#pragma once

#include <span>
#include <stdint.h>
#include <string>
#include <string_view>
#include <vector>

class Filesystem
{
public:
    ~Filesystem();
    bool open(std::string_view filename);
    bool reopen();
    void close();
    bool write(std::span<const uint8_t> data);
    bool read(std::vector<uint8_t> &data);

private:
    int fd_{-1};
    std::string filename_{};
};