#ifndef MIPS_OPTIMIZER_HPP
#define MIPS_OPTIMIZER_HPP

#include <vector>
#include <memory>
#include "generator/MipsStatements.ih"

namespace mips {
  class MipsOptimizer {
  public:
    explicit MipsOptimizer(std::vector<std::shared_ptr<MipsStatement>>& statements)
      : statements(statements)
    {}

    void optimize();
  private:
    std::vector<std::shared_ptr<MipsStatement>>& statements;

    void removeTrailingPopIfRegisterIsUnusedAfter();
  };
}

#endif
