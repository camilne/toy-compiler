#include "generator/MipsGenerator.hpp"
#include "generator/MipsUtil.hpp"
#include "ast/SyntaxTreeNodes.ih"
#include <sstream>
#include <iostream>

void MipsGenerator::generate(IdentifierNode& node) {
    add(std::make_unique<MipsComment>(node.toCode()));

    //code += node.getName();
}

void MipsGenerator::generate(InitNode& node) {
    add(std::make_unique<MipsComment>(node.toCode()));

    code += ".text\n";
    if(node.getStatements())
        node.getStatements()->accept(*this);
}

void MipsGenerator::generate(IntegerNode& node) {
    add(std::make_unique<MipsComment>("Integer " + node.toCode()));

    // TODO: better register allocation.
    auto reg = nextTmpAndPush();
    add(std::make_unique<MipsLoadImmediate>(reg, node.getValue()));
}

void MipsGenerator::generate(OpDivideNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    add(std::make_unique<MipsComment>(node.toCode()));

    addOpForCurrentTmp<MipsDivide>();
    previousTmpAndPop();
}

void MipsGenerator::generate(OpMinusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    add(std::make_unique<MipsComment>(node.toCode()));

    addOpForCurrentTmp<MipsMinus>();
    previousTmpAndPop();
}

void MipsGenerator::generate(OpMultiplyNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    add(std::make_unique<MipsComment>(node.toCode()));

    addOpForCurrentTmp<MipsMultiply>();
    previousTmpAndPop();
}

void MipsGenerator::generate(OpPlusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    add(std::make_unique<MipsComment>(node.toCode()));

    addOpForCurrentTmp<MipsAdd>();
    previousTmpAndPop();
}

void MipsGenerator::generate(PrintNode& node) {
    add(std::make_unique<MipsComment>(node.toCode()));

    if(node.getExp())
        node.getExp()->accept(*this);
    else
        add(std::make_unique<MipsComment>("No expression in print"));

    // print int
    add(std::make_unique<MipsSysCall<std::string>>(1, MipsUtil::toRegister(tmpRegCounter)));

    // print newline
    add(std::make_unique<MipsSysCall<int>>(11, 10));
}

void MipsGenerator::generate(StatementsNode& node) {
    if(node.getStatements())
        node.getStatements()->accept(*this);
    if(node.getStatement())
        node.getStatement()->accept(*this);
}

const std::string& MipsGenerator::getCode() {
    static bool isCodeGenerated = false;

    if(!isCodeGenerated) {
        std::stringstream ss;
        for(std::unique_ptr<MipsStatement>& statement : mipsStatements) {
            ss << statement->toCode();
        }
        code += ss.str();
        isCodeGenerated = true;
    }

    return code;
}

int MipsGenerator::getTmpOffset(int off) {
    if(tmpRegCounter + off >= MipsUtil::TMP_BEGIN && tmpRegCounter + off < MipsUtil::TMP_END)
        return tmpRegCounter + off;

    if(off > -NUM_TMP_REGISTERS)
        return tmpRegCounter + off + NUM_TMP_REGISTERS;

    // Fix to pop off stack
    return 55;
}

int MipsGenerator::previousTmp() {
    if(--tmpRegCounter < MipsUtil::TMP_BEGIN) {
        tmpRegCounter = MipsUtil::TMP_END - 1;
    }
    return tmpRegCounter;
}

int MipsGenerator::previousTmpAndPop() {
    if(tmpUse[tmpRegCounter - MipsUtil::TMP_BEGIN] > 1) {
        add(std::make_unique<MipsPop>(tmpRegCounter));
        tmpUse[tmpRegCounter - MipsUtil::TMP_BEGIN]--;
    }
    if(--tmpRegCounter < MipsUtil::TMP_BEGIN) {
        tmpRegCounter = MipsUtil::TMP_END - 1;
    }
    return tmpRegCounter;
}

int MipsGenerator::nextTmp() {
    if(++tmpRegCounter >= MipsUtil::TMP_END) {
        tmpRegCounter = MipsUtil::TMP_BEGIN;
    }
    return tmpRegCounter;
}

int MipsGenerator::nextTmpAndPush() {
    if(++tmpRegCounter >= MipsUtil::TMP_END) {
        tmpRegCounter = MipsUtil::TMP_BEGIN;
    }
    if(tmpUse[tmpRegCounter - MipsUtil::TMP_BEGIN]) {
        add(std::make_unique<MipsPush>(tmpRegCounter));
    }
    tmpUse[tmpRegCounter - MipsUtil::TMP_BEGIN]++;
    return tmpRegCounter;
}

void MipsGenerator::add(std::unique_ptr<MipsStatement>&& statement) {
    mipsStatements.emplace_back(std::move(statement));
}
