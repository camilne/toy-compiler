#include "ast/OpMultiplyNode.hpp"

std::string OpMultiplyNode::toCode() const {
    std::string code;

    if(leftExp)
        code += leftExp->toCode();

    code += " * ";

    if(rightExp)
        code += rightExp->toCode();

    return code;
}
