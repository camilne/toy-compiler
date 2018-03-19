cmake_minimum_required(VERSION 3.5)
project(compiler)

option(tests "Build tests" OFF)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/include)
include_directories(${CMAKE_CURRENT_BINARY_DIR})
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -Wall -Wextra")
set(CMAKE_CXX_STANDARD 14)

set(INCLUDE_FILES
  include/Arguments.hpp
  include/ast/AssignmentNode.hpp
  include/ast/IdentifierNode.hpp
  include/ast/InitNode.hpp
  include/ast/IntegerNode.hpp
  include/ast/OpDivideNode.hpp
  include/ast/OpMinusNode.hpp
  include/ast/OpMultiplyNode.hpp
  include/ast/OpPlusNode.hpp
  include/ast/PrintNode.hpp
  include/ast/StatementsNode.hpp
  include/ast/SyntaxTree.hpp
  include/ast/SyntaxTree.ih
  include/ast/SyntaxTreeNode.hpp
  include/ast/SyntaxTreeNodes.ih
  include/ast/WhileNode.hpp
  include/generator/IGenerator.hpp
  include/generator/MipsAdd.hpp
  include/generator/MipsBranchEqual.hpp
  include/generator/MipsComment.hpp
  include/generator/MipsDivide.hpp
  include/generator/MipsGenerator.hpp
  include/generator/MipsJump.hpp
  include/generator/MipsLabel.hpp
  include/generator/MipsLoad.hpp
  include/generator/MipsLoadAddress.hpp
  include/generator/MipsLoadImmediate.hpp
  include/generator/MipsMinus.hpp
  include/generator/MipsMultiply.hpp
  include/generator/MipsOp.hpp
  include/generator/MipsPop.hpp
  include/generator/MipsPush.hpp
  include/generator/MipsStatement.hpp
  include/generator/MipsStatements.ih
  include/generator/MipsStore.hpp
  include/generator/MipsSysCall.hpp
  include/generator/MipsUtil.hpp
)

set(LIB_SOURCE_FILES
  src/Arguments.cpp
  src/ast/AssignmentNode.cpp
  src/ast/IdentifierNode.cpp
  src/ast/InitNode.cpp
  src/ast/IntegerNode.cpp
  src/ast/OpDivideNode.cpp
  src/ast/OpMinusNode.cpp
  src/ast/OpMultiplyNode.cpp
  src/ast/OpPlusNode.cpp
  src/ast/PrintNode.cpp
  src/ast/StatementsNode.cpp
  src/ast/WhileNode.cpp
  src/generator/MipsGenerator.cpp
  src/generator/MipsUtil.cpp
)

set(SOURCE_FILES src/main.cpp)

find_package(BISON REQUIRED)
find_package(FLEX REQUIRED)

BISON_TARGET(Parser ${CMAKE_CURRENT_SOURCE_DIR}/lang/grammar.y ${CMAKE_CURRENT_BINARY_DIR}/grammar.tab.c)
FLEX_TARGET(Lexer ${CMAKE_CURRENT_SOURCE_DIR}/lang/lex.l  ${CMAKE_CURRENT_BINARY_DIR}/lexer.yy.c)
ADD_FLEX_BISON_DEPENDENCY(Lexer Parser)

set_source_files_properties(${BISON_Parser_OUTPUT_SOURCE} PROPERTIES LANGUAGE CXX)
set_source_files_properties(${FLEX_Lexer_OUTPUTS} PROPERTIES LANGUAGE CXX)

set(GENERATED_FILES ${BISON_Parser_OUTPUTS} ${FLEX_Lexer_OUTPUTS})

add_library(compiler_lib ${INCLUDE_FILES} ${LIB_SOURCE_FILES} ${GENERATED_FILES})
add_executable(compiler ${INCLUDE_FILES} ${SOURCE_FILES})
target_link_libraries(compiler compiler_lib)

if(${tests})
  set(TEST_INCLUDE_FILES ${INCLUDE_FILES} include/catch.hpp)
  set(TEST_SOURCE_FILES
    test/grammar.cpp
    test/lexer.cpp
    test/main.cpp
  )

  add_executable(compiler_tests ${TEST_INCLUDE_FILES} ${TEST_SOURCE_FILES})
  target_link_libraries(compiler_tests compiler_lib)
endif()
