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

  SECTION("empty while") {
    static const std::string source = "while(0){}";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto whileNode = ast->getRoot()->getStatements()->getStatementAs<WhileNode*>();
    REQUIRE(whileNode);
    REQUIRE(whileNode->getExpression());
    REQUIRE(whileNode->getStatements() == nullptr);
  }

  SECTION("while with statement") {
    static const std::string source = "while(0){0;}";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto whileNode = ast->getRoot()->getStatements()->getStatementAs<WhileNode*>();
    REQUIRE(whileNode);
    REQUIRE(whileNode->getExpression());
    REQUIRE(whileNode->getStatements());
  }

  SECTION("op divide") {
    static const std::string source = "1 / 2;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto divideNode = ast->getRoot()->getStatements()->getStatementAs<OpDivideNode*>();
    REQUIRE(divideNode);
    REQUIRE(divideNode->getLeftExp());
    REQUIRE(divideNode->getRightExp());
  }

  SECTION("op minus") {
    static const std::string source = "1 - 2;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto minusNode = ast->getRoot()->getStatements()->getStatementAs<OpMinusNode*>();
    REQUIRE(minusNode);
    REQUIRE(minusNode->getLeftExp());
    REQUIRE(minusNode->getRightExp());
  }

  SECTION("op multiply") {
    static const std::string source = "1 * 2;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto multiplyNode = ast->getRoot()->getStatements()->getStatementAs<OpMultiplyNode*>();
    REQUIRE(multiplyNode);
    REQUIRE(multiplyNode->getLeftExp());
    REQUIRE(multiplyNode->getRightExp());
  }

  SECTION("op plus") {
    static const std::string source = "1 + 2;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto plusNode = ast->getRoot()->getStatements()->getStatementAs<OpPlusNode*>();
    REQUIRE(plusNode);
    REQUIRE(plusNode->getLeftExp());
    REQUIRE(plusNode->getRightExp());
  }

  SECTION("assignment") {
    static const std::string source = "a = 10;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto assignmentNode = ast->getRoot()->getStatements()->getStatementAs<AssignmentNode*>();
    REQUIRE(assignmentNode);
    REQUIRE(assignmentNode->getIdentifier());
    REQUIRE(assignmentNode->getExpression());
  }
}
