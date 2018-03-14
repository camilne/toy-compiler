#include "ast/WhileNode.hpp"

std::string WhileNode::toCode() const {
    std::string code;

    code += "while(";

    if(exp) {
        code += exp->toCode();
    }

    code += ") {\n";

    if(statements)
        code += statements->toCode();

    code += "\n}";

    return code;
}
