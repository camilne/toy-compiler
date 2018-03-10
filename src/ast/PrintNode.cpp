#include "ast/PrintNode.hpp"

std::string PrintNode::toCode() const {
    return "print " + exp->toCode();
}
