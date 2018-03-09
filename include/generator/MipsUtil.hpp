#ifndef MIPS_UTIL_HPP
#define MIPS_UTIL_HPP

#include <string>

using word = uint32_t;
using hword = uint16_t;
using byte = uint8_t;

class MipsUtil {
public:
    const static int FRAME_SIZE = 8 * sizeof(word);

    static std::string newFrame();
    static std::string popFrame();
    static std::string loadImmediate(std::string reg, word imm);
    static std::string add(std::string rd, std::string rs, std::string rt);
    static std::string sub(std::string rd, std::string rs, std::string rt);
};

#endif
