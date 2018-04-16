#include "catch.hpp"
#include "grammar.tab.h"
#include "ast/SyntaxTree.ih"
#include <string>
#include <iostream>

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

  SECTION("empty if") {
    static const std::string source = "if(0){}";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto ifNode = ast->getRoot()->getStatements()->getStatementAs<IfNode*>();
    REQUIRE(ifNode);
    REQUIRE(ifNode->getExpression());
    REQUIRE(ifNode->getStatements() == nullptr);
  }

  SECTION("if with statement") {
    static const std::string source = "if(0){0;}";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto ifNode = ast->getRoot()->getStatements()->getStatementAs<IfNode*>();
    REQUIRE(ifNode);
    REQUIRE(ifNode->getExpression());
    REQUIRE(ifNode->getStatements());
  }

  SECTION("empty else") {
    static const std::string source = "if(0){}else{}";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto ifElseNode = ast->getRoot()->getStatements()->getStatementAs<IfElseNode*>();
    REQUIRE(ifElseNode);
    REQUIRE(ifElseNode->getExpression());
    REQUIRE(ifElseNode->getStatements() == nullptr);
    REQUIRE(ifElseNode->getElseStatements() == nullptr);
  }

  SECTION("if else with statement") {
    static const std::string source = "if(0){0;}else{0;}";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto ifElseNode = ast->getRoot()->getStatements()->getStatementAs<IfElseNode*>();
    REQUIRE(ifElseNode);
    REQUIRE(ifElseNode->getExpression());
    REQUIRE(ifElseNode->getStatements());
    REQUIRE(ifElseNode->getElseStatements());
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
}

TEST_CASE("parses expression", "[parser]") {
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

  SECTION("unary minus") {
    static const std::string source = "-5;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto minusNode = ast->getRoot()->getStatements()->getStatementAs<OpMinusNode*>();
    REQUIRE(minusNode);

    REQUIRE(minusNode->getLeftExp());
    auto zeroNode = dynamic_cast<IntegerNode*>(minusNode->getLeftExp());
    REQUIRE(zeroNode);
    REQUIRE(zeroNode->getValue() == 0);

    REQUIRE(minusNode->getRightExp());
    auto valueNode = dynamic_cast<IntegerNode*>(minusNode->getRightExp());
    REQUIRE(valueNode);
    REQUIRE(valueNode->getValue() == 5);
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

  SECTION("equality") {
    static const std::string source = "5 == 10;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto equalityNode = ast->getRoot()->getStatements()->getStatementAs<OpEqualityNode*>();
    REQUIRE(equalityNode);
    REQUIRE(equalityNode->getLeftExp());
    REQUIRE(equalityNode->getRightExp());
  }

  SECTION("inequality") {
    static const std::string source = "5 != 10;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto inequalityNode = ast->getRoot()->getStatements()->getStatementAs<OpInequalityNode*>();
    REQUIRE(inequalityNode);
    REQUIRE(inequalityNode->getLeftExp());
    REQUIRE(inequalityNode->getRightExp());
  }

  SECTION("less than") {
    static const std::string source = "5 < 10;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto lessThanNode = ast->getRoot()->getStatements()->getStatementAs<OpLessThanNode*>();
    REQUIRE(lessThanNode);
    REQUIRE(lessThanNode->getLeftExp());
    REQUIRE(lessThanNode->getRightExp());
  }

  SECTION("greater than") {
    static const std::string source = "5 > 10;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto greaterThanNode = ast->getRoot()->getStatements()->getStatementAs<OpGreaterThanNode*>();
    REQUIRE(greaterThanNode);
    REQUIRE(greaterThanNode->getLeftExp());
    REQUIRE(greaterThanNode->getRightExp());
  }

  SECTION("less than equal") {
    static const std::string source = "5 <= 10;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto lessThanEqualNode = ast->getRoot()->getStatements()->getStatementAs<OpLessThanEqualNode*>();
    REQUIRE(lessThanEqualNode);
    REQUIRE(lessThanEqualNode->getLeftExp());
    REQUIRE(lessThanEqualNode->getRightExp());
  }

  SECTION("single parentheses are transparent") {
    static const std::string source = "(1);";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto integerNode = ast->getRoot()->getStatements()->getStatementAs<IntegerNode*>();
    REQUIRE(integerNode);
    REQUIRE(integerNode->getValue() == 1);
  }
}

TEST_CASE("operator precedence is respected", "[parser]") {
  SECTION("op with unary minus") {
    static const std::string source = "1 + -5;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto plusNode = ast->getRoot()->getStatements()->getStatementAs<OpPlusNode*>();
    REQUIRE(plusNode);
    REQUIRE(plusNode->getLeftExp());
    REQUIRE(plusNode->getRightExp());
    auto minusNode = dynamic_cast<OpMinusNode*>(plusNode->getRightExp());
    REQUIRE(minusNode);
  }

  SECTION("op plus and op minus same precedence") {
    static const std::string source = "1 + 5 - 3;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto plusNode = ast->getRoot()->getStatements()->getStatementAs<OpPlusNode*>();
    REQUIRE(plusNode);
    REQUIRE(plusNode->getLeftExp());
    REQUIRE(plusNode->getRightExp());
    auto minusNode = dynamic_cast<OpMinusNode*>(plusNode->getRightExp());
    REQUIRE(minusNode);
    REQUIRE(minusNode->getLeftExp());
    REQUIRE(minusNode->getRightExp());
  }

  SECTION("op multiply and op divide same precedence") {
    static const std::string source = "1 * 5 / 3;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto multiplyNode = ast->getRoot()->getStatements()->getStatementAs<OpMultiplyNode*>();
    REQUIRE(multiplyNode);
    REQUIRE(multiplyNode->getLeftExp());
    REQUIRE(multiplyNode->getRightExp());
    auto divideNode = dynamic_cast<OpDivideNode*>(multiplyNode->getRightExp());
    REQUIRE(divideNode);
    REQUIRE(divideNode->getLeftExp());
    REQUIRE(divideNode->getRightExp());
  }

  SECTION("op multiply higher than op plus") {
    static const std::string source = "1 + 2 * 3;";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto plusNode = ast->getRoot()->getStatements()->getStatementAs<OpPlusNode*>();
    REQUIRE(plusNode);
    REQUIRE(plusNode->getLeftExp());
    REQUIRE(plusNode->getRightExp());
    auto multiplyNode = dynamic_cast<OpMultiplyNode*>(plusNode->getRightExp());
    REQUIRE(multiplyNode);
    REQUIRE(multiplyNode->getLeftExp());
    REQUIRE(multiplyNode->getRightExp());
  }

  SECTION("parentheses higher than all op") {
    static const std::string source = "5 * (2 + 1);";

    auto ast = parseString(source);

    REQUIRE(ast);
    REQUIRE(ast->getRoot());
    REQUIRE(ast->getRoot()->getStatements());
    auto multiplyNode = ast->getRoot()->getStatements()->getStatementAs<OpMultiplyNode*>();
    REQUIRE(multiplyNode);
    REQUIRE(multiplyNode->getLeftExp());
    REQUIRE(multiplyNode->getRightExp());
    auto plusNode = dynamic_cast<OpPlusNode*>(multiplyNode->getRightExp());
    REQUIRE(plusNode);
    REQUIRE(plusNode->getLeftExp());
    REQUIRE(plusNode->getRightExp());
  }
}
