#ifndef MIPS_GENERATOR_HPP
#define MIPS_GENERATOR_HPP

#include "generator/IGenerator.hpp"

class MipsGenerator : public IGenerator {
public:
    virtual void generate(IdentifierNode& node) override;
    virtual void generate(IntegerNode&    node) override;
    virtual void generate(OpMinusNode&    node) override;
    virtual void generate(OpPlusNode&     node) override;
    virtual void generate(StatementsNode& node) override;
};

#endif
