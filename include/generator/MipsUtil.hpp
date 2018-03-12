#ifndef MIPS_UTIL_HPP
#define MIPS_UTIL_HPP

#include <string>

using word = uint32_t;
using hword = uint16_t;
using byte = uint8_t;

class MipsUtil {
public:
    /// The register number of the first tmp register.
    static const int TMP_BEGIN = 8;
    /// The register number 1 after the last tmp register.
    static const int TMP_END = 16;

    static std::string toHex(word val);
    static std::string toRegister(int val);
};

#endif
