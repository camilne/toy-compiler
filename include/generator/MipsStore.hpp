#ifndef MIPS_STORE_HPP
#define MIPS_STORE_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsStore : public MipsStatement {
public:
    explicit MipsStore(unsigned int reg, unsigned int addr, int offset = 0)
        : reg(reg), addr(addr), offset(offset)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "sw " << MipsUtil::toRegister(reg) << " " << offset;
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
