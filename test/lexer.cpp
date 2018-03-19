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

TEST_CASE("tokenizes identifiers", "[lexer]") {
  static const std::string source = "a f z A F Z a0 a5 a9 _a a_ __afzAFZ09__";

  SECTION("type") {
    std::vector<int> tokens = lexString(source);

    REQUIRE(tokens.size() == 12);
    for(unsigned int i = 0; i < tokens.size(); i++) {
      REQUIRE(tokens[i] == yytokentype::IDENTIFIER);
    }
  }

  SECTION("value") {
    yy_scan_string(source.c_str());
    std::array<std::string, 12> values = {"a", "f", "z", "A", "F", "Z", "a0", "a5", "a9", "_a", "a_", "__afzAFZ09__"};
    for(auto it = values.begin(); it != values.end() && yylex(); ++it) {
      REQUIRE(*it == yylval.STRING);
    }
  }

  SECTION("invalid") {
    static const std::string invalid = "0a $a #a @a";
    static const std::string identifier = "a";

    std::vector<int> tokens = lexString(invalid);
    yy_scan_string(invalid.c_str());

    for(unsigned int i = 0; i < tokens.size() && yylex(); i++) {
      switch(tokens[i]) {
      case yytokentype::IDENTIFIER:
        REQUIRE(yylval.STRING == identifier);
        break;
      case yytokentype::INVALID_IDENTIFIER:
      case yytokentype::UNKNOWN:
        break;
      default:
        INFO("Invalid token");
        REQUIRE(i == 0);
      }
    }
  }
}

TEST_CASE("ignores comments", "[lexer]") {
  SECTION("line") {
    static const std::string source = "shown // ignore";
    static const std::string identifier = "shown";

    std::vector<int> tokens = lexString(source);
    yy_scan_string(source.c_str());

    REQUIRE(tokens.size() == 1);
    yylex();
    REQUIRE(yylval.STRING == identifier);
  }

  SECTION("block") {
    static const std::string source = "shown /* ignored \n \n ignored \n ***/ also_shown";
    static const std::string identifier1 = "shown";
    static const std::string identifier2 = "also_shown";

    std::vector<int> tokens = lexString(source);
    yy_scan_string(source.c_str());

    REQUIRE(tokens.size() == 2);
    yylex();
    INFO("Before block");
    REQUIRE(yylval.STRING == identifier1);
    yylex();
    INFO("After block");
    REQUIRE(yylval.STRING == identifier2);
  }
}
