#include "ast/OpLessThanEqualNode.hpp"

std::string OpLessThanEqualNode::toCode() const {
    std::string code;

    if(leftExp)
        code += leftExp->toCode();

    code += " <= ";

    if(rightExp)
        code += rightExp->toCode();

    return code;
}
