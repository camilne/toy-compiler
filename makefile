CXX				:= g++
CXXFLAGS		:= -std=c++11 -g3

GENERATED_FILES := grammar.tab.c grammar.tab.h lex.yy.c
SOURCE_FILES	:= $(GENERATED_FILES) main.cpp
EXECUTABLE		:= compiler

all: compiler

lex.yy.c: lex.l grammar.tab.h
	flex lex.l

grammar.tab.c grammar.tab.h: grammar.y
	bison -d grammar.y

compiler: $(SOURCE_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(SOURCE_FILES)

clean:
	rm $(EXECUTABLE) $(GENERATED_FILES) 

run:
	@$(MAKE) all -s
	@./$(EXECUTABLE) < test/test.code
