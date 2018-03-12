#include "generator/MipsUtil.hpp"
#include <iostream>
#include <sstream>

// static
std::string MipsUtil::toHex(word val) {
    std::stringstream ss;
    ss << std::hex << val;
    return ss.str();
}

// static
std::string MipsUtil::toRegister(int val) {
    std::string strVal = std::to_string(val - TMP_BEGIN);
    if(val >= TMP_BEGIN && val < TMP_END)
        return "$t" + strVal;
    return "$INVALID(" + strVal + ")";
}
