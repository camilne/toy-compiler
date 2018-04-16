#include "ast/OpEqualityNode.hpp"

std::string OpEqualityNode::toCode() const {
    std::string code;

    if(leftExp)
        code += leftExp->toCode();

    code += " == ";

    if(rightExp)
        code += rightExp->toCode();

    return code;
}
