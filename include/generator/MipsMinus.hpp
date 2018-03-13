#ifndef MIPS_MINUS_HPP
#define MIPS_MINUS_HPP

#include "generator/MipsOp.hpp"

class MipsMinus : public MipsOp {
public:
    MipsMinus(int dest, int arg1, int arg2)
        : MipsOp("sub", dest, arg1, arg2)
    {}
};

#endif
