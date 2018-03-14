#ifndef MIPS_JUMP_HPP
#define MIPS_JUMP_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsJump : public MipsStatement {
public:
    explicit MipsJump(std::string name)
        : name(name)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "j " << name << "\n";
        return ss.str();
    }

    std::string getName() const {
        return name;
    }

private:
    std::string name;
};

#endif
