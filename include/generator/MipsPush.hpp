#ifndef MIPS_PUSH_HPP
#define MIPS_PUSH_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsPush : public MipsStatement {
public:
    explicit MipsPush(int reg)
        : reg(reg)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "addi $sp $sp -4\n";
        ss << "sw " << MipsUtil::toRegister(reg) << " 0($sp)\n";
        return ss.str();
    }

private:
    int reg;
};

#endif
