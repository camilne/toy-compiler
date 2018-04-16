#ifndef MIPS_INEQUALITY_HPP
#define MIPS_INEQUALITY_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

namespace mips{
  class MipsInequality : public MipsStatement {
  public:
    MipsInequality(int dest, int arg1, int arg2)
      : dest(dest), arg1(arg1), arg2(arg2)
    {}

    virtual std::string toCode() const override {
      std::stringstream ss;
      // Compare
      ss << "xor " << MipsUtil::toRegister(dest) << " ";
      ss << MipsUtil::toRegister(arg1) << " ";
      ss << MipsUtil::toRegister(arg2) << "\n";
      return ss.str();
    }

  private:
    int dest;
    int arg1;
    int arg2;
  };
}

#endif
