#include "generator/MipsUtil.hpp"
#include <iostream>
#include <sstream>

// static
std::string MipsUtil::loadImmediate(std::string reg, word imm) {
    return "li " + reg + " " + std::to_string(imm) + "\n";
}

// static
std::string MipsUtil::add(std::string rd, std::string rs, std::string rt) {
    return "add " + rd + " " + rs + " " + rt + "\n";
}

// static
std::string MipsUtil::div(std::string rd, std::string rs, std::string rt) {
    return "div " + rd + " " + rs + " " + rt + "\n";
}

// static
std::string MipsUtil::mul(std::string rd, std::string rs, std::string rt) {
    return "mul " + rd + " " + rs + " " + rt + "\n";
}

// static
std::string MipsUtil::sub(std::string rd, std::string rs, std::string rt) {
    return "sub " + rd + " " + rs + " " + rt + "\n";
}

// static
std::string MipsUtil::toHex(word val) {
    std::stringstream ss;
    ss << std::hex << val;
    return ss.str();
}

// static
std::string MipsUtil::push(std::string reg) {
    std::string code;
    code += "addi $sp $sp -4\n";
    code += "sw " + reg + " 0($sp)\n";
    return code;
}

// static
std::string MipsUtil::pop(std::string reg) {
    std::string code;
    code += "lw " + reg + " 0($sp)\n";
    code += "addi $sp $sp 4\n";
    return code;
}

// static
std::string MipsUtil::copy(std::string dest, std::string src) {
    return add(dest, src, "$zero");
}

// static
std::string MipsUtil::comment(std::string message) {
    return "# " + message + "\n";
}
