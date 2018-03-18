#include "catch.hpp"
#include "grammar.tab.h"
#include <vector>
#include <string>
#include <array>

struct yy_buffer_state;
typedef struct yy_buffer_state *YY_BUFFER_STATE;
extern YY_BUFFER_STATE yy_scan_string(const char* str);
union YYSTYPE;
extern YYSTYPE yylval;
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

TEST_CASE("tokenizes integers", "[lexer]") {
  static const std::string source = "0 1 12 015 1234567890";

  SECTION("type") {
    std::vector<int> tokens = lexString(source);

    REQUIRE(tokens.size() == 5);
    REQUIRE(tokens[0] == yytokentype::INTEGER);
    REQUIRE(tokens[1] == yytokentype::INTEGER);
    REQUIRE(tokens[2] == yytokentype::INTEGER);
    REQUIRE(tokens[3] == yytokentype::INTEGER);
    REQUIRE(tokens[4] == yytokentype::INTEGER);
  }

  SECTION("value") {
    yy_scan_string(source.c_str());
    std::array<int, 5> values = {0, 1, 12, 15, 1234567890};
    for(auto it = values.begin(); it != values.end() && yylex(); ++it) {
      REQUIRE(*it == yylval.INT);
    }
  }
}
