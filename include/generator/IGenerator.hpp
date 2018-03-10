#ifndef I_GENERATOR_HPP
#define I_GENERATOR_HPP

#include <string>

class IdentifierNode;
class InitNode;
class IntegerNode;
class OpMinusNode;
class OpPlusNode;
class PrintNode;
class StatementsNode;

class IGenerator {
public:
    virtual void generate(IdentifierNode& node) = 0;
    virtual void generate(InitNode&       node) = 0;
    virtual void generate(IntegerNode&    node) = 0;
    virtual void generate(OpMinusNode&    node) = 0;
    virtual void generate(OpPlusNode&     node) = 0;
    virtual void generate(PrintNode&      node) = 0;
    virtual void generate(StatementsNode& node) = 0;

    const std::string& getCode() const {
        return code;
    }

protected:
    std::string code;
};

#endif
