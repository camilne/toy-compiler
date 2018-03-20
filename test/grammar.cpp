#include "catch.hpp"
#include "grammar.tab.h"
#include "ast/SyntaxTree.ih"
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

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements() == nullptr);
  }

  SECTION("one") {
    static const std::string source = "1;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
  }

  SECTION("many") {
    static const std::string source = "1;1;1;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    REQUIRE(ast->getRoot()->getStatements()->getStatements());
  }
}

TEST_CASE("parses statement", "[parser]") {
  SECTION("print") {
    static const std::string source = "print 1;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto printNode = ast->getRoot()->getStatements()->getStatementAs<PrintNode*>();
    REQUIRE(printNode);
    REQUIRE(printNode->getExp());
  }

  SECTION("integer literal") {
    static const std::string source = "10;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto integerNode = ast->getRoot()->getStatements()->getStatementAs<IntegerNode*>();
    REQUIRE(integerNode);
    REQUIRE(integerNode->getValue() == 10);
  }

  SECTION("identifier") {
    static const std::string source = "id;";
    static const std::string idName = "id";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto identifierNode = ast->getRoot()->getStatements()->getStatementAs<IdentifierNode*>();
    REQUIRE(identifierNode);
    REQUIRE(identifierNode->getName() == idName);
  }
}