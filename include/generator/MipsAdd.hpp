#ifndef MIPS_ADD_HPP
#define MIPS_ADD_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsAdd : public MipsStatement {
public:
    MipsAdd(int dest, int arg1, int arg2)
        : dest(dest), arg1(arg1), arg2(arg2)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "add " << MipsUtil::toRegister(dest) << " ";
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
