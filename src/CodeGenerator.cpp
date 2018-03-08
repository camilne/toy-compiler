#include "CodeGenerator.hpp"

std::string CodeGenerator::generate() {
    return ast->toCode();
}
