#ifndef MIPS_MULTIPLY_HPP
#define MIPS_MULTIPLY_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsMultiply : public MipsStatement {
public:
    MipsMultiply(int dest, int arg1, int arg2)
        : dest(dest), arg1(arg1), arg2(arg2)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "mul " << MipsUtil::toRegister(dest) << " ";
        ss << MipsUtil::toRegister(arg1) << " ";
        ss << MipsUtil::toRegister(arg2) << "\n";
        return ss.str();
    }

private:
    int dest;
    int arg1;
    int arg2;
};

#endif
