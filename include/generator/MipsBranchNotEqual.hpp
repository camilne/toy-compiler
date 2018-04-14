#ifndef MIPS_BRANCH_NOT_EQUAL_HPP
#define MIPS_BRANCH_NOT_EQUAL_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

namespace mips{
  class MipsBranchNotEqual : public MipsStatement {
  public:
      explicit MipsBranchNotEqual(int regA, int regB, std::string name)
          : regA(regA), regB(regB), name(name)
      {}

      virtual std::string toCode() const override {
          std::stringstream ss;
          ss << "bne " << MipsUtil::toRegister(regA) << " " << MipsUtil::toRegister(regB);
          ss << " " << name << "\n";
          return ss.str();
      }

      std::string getName() const {
          return name;
      }

  private:
      int regA;
      int regB;
      std::string name;
  };
}

#endif
