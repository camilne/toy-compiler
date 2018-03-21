#ifndef MIPS_ADD_HPP
#define MIPS_ADD_HPP

#include "generator/MipsOp.hpp"

namespace mips{
  class MipsAdd : public MipsOp {
  public:
      MipsAdd(int dest, int arg1, int arg2)
          : MipsOp("add", dest, arg1, arg2)
      {}
  };
}

#endif
