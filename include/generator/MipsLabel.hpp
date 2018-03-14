#ifndef MIPS_LABEL_HPP
#define MIPS_LABEL_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsLabel : public MipsStatement {
public:
    explicit MipsLabel(std::string name)
        : name(name)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << name << ":\n";
        return ss.str();
    }

    std::string getName() const {
        return name;
    }

private:
    std::string name;
};

#endif
