#include "ast/StatementsNode.hpp"

std::string StatementsNode::toCode() const {
    std::string code;

    if(statements) {
        code += statements->toCode();
        code += "\n";
    }

    if(statement)
        code += statement->toCode();

    code += ";";

    return code;
}
