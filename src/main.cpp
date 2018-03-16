#include <iostream>
#include "../generated/grammar.tab.h"
#include "ast/SyntaxTree.hpp"
#include "generator/MipsGenerator.hpp"
#include "Arguments.hpp"
#include <vector>
#include <fstream>
#include <stdio.h>

extern FILE* yyin;
extern SyntaxTree* ast;

int main(int argc, char** argv) {
    bool verbose = false;
    std::string outputFile;

    Arguments arguments(argc, argv);
    arguments.registerFlag("-v", [&](){
        verbose = true;
    });
    arguments.registerFlag("-o", [&](std::string arg) {
        outputFile = arg;
    });
    arguments.process();
    if(arguments.fail())
        return 1;

    // TEMP: only process the first input file given
    if(arguments.getAnonymousArgs().size() > 0) {
        const std::string fileName = arguments.getAnonymousArgs()[0];
        std::ifstream fin(fileName);
        if(fin.good()) {
            fin.close();
            yyin = fopen(fileName.c_str(), "r");
        } else {
            std::cerr << "Invalid input file " << fileName << std::endl;
            return 2;
        }
    }

    int result = yyparse();

    if(result)
        std::cerr << "This input is invalid." << std::endl;
    else {
        MipsGenerator generator(verbose);
        ast->accept(generator);

        generator.optimize();

        if(outputFile != "") {
            std::ofstream fout(outputFile);
            fout << generator.getCode() << std::endl;
            fout.close();
        } else {
            std::cout << generator.getCode() << std::endl;
        }
    }

    return result;
}
