#ifndef MIPS_EQUALITY_HPP
#define MIPS_EQUALITY_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>

namespace mips{
  class MipsEquality : public MipsStatement {
  public:
    MipsEquality(int dest, int arg1, int arg2)
      : dest(dest), arg1(arg1), arg2(arg2)
    {}

    virtual std::string toCode() const override {
      std::stringstream ss;
      // Compare
      ss << "xor " << MipsUtil::toRegister(dest) << " ";
      ss << MipsUtil::toRegister(arg1) << " ";
      ss << MipsUtil::toRegister(arg2) << "\n";
      // Set to 1 if same
      ss << "sltu " << MipsUtil::toRegister(dest) << " ";
      ss << MipsUtil::toRegister(0) << " ";
      ss << MipsUtil::toRegister(dest) << "\n";
      // Invert 1->0 or 0->1
      ss << "xori " << MipsUtil::toRegister(dest) << " ";
      ss << MipsUtil::toRegister(dest) << " ";
      ss << "1\n";
      return ss.str();
    }

  private:
    int dest;
    int arg1;
    int arg2;
  };
}

#endif
