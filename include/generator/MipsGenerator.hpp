#ifndef MIPS_GENERATOR_HPP
#define MIPS_GENERATOR_HPP

#include "generator/IGenerator.hpp"
#include "generator/MipsStatements.ih"
#include <vector>
#include <memory>

/**
Generates mips32 code from a {@link SyntaxTree}.

Uses the visitor pattern to visit every node and generate separate code for each.
*/
class MipsGenerator : public IGenerator {
public:
    MipsGenerator()
        : tmpRegCounter(MipsUtil::TMP_BEGIN)
    {
        tmpUse.resize(NUM_TMP_REGISTERS);
        for(int& i : tmpUse) {
            i = 0;
        }
    }

    virtual void generate(IdentifierNode& node) override;
    virtual void generate(InitNode&       node) override;
    virtual void generate(IntegerNode&    node) override;
    virtual void generate(OpDivideNode&   node) override;
    virtual void generate(OpMinusNode&    node) override;
    virtual void generate(OpMultiplyNode& node) override;
    virtual void generate(OpPlusNode&     node) override;
    virtual void generate(PrintNode&      node) override;
    virtual void generate(StatementsNode& node) override;

    virtual const std::string& getCode() override;

private:
    /// The number of tmp registers on a mips machine.
    static const int NUM_TMP_REGISTERS = 8;

    /// Holds the current tmp register for operations.
    int tmpRegCounter;
    /// Holds the number of times that each tmp register has been pushed to the stack for a block.
    std::vector<int> tmpUse;
    /// Holds the statements in the program in order of the output file.
    std::vector<std::unique_ptr<MipsStatement>> mipsStatements;

    /**
    Return the tmp register offset from <tt>tmpRegCounter</tt>. The offset will wrap around the registers if it goes out of range.

    @param off The offset to tmpRegCounter.
    @return the register number.
    */
    int getTmpOffset(int off);
    /**
    Return the previous tmp register number of <tt>tmpRegCounter</tt> with wrap-around.

    @return the previous (lower numbered) register number.
    */
    int previousTmp();
    /**
    Pop the current register number off the stack then return the previous tmp register number of <tt>tmpRegCounter</tt> with wrap-around.

    @return the previous (lower numbered) register number.
    */
    int previousTmpAndPop();
    /**
    Return the next tmp register number of <tt>tmpRegCounter</tt> with wrap-around.

    @return the next (higher numbered) register number.
    */
    int nextTmp();
    /**
    Return the next tmp register number of <tt>tmpRegCounter</tt> with wrap-around then push the current tmp register to the stack.

    @return the next (higher numbered) register number.
    */
    int nextTmpAndPush();
    /**
    Append a mips statement to the end of the current statements.

    @param statement An instance of the statement to add.
    */
    void add(std::unique_ptr<MipsStatement>&& statement);

};

#endif
