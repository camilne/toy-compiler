#ifndef MIPS_STATEMENT_HPP
#define MIPS_STATEMENT_HPP

#include <string>

namespace mips {
  class MipsStatement {
  public:
      virtual std::string toCode() const = 0;
  };
}

#endif
