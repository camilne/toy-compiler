#include "generator/MipsGenerator.hpp"
#include "ast/IdentifierNode.hpp"
#include "ast/IntegerNode.hpp"
#include "ast/OpMinusNode.hpp"
#include "ast/OpPlusNode.hpp"
#include "ast/StatementsNode.hpp"

void MipsGenerator::generate(IdentifierNode& node) {
    code += node.getName();    
}

void MipsGenerator::generate(IntegerNode& node) {
    code += std::to_string(node.getValue());
}

void MipsGenerator::generate(OpMinusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    code += " - ";
    if(node.getRightExp())
        node.getRightExp()->accept(*this);
}

void MipsGenerator::generate(OpPlusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    code += " + ";
    if(node.getRightExp())
        node.getRightExp()->accept(*this);
}

void MipsGenerator::generate(StatementsNode& node) {
    if(node.getStatements())
        node.getStatements()->accept(*this);
    if(node.getStatement()) {
        node.getStatement()->accept(*this);
        code += ";\n";
    }
}
