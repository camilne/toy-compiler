#ifndef MIPS_COMMENT_HPP
#define MIPS_COMMENT_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

class MipsComment : public MipsStatement {
public:
    MipsComment(std::string content)
        : content(content)
    {}

    virtual std::string toCode() const override {
        std::stringstream ss;
        ss << "# " << content << "\n";
        return ss.str();
    }

private:
    std::string content;
};

#endif
