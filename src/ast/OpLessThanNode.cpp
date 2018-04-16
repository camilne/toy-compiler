#include "ast/OpLessThanNode.hpp"

std::string OpLessThanNode::toCode() const {
    std::string code;

    if(leftExp)
        code += leftExp->toCode();

    code += " < ";

    if(rightExp)
        code += rightExp->toCode();

    return code;
}
