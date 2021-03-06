#include "ast/OpMinusNode.hpp"

std::string OpMinusNode::toCode() const {
    std::string code;

    if(leftExp)
        code += leftExp->toCode();

    code += " - ";

    if(rightExp)
        code += rightExp->toCode();

    return code;
}
