#include "ast/OpDivideNode.hpp"

std::string OpDivideNode::toCode() const {
    std::string code;

    if(leftExp)
        code += leftExp->toCode();

    code += " / ";

    if(rightExp)
        code += rightExp->toCode();

    return code;
}
