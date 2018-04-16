#include "ast/OpInequalityNode.hpp"

std::string OpInequalityNode::toCode() const {
    std::string code;

    if(leftExp)
        code += leftExp->toCode();

    code += " != ";

    if(rightExp)
        code += rightExp->toCode();

    return code;
}
