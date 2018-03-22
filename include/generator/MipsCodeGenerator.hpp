#ifndef MIPS_CODE_GENERATOR_HPP
#define MIPS_CODE_GENERATOR_HPP

#include <vector>
#include <memory>
#include <unordered_map>
#include <string>
#include "generator/MipsStatements.ih"

namespace mips {
  class MipsCodeGenerator {
  public:
    MipsCodeGenerator(std::vector<std::shared_ptr<MipsStatement>>& statements, std::unordered_map<std::string, int>& identifiers)
      : statements(statements), identifiers(identifiers), isCodeGenerated(false), code("")
    {}

    const std::string& getCode() {
      if(!isCodeGenerated) {
        generateCode();
      }

      return code;
    }

  private:
    std::vector<std::shared_ptr<MipsStatement>>& statements;
    std::unordered_map<std::string, int>& identifiers;
    bool isCodeGenerated;
    std::string code;

    void generateCode();
  };
}

#endif
