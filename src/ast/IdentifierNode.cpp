#include "ast/IdentifierNode.hpp"

std::string IdentifierNode::toCode() const {
    return name;
}
