#include "generator/CodeGenerator.hpp"

std::string CodeGenerator::generate() {
    return ast->toCode();
}
