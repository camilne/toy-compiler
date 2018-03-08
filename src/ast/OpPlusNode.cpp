#include "ast/OpPlusNode.hpp"

std::string OpPlusNode::toCode() const {
    std::string code;

    if(leftExp)
        code += leftExp->toCode();

    code += " + ";

    if(rightExp)
        code += rightExp->toCode();

    return code;
}
