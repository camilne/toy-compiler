#include "catch.hpp"
#include "grammar.tab.h"
#include "ast/SyntaxTree.hpp"
#include <string>

struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char* str);
extern SyntaxTree* ast;

SyntaxTree* parseString(const std::string& str) {
  yy_scan_string(str.c_str());
  yyparse();

  return ast;
}

TEST_CASE("parses statements", "[parser]") {
  SECTION("none") {
    static const std::string source = "";

    auto ast = parseString(source);

    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements() == nullptr);
  }

  SECTION("one") {
    static const std::string source = "1;";

    auto ast = parseString(source);

    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
  }

  SECTION("many") {
    static const std::string source = "1;1;1;";

    auto ast = parseString(source);

    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
  }
}
