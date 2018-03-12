#ifndef MIPS_SYS_CALL_HPP
#define MIPS_SYS_CALL_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

template <typename Arg>
class MipsSysCall : public MipsStatement {
public:
    MipsSysCall(int func, Arg arg)
        : func(func), arg(arg)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "li $v0 " << func << "\n";
        ss << loadArg(arg) << "\n";
        ss << "syscall\n";
        return ss.str();
    }

private:
    int func;
    Arg arg;

    std::string loadArg(int val) const {
        return "li $a0 " + std::to_string(val);
    }

    std::string loadArg(std::string val) const {
        return "add $a0 $zero " + val;
    }

};

#endif
