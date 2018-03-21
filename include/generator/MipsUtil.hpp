#ifndef MIPS_UTIL_HPP
#define MIPS_UTIL_HPP

#include <string>

namespace mips {
  class MipsUtil {
  public:
      static std::string toHex(uint32_t val);
      static std::string toRegister(int val);
  };
}

#endif
