#include "generator/MipsCodeGenerator.hpp"
#include "generator/MipsOptimizer.hpp"
#include <sstream>

using namespace mips;

void MipsCodeGenerator::generateCode() {
  MipsOptimizer optimizer(statements);
  optimizer.optimize();

  std::stringstream ss;
  ss << ".data\n";
  for(std::pair<std::string, int> identifier : identifiers) {
      ss << identifier.first << ": .word 0\n";
  }
  ss << ".text\n";
  for(std::shared_ptr<MipsStatement>& statement : statements) {
      ss << statement->toCode();
  }
  code = ss.str();
  isCodeGenerated = true;
}
