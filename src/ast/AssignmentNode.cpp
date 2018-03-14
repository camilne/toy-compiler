#include "ast/AssignmentNode.hpp"

std::string AssignmentNode::toCode() const {
    std::string code;

    if(lhs)
        code += lhs->toCode();

    code += " = ";

    if(rhs)
        code += rhs->toCode();

    return code;
}
