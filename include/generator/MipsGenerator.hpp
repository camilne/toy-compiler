#ifndef MIPS_GENERATOR_HPP
#define MIPS_GENERATOR_HPP

#include "generator/IGenerator.hpp"

/**
Generates mips32 code from a {@link SyntaxTree}.

Uses the visitor pattern to visit every node and generate separate code for each.
*/
class MipsGenerator : public IGenerator {
public:
    MipsGenerator()
        : tmpRegCounter(0)
    {}

    virtual void generate(IdentifierNode& node) override;
    virtual void generate(InitNode&       node) override;
    virtual void generate(IntegerNode&    node) override;
    virtual void generate(OpDivideNode&   node) override;
    virtual void generate(OpMinusNode&    node) override;
    virtual void generate(OpMultiplyNode& node) override;
    virtual void generate(OpPlusNode&     node) override;
    virtual void generate(PrintNode&      node) override;
    virtual void generate(StatementsNode& node) override;

private:
    /// Holds the current tmp register for operations.
    int tmpRegCounter;
    /// Holds the number of times that each tmp register has been pushed to the stack for a block.
    int tmpUse[4] = {0, 0, 0, 0};

    /**
    Return the string value of the tmp register number.

    @param val This is the number of the tmp register to return. Valid if <tt>val >= 0</tt> and <tt>val < NUM_TMPS</tt>.
    @return "$t#" where # is <tt>val</tt> if valid. "INVALID(val)" otherwise.
    */
    std::string getTmp(int val);
    /**
    Return the string value of the tmp regsiter offset from <tt>tmpRegCounter</tt>. The offset will wrap around the registers if it goes out of range.

    @param off The offset to tmpRegCounter.
    @return "$t#" where # is the register number.
    */
    std::string getTmpOffset(int off);
    /**
    Return the previous tmp register number to <tt>tmpRegCounter</tt> with wrap-around.

    @return the previous (lower numbered) register number.
    */
    int previousTmp();
    /**
    Pop the current register number off the stack then return the previous tmp register number to <tt>tmpRegCounter</tt> with wrap-around.

    @return the previous (lower numbered) register number.
    */
    int previousTmpAndPop();
    /**
    Return the next tmp register number to <tt>tmpRegCounter</tt> with wrap-around.

    @return the next (higher numbered) register number.
    */
    int nextTmp();
    /**
    Return the next tmp register number to <tt>tmpRegCounter</tt> with wrap-around then push the current tmp register to the stack.

    @return the next (higher numbered) register number.
    */
    int nextTmpAndPush();
};

#endif
