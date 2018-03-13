#include "generator/MipsGenerator.hpp"
#include "generator/MipsUtil.hpp"
#include "ast/SyntaxTreeNodes.ih"
#include <sstream>
#include <iostream>

void MipsGenerator::generate(IdentifierNode& node) {
    add(std::make_shared<MipsComment>(node.toCode()));

    //code += node.getName();
}

void MipsGenerator::generate(InitNode& node) {
    add(std::make_shared<MipsComment>(node.toCode()));

    code += ".text\n";
    if(node.getStatements())
        node.getStatements()->accept(*this);
}

void MipsGenerator::generate(IntegerNode& node) {
    add(std::make_shared<MipsComment>("Integer " + node.toCode()));

    // TODO: better register allocation.
    auto reg = nextTmpAndPush();
    add(std::make_shared<MipsLoadImmediate>(reg, node.getValue()));
}

void MipsGenerator::generate(OpDivideNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    add(std::make_shared<MipsComment>(node.toCode()));

    addOpForCurrentTmp<MipsDivide>();
    previousTmpAndPop();
}

void MipsGenerator::generate(OpMinusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    add(std::make_shared<MipsComment>(node.toCode()));

    addOpForCurrentTmp<MipsMinus>();
    previousTmpAndPop();
}

void MipsGenerator::generate(OpMultiplyNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    add(std::make_shared<MipsComment>(node.toCode()));

    addOpForCurrentTmp<MipsMultiply>();
    previousTmpAndPop();
}

void MipsGenerator::generate(OpPlusNode& node) {
    if(node.getLeftExp())
        node.getLeftExp()->accept(*this);
    if(node.getRightExp())
        node.getRightExp()->accept(*this);

    add(std::make_shared<MipsComment>(node.toCode()));

    addOpForCurrentTmp<MipsAdd>();
    previousTmpAndPop();
}

void MipsGenerator::generate(PrintNode& node) {
    add(std::make_shared<MipsComment>(node.toCode()));

    if(node.getExp())
        node.getExp()->accept(*this);
    else
        add(std::make_shared<MipsComment>("No expression in print"));

    // print int
    add(std::make_shared<MipsSysCall<std::string>>(1, MipsUtil::toRegister(tmpRegCounter)));

    // print newline
    add(std::make_shared<MipsSysCall<int>>(11, 10));
}

void MipsGenerator::generate(StatementsNode& node) {
    if(node.getStatements())
        node.getStatements()->accept(*this);
    if(node.getStatement())
        node.getStatement()->accept(*this);
}

void MipsGenerator::optimize() {
    // Remove trailing pops if register is unused after
    std::vector<int> popRegisters(NUM_REGISTERS);
    for(auto& i : popRegisters)
        i = 0;

    for(auto it = mipsStatements.rbegin(); it != mipsStatements.rend(); ++it) {
        std::shared_ptr<MipsStatement> obj = *it;
        if(std::shared_ptr<MipsPop> pop = std::dynamic_pointer_cast<MipsPop>(obj)) {
            if(pop->getRegister() < popRegisters.size()) {
                if(!popRegisters[pop->getRegister()]) {
                    mipsStatements.erase(std::next(it).base());
                    --it;
                } else {
                    --popRegisters[pop->getRegister()];
                }
            }
        } else if(std::shared_ptr<MipsPush> push = std::dynamic_pointer_cast<MipsPush>(obj)) {
            if(push->getRegister() < popRegisters.size())
                ++popRegisters[push->getRegister()];
        } else if(std::shared_ptr<MipsOp> op = std::dynamic_pointer_cast<MipsOp>(obj)) {
            if(op->getArg1Register() < popRegisters.size())
                ++popRegisters[op->getArg1Register()];
            if(op->getArg2Register() < popRegisters.size())
                ++popRegisters[op->getArg2Register()];
        }
    }
}

const std::string& MipsGenerator::getCode() {
    static bool isCodeGenerated = false;

    if(!isCodeGenerated) {
        std::stringstream ss;
        for(std::shared_ptr<MipsStatement>& statement : mipsStatements) {
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
        add(std::make_shared<MipsPop>(tmpRegCounter));
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
        add(std::make_shared<MipsPush>(tmpRegCounter));
    }
    tmpUse[tmpRegCounter - MipsUtil::TMP_BEGIN]++;
    return tmpRegCounter;
}

void MipsGenerator::add(std::shared_ptr<MipsStatement>&& statement) {
    // Ignore if it is a comment statement
    if(!debug && std::dynamic_pointer_cast<MipsComment>(statement))
        return;

    mipsStatements.emplace_back(statement);
}
