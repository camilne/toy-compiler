#ifndef MIPS_OR_HPP
#define MIPS_OR_HPP

#include "generator/MipsOp.hpp"

namespace mips {
  class MipsOr : public MipsOp {
  public:
      MipsOr(int dest, int arg1, int arg2)
          : MipsOp("or ", dest, arg1, arg2)
      {}
  };
}

#endif
