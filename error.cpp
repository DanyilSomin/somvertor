#include "error.h"

namespace BigInt {

Error::Error(const std::string &what) : _what{ what } { }

Error::Error(std::string &&what) : _what{ what } { }

const std::string &Error::what() { return _what; }

}
