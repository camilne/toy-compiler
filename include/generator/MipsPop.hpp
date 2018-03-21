#ifndef MIPS_POP_HPP
#define MIPS_POP_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

namespace mips {
  class MipsPop : public MipsStatement {
  public:
      explicit MipsPop(unsigned int reg)
          : reg(reg)
      {}

      virtual std::string toCode() const override {
          std::stringstream ss;
          ss << "lw " << MipsUtil::toRegister(reg) << " 0($sp)\n";
          ss << "addi $sp $sp 4\n";
          return ss.str();
      }

      unsigned int getRegister() const {
          return reg;
      }

  private:
      unsigned int reg;
  };
}

#endif
