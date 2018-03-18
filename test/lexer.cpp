#include "catch.hpp"
#include "../generated/grammar.tab.h"
#include <vector>
#include <string>

struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char* str);
extern int yylex();

std::vector<int> lexString(const std::string& str) {
  yy_scan_string(str.c_str());
  std::vector<int> tokens;
  int token;
  while(token = yylex()) {
    tokens.push_back(token);
  }
  return tokens;
}

TEST_CASE("ignores whitespace", "[lexer]") {
  static const std::string reference = "1;2;3;";
  std::vector<int> refTokens = lexString(reference);

  REQUIRE(refTokens.size() == 6);
  REQUIRE(refTokens[0] == yytokentype::INTEGER);
  REQUIRE(refTokens[1] == yytokentype::SEMICOLON);
  REQUIRE(refTokens[2] == yytokentype::INTEGER);
  REQUIRE(refTokens[3] == yytokentype::SEMICOLON);
  REQUIRE(refTokens[4] == yytokentype::INTEGER);
  REQUIRE(refTokens[5] == yytokentype::SEMICOLON);

  SECTION("one line") {
    static const std::string source = "1; 2; 3;";
    std::vector<int> tokens = lexString(source);

    REQUIRE(refTokens == tokens);
  }

  SECTION("leading space") {
    static const std::string source = "  1; 2; 3;";
    std::vector<int> tokens = lexString(source);

    REQUIRE(refTokens == tokens);
  }

  SECTION("trailing space") {
    static const std::string source = "1; 2; 3;     ";
    std::vector<int> tokens = lexString(source);

    REQUIRE(refTokens == tokens);
  }

  SECTION("multi-line") {
    static const std::string source = "1;\n2;\n3;";
    std::vector<int> tokens = lexString(source);

    REQUIRE(refTokens == tokens);
  }

  SECTION("multi-space") {
    static const std::string source = "1;    2;        3;";
    std::vector<int> tokens = lexString(source);

    REQUIRE(refTokens == tokens);
  }

  SECTION("tabs") {
    static const std::string source = "1;\t2; \t\t 3;";
    std::vector<int> tokens = lexString(source);

    REQUIRE(refTokens == tokens);
  }

  SECTION("mixed") {
    static const std::string source = "1; \n\t\t 2;     \n    \t 3;  \t";
    std::vector<int> tokens = lexString(source);

    REQUIRE(refTokens == tokens);
  }
}
