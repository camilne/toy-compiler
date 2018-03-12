#ifndef MIPS_DIVIDE_HPP
#define MIPS_DIVIDE_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsDivide : public MipsStatement {
public:
    MipsDivide(int dest, int arg1, int arg2)
        : dest(dest), arg1(arg1), arg2(arg2)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "div " << MipsUtil::toRegister(dest) << " ";
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
