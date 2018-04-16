#ifndef I_GENERATOR_HPP
#define I_GENERATOR_HPP

#include <string>

class AssignmentNode;
class IdentifierNode;
class IfNode;
class IfElseNode;
class InitNode;
class IntegerNode;
class OpDivideNode;
class OpEqualityNode;
class OpGreaterThanEqualNode;
class OpGreaterThanNode;
class OpInequalityNode;
class OpLessThanEqualNode;
class OpLessThanNode;
class OpMinusNode;
class OpMultiplyNode;
class OpOrNode;
class OpPlusNode;
class PrintNode;
class StatementsNode;
class WhileNode;

class IGenerator {
public:
    virtual void generate(AssignmentNode& node) = 0;
    virtual void generate(IdentifierNode& node) = 0;
    virtual void generate(IfNode&         node) = 0;
    virtual void generate(IfElseNode&     node) = 0;
    virtual void generate(InitNode&       node) = 0;
    virtual void generate(IntegerNode&    node) = 0;
    virtual void generate(OpDivideNode&   node) = 0;
    virtual void generate(OpEqualityNode& node) = 0;
    virtual void generate(OpGreaterThanEqualNode& node) = 0;
    virtual void generate(OpGreaterThanNode& node) = 0;
    virtual void generate(OpInequalityNode& node) = 0;
    virtual void generate(OpLessThanEqualNode& node) = 0;
    virtual void generate(OpLessThanNode& node) = 0;
    virtual void generate(OpMinusNode&    node) = 0;
    virtual void generate(OpMultiplyNode& node) = 0;
    virtual void generate(OpOrNode&       node) = 0;
    virtual void generate(OpPlusNode&     node) = 0;
    virtual void generate(PrintNode&      node) = 0;
    virtual void generate(StatementsNode& node) = 0;
    virtual void generate(WhileNode&      node) = 0;

    virtual std::string getCode() = 0;
};

#endif
