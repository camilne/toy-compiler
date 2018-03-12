#ifndef MIPS_LOAD_IMMEDIATE_HPP
#define MIPS_LOAD_IMMEDIATE_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsLoadImmediate : public MipsStatement {
public:
    MipsLoadImmediate(int dest, int imm)
        : dest(dest), imm(imm)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "li " << MipsUtil::toRegister(dest) << " " << imm << "\n";
        return ss.str();
    }

private:
    int dest;
    int imm;
};

#endif
