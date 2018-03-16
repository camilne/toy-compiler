#include "generator/MipsGenerator.hpp"
#include "generator/MipsUtil.hpp"
#include "ast/SyntaxTreeNodes.ih"
#include <sstream>
#include <iostream>

// static
const std::string MipsGenerator::IDENTIFIER_PREFIX = "__identifier__";
// static
const std::string MipsGenerator::LABEL_PREFIX = "__label__";

void MipsGenerator::generate(AssignmentNode& node) {
    add(std::make_shared<MipsComment>(node.toCode()));

    if(!node.getExpression()) {
        std::cerr << "Assignment has no expression: " << node.toCode() << std::endl;
        return;
    }

    if(!node.getIdentifier()) {
        std::cerr << "Assignment has no identifier: " << node.toCode() << std::endl;
        return;
    }

    node.getExpression()->accept(*this);

    std::string identifier = IDENTIFIER_PREFIX + node.getIdentifier()->getName();

    variables[identifier] = 0;

    auto addr = getAddrOfIdentifier(identifier);
    add(std::make_shared<MipsStore>(getTmpOffset(0), addr));
}

void MipsGenerator::generate(IdentifierNode& node) {
    add(std::make_shared<MipsComment>("Identifier " + node.toCode()));

    std::string identifier = IDENTIFIER_PREFIX + node.getName();

    if(variables.find(identifier) == variables.end()) {
        std::cerr << "Identifier [" << identifier << "] has not been declared" << std::endl;
        return;
    }

    auto addr = getAddrOfIdentifier(identifier);
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

void MipsGenerator::generate(WhileNode& node) {
    add(std::make_shared<MipsComment>(node.toCode()));

    if(!node.getExpression()) {
        add(std::make_shared<MipsComment>("No expression in while"));
        return;
    }

    std::string whileId = uniqueId();
    std::string whileTop = LABEL_PREFIX + "while_top_" + whileId;
    std::string whileEnd = LABEL_PREFIX + "while_end_" + whileId;

    add(std::make_shared<MipsLabel>(whileTop));
    node.getExpression()->accept(*this);
    add(std::make_shared<MipsBranchEqual>(tmpRegCounter, 0, whileEnd));
    if(node.getStatements())
        node.getStatements()->accept(*this);
    add(std::make_shared<MipsJump>(whileTop));
    add(std::make_shared<MipsLabel>(whileEnd));
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

int MipsGenerator::getAddrOfIdentifier(std::string identifier) {
    for(unsigned int i = 0; i < savedVariableMapping.size(); i++)
        if(savedVariableMapping[i] == identifier)
            return i;

    auto addr = nextSaveAndPush();
    add(std::make_shared<MipsLoadAddress>(addr, identifier));
    savedVariableMapping[addr] = identifier;

    return addr;
}

std::string MipsGenerator::uniqueId() {
    static int currentId = 1;
    static const char ALPHABET[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z'
    };
    static const int ALPHABET_LENGTH = sizeof(ALPHABET) / sizeof(char);

    std::vector<char> encoded;
    int id = currentId++;

    do {
        encoded.push_back(ALPHABET[id % ALPHABET_LENGTH]);
        id /= ALPHABET_LENGTH;
    } while(id > 0);

    return std::string(encoded.begin(), encoded.end());
}
