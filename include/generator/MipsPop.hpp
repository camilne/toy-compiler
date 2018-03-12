#ifndef MIPS_POP_HPP
#define MIPS_POP_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsPop : public MipsStatement {
public:
    explicit MipsPop(int reg)
        : reg(reg)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "lw " << MipsUtil::toRegister(reg) << " 0($sp)\n";
        ss << "addi $sp $sp 4\n";
        return ss.str();
    }

private:
    int reg;
};

#endif
