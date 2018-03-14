#include "generator/MipsGenerator.hpp"
#include "generator/MipsUtil.hpp"
#include "ast/SyntaxTreeNodes.ih"
#include <sstream>
#include <iostream>

void MipsGenerator::generate(AssignmentNode& node) {
    add(std::make_shared<MipsComment>(node.toCode()));

    if(!node.getExpression()) {
        std::cerr << "Assignment has no expression: " << node.toCode() << std::endl;
        return;
    }

    node.getExpression()->accept(*this);

    if(!node.getIdentifier()) {
        std::cerr << "Assignment has no identifier: " << node.toCode() << std::endl;
        return;
    }

    std::string identifier = node.getIdentifier()->getName();

    variables[identifier] = 0;

    auto addr = nextSaveAndPush();
    add(std::make_shared<MipsLoadAddress>(addr, identifier));
    add(std::make_shared<MipsStore>(getTmpOffset(0), addr));
}

void MipsGenerator::generate(IdentifierNode& node) {
    add(std::make_shared<MipsComment>("Identifier " + node.toCode()));

    std::string name = node.getName();

    if(variables.find(name) == variables.end()) {
        std::cerr << "Identifier [" << name << "] has not been declared" << std::endl;
        return;
    }

    auto addr = nextSaveAndPush();
    add(std::make_shared<MipsLoadAddress>(addr, name));
    auto dest = nextTmpAndPush();
    add(std::make_shared<MipsLoad>(dest, addr));
}

void MipsGenerator::generate(InitNode& node) {
    add(std::make_shared<MipsComment>(node.toCode()));

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
    else {
        add(std::make_shared<MipsComment>("No expression in print"));
        return;
    }

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
        ss << ".data\n";
        for(std::pair<std::string, int> identifier : variables) {
            ss << identifier.first << ": .word 0\n";
        }
        ss << ".text\n";
        for(std::shared_ptr<MipsStatement>& statement : mipsStatements) {
            ss << statement->toCode();
        }
        code += ss.str();
        isCodeGenerated = true;
    }

    return code;
}

int MipsGenerator::getRegOffset(int& reg, int off, int begin, int end) {
    if(reg + off >= begin && reg + off < end)
        return reg + off;

    const int RANGE = end - begin;
    if(off < 0 && off > -RANGE)
        return reg + off + RANGE;

    // Fix to pop off stack
    return -55;
}

int MipsGenerator::previousReg(int& reg, int begin, int end) {
    if(--reg < begin) {
        reg = end - 1;
    }
    return reg;
}

int MipsGenerator::previousRegAndPop(int& reg, int begin, int end) {
    if(regUse[reg] > 1) {
        add(std::make_shared<MipsPop>(reg));
        regUse[reg]--;
    }
    if(--reg < begin) {
        reg = end - 1;
    }
    return reg;
}

int MipsGenerator::nextReg(int& reg, int begin, int end) {
    if(++reg >= end) {
        reg = begin;
    }
    return reg;
}

int MipsGenerator::nextRegAndPush(int& reg, int begin, int end) {
    if(++reg >= end) {
        reg = begin;
    }
    if(regUse[reg]) {
        add(std::make_shared<MipsPush>(reg));
    }
    regUse[reg]++;
    return reg;
}

int MipsGenerator::getTmpOffset(int off) {
    return getRegOffset(tmpRegCounter, off, MipsUtil::TMP_BEGIN, MipsUtil::TMP_END);
}

int MipsGenerator::previousTmp() {
    return previousReg(tmpRegCounter, MipsUtil::TMP_BEGIN, MipsUtil::TMP_END);
}

int MipsGenerator::previousTmpAndPop() {
    return previousRegAndPop(tmpRegCounter, MipsUtil::TMP_BEGIN, MipsUtil::TMP_END);
}

int MipsGenerator::nextTmp() {
    return nextReg(tmpRegCounter, MipsUtil::TMP_BEGIN, MipsUtil::TMP_END);
}

int MipsGenerator::nextTmpAndPush() {
    return nextRegAndPush(tmpRegCounter, MipsUtil::TMP_BEGIN, MipsUtil::TMP_END);
}

int MipsGenerator::getSaveOffset(int off) {
    return getRegOffset(saveRegCounter, off, MipsUtil::SAVE_BEGIN, MipsUtil::SAVE_END);
}

int MipsGenerator::previousSave() {
    return previousReg(saveRegCounter, MipsUtil::SAVE_BEGIN, MipsUtil::SAVE_END);
}

int MipsGenerator::previousSaveAndPop() {
    return previousRegAndPop(saveRegCounter, MipsUtil::SAVE_BEGIN, MipsUtil::SAVE_END);
}

int MipsGenerator::nextSave() {
    return nextReg(saveRegCounter, MipsUtil::SAVE_BEGIN, MipsUtil::SAVE_END);
}

int MipsGenerator::nextSaveAndPush() {
    return nextRegAndPush(saveRegCounter, MipsUtil::SAVE_BEGIN, MipsUtil::SAVE_END);
}

void MipsGenerator::add(std::shared_ptr<MipsStatement>&& statement) {
    // Ignore if it is a comment statement
    if(!debug && std::dynamic_pointer_cast<MipsComment>(statement))
        return;

    mipsStatements.emplace_back(statement);
}
