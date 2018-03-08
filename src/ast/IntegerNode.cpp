#include "ast/IntegerNode.hpp"
#include <string>

std::string IntegerNode::toCode() const {
    return std::to_string(value);
}
