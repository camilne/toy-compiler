#ifndef MIPS_DIVIDE_HPP
#define MIPS_DIVIDE_HPP

#include "generator/MipsOp.hpp"

namespace mips{
  class MipsDivide : public MipsOp {
  public:
      MipsDivide(int dest, int arg1, int arg2)
          : MipsOp("div", dest, arg1, arg2)
      {}
  };
}

#endif
