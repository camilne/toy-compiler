#include "ast/IfNode.hpp"

std::string IfNode::toCode() const {
    std::string code;

    code += "if(";

    if(exp) {
        code += exp->toCode();
    }

    code += ") {\n";

    if(statements)
        code += statements->toCode();

    code += "\n}";

    return code;
}
