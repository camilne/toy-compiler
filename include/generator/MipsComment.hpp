#ifndef MIPS_COMMENT_HPP
#define MIPS_COMMENT_HPP

#include "generator/MipsStatement.hpp"
#include "generator/MipsUtil.hpp"
#include <sstream>
#include <algorithm>

namespace mips{
  class MipsComment : public MipsStatement {
  public:
      MipsComment(std::string content)
          : content(content)
      {}

      virtual std::string toCode() const override {
          std::string stripped = content;
          std::replace(stripped.begin(), stripped.end(), '\n', ' ');

          std::stringstream ss;
          ss << "# " << stripped << "\n";
          return ss.str();
      }

  private:
      std::string content;
  };
}

#endif
