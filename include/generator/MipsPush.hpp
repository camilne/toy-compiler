#ifndef MIPS_PUSH_HPP
#define MIPS_PUSH_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

namespace mips {
  class MipsPush : public MipsStatement {
  public:
      explicit MipsPush(unsigned int reg)
          : reg(reg)
      {}

      virtual std::string toCode() const override {
          std::stringstream ss;
          ss << "addi $sp $sp -4\n";
          ss << "sw " << MipsUtil::toRegister(reg) << " 0($sp)\n";
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
