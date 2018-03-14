#ifndef MIPS_LOAD_HPP
#define MIPS_LOAD_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsLoad : public MipsStatement {
public:
    explicit MipsLoad(unsigned int reg, unsigned int addr, int offset = 0)
        : reg(reg), addr(addr), offset(offset)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "lw " << MipsUtil::toRegister(reg) << " " << offset;
        ss << "(" << MipsUtil::toRegister(addr) << ")\n";
        return ss.str();
    }

    unsigned int getRegister() const {
        return reg;
    }

private:
    unsigned int reg;
    unsigned int addr;
    int offset;
};

#endif
