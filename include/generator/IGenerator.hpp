#ifndef I_GENERATOR_HPP
#define I_GENERATOR_HPP

#include <string>

class AssignmentNode;
class IdentifierNode;
class InitNode;
class IntegerNode;
class OpDivideNode;
class OpMinusNode;
class OpMultiplyNode;
class OpPlusNode;
class PrintNode;
class StatementsNode;
class WhileNode;

class IGenerator {
public:
    virtual void generate(AssignmentNode& node) = 0;
    virtual void generate(IdentifierNode& node) = 0;
    virtual void generate(InitNode&       node) = 0;
    virtual void generate(IntegerNode&    node) = 0;
    virtual void generate(OpDivideNode&   node) = 0;
    virtual void generate(OpMinusNode&    node) = 0;
    virtual void generate(OpMultiplyNode& node) = 0;
    virtual void generate(OpPlusNode&     node) = 0;
    virtual void generate(PrintNode&      node) = 0;
    virtual void generate(StatementsNode& node) = 0;
    virtual void generate(WhileNode&      node) = 0;

    virtual std::string getCode() = 0;
};

#endif
