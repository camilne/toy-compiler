#ifndef MIPS_LOAD_ADDRESS_HPP
#define MIPS_LOAD_ADDRESS_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

namespace mips {
  class MipsLoadAddress : public MipsStatement {
  public:
      MipsLoadAddress(int dest, std::string addr)
          : dest(dest), addr(addr)
      {}

      virtual std::string toCode() const override {
          std::stringstream ss;
          ss << "la " << MipsUtil::toRegister(dest) << " " << addr << "\n";
          return ss.str();
      }

  private:
      int dest;
      std::string addr;
  };
}

#endif
