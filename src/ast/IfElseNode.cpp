#include "ast/IfElseNode.hpp"

std::string IfElseNode::toCode() const {
    std::string code;

    code += "if(";

    if(exp) {
        code += exp->toCode();
    }

    code += ") {\n";

    if(statements)
        code += statements->toCode();

    code += "\n} else {\n";

    if(elseStatements)
      code += elseStatements->toCode();

    code += "\n}";

    return code;
}
