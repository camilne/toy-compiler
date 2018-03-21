#ifndef MIPS_MULTIPLY_HPP
#define MIPS_MULTIPLY_HPP

#include "generator/MipsOp.hpp"

namespace mips {
  class MipsMultiply : public MipsOp {
  public:
      MipsMultiply(int dest, int arg1, int arg2)
          : MipsOp("mul", dest, arg1, arg2)
      {}
  };
}

#endif
