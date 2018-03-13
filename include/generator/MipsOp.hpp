#ifndef MIPS_OP_HPP
#define MIPS_OP_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsOp : public MipsStatement {
public:
    MipsOp(std::string opName, int dest, int arg1, int arg2)
        : opName(opName), dest(dest), arg1(arg1), arg2(arg2)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << opName << " " << MipsUtil::toRegister(dest) << " ";
        ss << MipsUtil::toRegister(arg1) << " ";
        ss << MipsUtil::toRegister(arg2) << "\n";
        return ss.str();
    }

    int getDestinationRegister() const {
        return dest;
    }

    int getArg1Register() const {
        return arg1;
    }

    int getArg2Register() const {
        return arg2;
    }

protected:
    std::string opName;
    int dest;
    int arg1;
    int arg2;
};

#endif
