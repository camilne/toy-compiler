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
    if(val == 0)
        return "$zero";
    else if(val >= TMP_BEGIN && val < TMP_END)
        return "$t" + std::to_string(val - TMP_BEGIN);
    else if(val >= SAVE_BEGIN && val < SAVE_END)
        return "$s" + std::to_string(val - SAVE_BEGIN);
    return "$INVALID(" + std::to_string(val) + ")";
}
