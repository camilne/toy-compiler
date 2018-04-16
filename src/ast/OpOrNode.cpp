#include "ast/OpOrNode.hpp"

std::string OpOrNode::toCode() const {
    std::string code;

    if(leftExp)
        code += leftExp->toCode();

    code += " || ";

    if(rightExp)
        code += rightExp->toCode();

    return code;
}
