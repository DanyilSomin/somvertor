#pragma once

#include <string>

namespace BigInt {

class Error {
public:
    explicit Error(const std::string &what);
    explicit Error(std::string &&what);

    Error(const Error&) = delete;
    Error(Error&&) = delete;

    Error &operator=(const Error &) = delete;
    Error &operator=(Error &&) = delete;

    const std::string &what();

public:
    std::string _what;
};

}
