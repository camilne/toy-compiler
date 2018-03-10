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
    static std::string div(std::string rd, std::string rs, std::string rt);
    static std::string mul(std::string rd, std::string rs, std::string rt);
    static std::string sub(std::string rd, std::string rs, std::string rt);
    static std::string toHex(word val);
    static std::string push(std::string reg);
    static std::string pop(std::string reg);
    static std::string copy(std::string dest, std::string src);
    static std::string comment(std::string message);
};

#endif
