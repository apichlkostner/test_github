#include "filesystem.h"
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <array>
#include <span>
#include <array>

Filesystem::~Filesystem() {
    close();
}

bool Filesystem::open(std::string_view filename) {
    filename_ = filename;
    if (fd_ != -1) {
        ::close(fd_);
        fd_ = -1;
    }
    fd_ = ::open(filename.data(), O_RDWR | O_CREAT, 0644);
    return fd_ != -1;
}

bool Filesystem::reopen() {
    if (fd_ != -1) {
        ::close(fd_);
        fd_ = -1;
    }
    fd_ = ::open(filename_.data(), O_RDWR | O_CREAT, 0644);
    return fd_ != -1;
}

void Filesystem::close() {
    if (fd_ != -1) {
        ::close(fd_);
        fd_ = -1;
    }
}

bool Filesystem::write(std::span<const uint8_t> data) {
    if (fd_ == -1) return false;
    size_t total_written = 0;
    size_t remaining = data.size();
    while (remaining > 0) {
        ssize_t written = ::write(fd_, data.data() + total_written, remaining);
        if (written < 0) {
            return false;
        }
        total_written += static_cast<size_t>(written);
        remaining -= static_cast<size_t>(written);
    }
    return true;
}

bool Filesystem::read(std::vector<uint8_t> &data) {
    if (fd_ == -1) return false;
    data.clear();
    constexpr size_t bufsize = 4096;
    std::array<uint8_t, bufsize> buf;
    ssize_t n;
    while ((n = ::read(fd_, buf.data(), bufsize)) > 0) {
        data.insert(data.end(), buf.begin(), buf.begin() + n);
    }
    return n >= 0;
}