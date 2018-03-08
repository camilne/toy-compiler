CXX				:= g++
CXXFLAGS		:= -std=c++11 -g3

FLEX			:= flex
FLEX_SOURCE		:= lex.l
FLEX_GENERATED	:= lex.yy.c

BISON			:= bison
BISONFLAGS		:= -d
BISON_SOURCE	:= grammar.y
BISON_GENERATED := grammar.tab.c grammar.tab.h

GENERATED_FILES := $(FLEX_GENERATED) $(BISON_GENERATED)
SOURCE_FILES	:= $(GENERATED_FILES) *.hpp *.cpp
EXECUTABLE		:= compiler


all: compiler

$(FLEX_GENERATED): $(FLEX_SOURCE) $(BISON_GENERATED)
	$(FLEX) $(FLEX_SOURCE)

$(BISON_GENERATED): $(BISON_SOURCE)
	$(BISON) $(BISONFLAGS) $(BISON_SOURCE)

compiler: $(SOURCE_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(SOURCE_FILES)

clean:
	rm $(EXECUTABLE) $(GENERATED_FILES) 

test:
	@$(MAKE) all -s
	@./$(EXECUTABLE) < test/test.code

.PHONY: test
