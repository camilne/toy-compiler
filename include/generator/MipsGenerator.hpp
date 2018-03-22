#ifndef MIPS_GENERATOR_HPP
#define MIPS_GENERATOR_HPP

#include "generator/IGenerator.hpp"
#include "generator/MipsStatements.ih"
#include "generator/MipsDefines.hpp"
#include <vector>
#include <memory>
#include <unordered_map>
#include <unordered_set>
#include <string>

namespace mips {
  /**
  Generates mips32 code from a {@link SyntaxTree}.

  Uses the visitor pattern to visit every node and generate separate code for each.
  */
  class MipsGenerator : public IGenerator {
  public:
      explicit MipsGenerator(bool debug = false)
          : debug(debug), saveRegCounter(SAVE_BEGIN), tmpRegCounter(TMP_BEGIN)
      {
          regUse.resize(NUM_REGISTERS);
          for(int& i : regUse) {
              i = 0;
          }

          savedVariableMapping.resize(NUM_REGISTERS);
      }

      virtual void generate(AssignmentNode& node) override;
      virtual void generate(IdentifierNode& node) override;
      virtual void generate(InitNode&       node) override;
      virtual void generate(IntegerNode&    node) override;
      virtual void generate(OpDivideNode&   node) override;
      virtual void generate(OpMinusNode&    node) override;
      virtual void generate(OpMultiplyNode& node) override;
      virtual void generate(OpPlusNode&     node) override;
      virtual void generate(PrintNode&      node) override;
      virtual void generate(StatementsNode& node) override;
      virtual void generate(WhileNode&      node) override;

      virtual std::string getCode() override;

  private:
      /// The prefix for generated identifiers.
      static const std::string IDENTIFIER_PREFIX;
      /// The prefix for generated labels.
      static const std::string LABEL_PREFIX;

      /// If the compiler should generate comments in the assembly.
      bool debug;
      /// Holds the current saved register.
      int saveRegCounter;
      /// Holds the current tmp register for operations.
      int tmpRegCounter;
      /// Holds the number of times that each register has been pushed to the stack for a block.
      std::vector<int> regUse;
      /// Holds the statements in the program in order of the output file.
      std::vector<std::shared_ptr<MipsStatement>> mipsStatements;
      /// Holds the declared variables and type (unused for now)
      std::unordered_map<std::string, int> variables;
      /// Holds the registers and what variable address is currently mapped to them (if any).
      std::vector<std::string> savedVariableMapping;
      /// Holds generated label ids to guarantee uniqueness.
      std::unordered_set<std::string> generatedLabelIds;

      /**
      Return the tmp register offset from <tt>tmpRegCounter</tt>. The offset will wrap around the registers if it goes out of range.

      @param off The offset to tmpRegCounter.
      @return the register number.
      */
      int getRegOffset(int& reg, int off, int begin, int end);
      /**
      Return the previous tmp register number of <tt>tmpRegCounter</tt> with wrap-around.

      @return the previous (lower numbered) register number.
      */
      int previousReg(int& reg, int begin, int end);
      /**
      Pop the current register number off the stack then return the previous tmp register number of <tt>tmpRegCounter</tt> with wrap-around.

      @return the previous (lower numbered) register number.
      */
      int previousRegAndPop(int& reg, int begin, int end);
      /**
      Return the next tmp register number of <tt>tmpRegCounter</tt> with wrap-around.

      @return the next (higher numbered) register number.
      */
      int nextReg(int& reg, int begin, int end);
      /**
      Return the next tmp register number of <tt>tmpRegCounter</tt> with wrap-around then push the current tmp register to the stack.

      @return the next (higher numbered) register number.
      */
      int nextRegAndPush(int& reg, int begin, int end);
      /**
      Return the tmp register offset from <tt>tmpRegCounter</tt>. The offset will wrap around the registers if it goes out of range.

      @param off The offset to tmpRegCounter.
      @return the register number.
      */
      int getSaveOffset(int off);
      /**
      Return the previous tmp register number of <tt>tmpRegCounter</tt> with wrap-around.

      @return the previous (lower numbered) register number.
      */
      int previousSave();
      /**
      Pop the current register number off the stack then return the previous tmp register number of <tt>tmpRegCounter</tt> with wrap-around.

      @return the previous (lower numbered) register number.
      */
      int previousSaveAndPop();
      /**
      Return the next tmp register number of <tt>tmpRegCounter</tt> with wrap-around.

      @return the next (higher numbered) register number.
      */
      int nextSave();
      /**
      Return the next tmp register number of <tt>tmpRegCounter</tt> with wrap-around then push the current tmp register to the stack.

      @return the next (higher numbered) register number.
      */
      int nextSaveAndPush();
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
      void add(std::shared_ptr<MipsStatement>&& statement);

      int getAddrOfIdentifier(std::string identifier);

      std::string uniqueId();
      /**
      Append a mips op statement to the end of the current statements. Uses the previous and current tmp registers as source and the previous tmp register as the desination.

      */
      template <typename T>
      void addOpForCurrentTmp();
  };

  template <typename T>
  void MipsGenerator::addOpForCurrentTmp() {
      add(std::make_shared<T>(getTmpOffset(-1), getTmpOffset(-1), getTmpOffset(0)));
  }
}

#endif
