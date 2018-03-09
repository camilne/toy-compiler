#include "generator/MipsGenerator.hpp"
#include "generator/MipsUtil.hpp"
#include "ast/IdentifierNode.hpp"
#include "ast/InitNode.hpp"
#include "ast/IntegerNode.hpp"
#include "ast/OpMinusNode.hpp"
#include "ast/OpPlusNode.hpp"
#include "ast/StatementsNode.hpp"

void MipsGenerator::generate(IdentifierNode& node) {
    code += node.getName();
}

void MipsGenerator::generate(InitNode& node) {
    code += ".text\n";
    if(node.getStatements())
        node.getStatements()->accept(*this);
}

void MipsGenerator::generate(IntegerNode& node) {
    // TODO: better register allocation. bounds checks.
    // TODO: push registers to stack if full
    code += MipsUtil::loadImmediate("$t" + std::to_string(tmpRegCounter++), node.getValue());
}

void MipsGenerator::generate(OpMinusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    code += MipsUtil::sub("$t" + std::to_string(tmpRegCounter-2),
                          "$t" + std::to_string(tmpRegCounter-2),
                          "$t" + std::to_string(tmpRegCounter-1));
    tmpRegCounter--;
}

void MipsGenerator::generate(OpPlusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    code += MipsUtil::add("$t" + std::to_string(tmpRegCounter-2),
                          "$t" + std::to_string(tmpRegCounter-2),
                          "$t" + std::to_string(tmpRegCounter-1));
    tmpRegCounter--;
}

void MipsGenerator::generate(StatementsNode& node) {
    if(node.getStatements())
        node.getStatements()->accept(*this);
    if(node.getStatement()) {
        //code += MipsUtil::newFrame();
        node.getStatement()->accept(*this);
        //code += MipsUtil::popFrame();
    }
}
