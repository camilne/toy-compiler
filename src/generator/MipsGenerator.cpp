#include "generator/MipsGenerator.hpp"
#include "generator/MipsUtil.hpp"
#include "ast/IdentifierNode.hpp"
#include "ast/InitNode.hpp"
#include "ast/IntegerNode.hpp"
#include "ast/OpMinusNode.hpp"
#include "ast/OpPlusNode.hpp"
#include "ast/StatementsNode.hpp"

void MipsGenerator::generate(IdentifierNode& node) {
    code += MipsUtil::comment(node.toCode());

    code += node.getName();
}

void MipsGenerator::generate(InitNode& node) {
    code += MipsUtil::comment(node.toCode());

    code += ".text\n";
    if(node.getStatements())
        node.getStatements()->accept(*this);
}

void MipsGenerator::generate(IntegerNode& node) {
    code += MipsUtil::comment(node.toCode());

    // TODO: better register allocation.
    code += MipsUtil::loadImmediate(getTmp(nextTmp()), node.getValue());
}

void MipsGenerator::generate(OpMinusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    code += MipsUtil::comment(node.toCode());

    code += MipsUtil::sub(getTmpOffset(-1),
                          getTmpOffset(-1),
                          getTmpOffset(0));
    previousTmp();
}

void MipsGenerator::generate(OpPlusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    code += MipsUtil::comment(node.toCode());

    code += MipsUtil::add(getTmpOffset(-1),
                          getTmpOffset(-1),
                          getTmpOffset(0));
    previousTmp();
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

std::string MipsGenerator::getTmp(int val) {
    if(val < 0 || val > 3)
        return "INVALID(" + std::to_string(val) + ")";
    return "$t" + std::to_string(val);
}

std::string MipsGenerator::getTmpOffset(int off) {
    if(tmpRegCounter + off >= 0 && tmpRegCounter + off <= 3)
        return getTmp(tmpRegCounter + off);

    if(off >= -3)
        return getTmp(tmpRegCounter + off + 4);

    // Fix to pop off stack
    return getTmp(55);
}

int MipsGenerator::previousTmp() {
    if(--tmpRegCounter < 0) {
        tmpRegCounter = 3;
        code += MipsUtil::pop(getTmp(tmpRegCounter));
    }
    return tmpRegCounter;
}

int MipsGenerator::nextTmp() {
    if(++tmpRegCounter > 3) {
        tmpRegCounter = 0;
        code += MipsUtil::push(getTmp(tmpRegCounter));
    }
    return tmpRegCounter;
}
