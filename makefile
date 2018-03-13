LANG_FOLDER		:= lang
INCLUDE_FOLDER	:= include
SOURCE_FOLDER	:= src
TEST_FOLDER		:= test
GENERATED_FOLDER	:= generated

CXX				:= g++
CXXFLAGS		:= -std=c++14 -g3 -Wall -Wextra -I $(INCLUDE_FOLDER)

FLEX			:= flex
FLEX_SOURCE		:= $(LANG_FOLDER)/lex.l
FLEX_GENERATED	:= lex.yy.c

BISON			:= bison
BISONFLAGS		:= -d -Wall
BISON_SOURCE	:= $(LANG_FOLDER)/grammar.y
BISON_GENERATED := grammar.tab.*

GENERATED_FILES := $(GENERATED_FOLDER)/$(FLEX_GENERATED) $(GENERATED_FOLDER)/$(BISON_GENERATED)
SOURCE_FILES	:= $(GENERATED_FILES) $(SOURCE_FOLDER)/*.cpp $(SOURCE_FOLDER)/**/*.cpp
EXECUTABLE		:= compiler


all: compiler

$(GENERATED_FOLDER)/$(FLEX_GENERATED): $(FLEX_SOURCE) $(GENERATED_FOLDER)/$(BISON_GENERATED)
	$(FLEX) $(FLEX_SOURCE)
	mkdir -p $(GENERATED_FOLDER)
	mv $(FLEX_GENERATED) $(GENERATED_FOLDER)

$(GENERATED_FOLDER)/$(BISON_GENERATED): $(BISON_SOURCE)
	$(BISON) $(BISONFLAGS) $(BISON_SOURCE)
	mkdir -p $(GENERATED_FOLDER)
	mv $(BISON_GENERATED) $(GENERATED_FOLDER)

compiler: $(SOURCE_FILES)
	$(CXX) $(CXXFLAGS) -o $(EXECUTABLE) $(SOURCE_FILES)

clean:
	rm $(EXECUTABLE)
	rm -r $(GENERATED_FOLDER)

test:
	@$(MAKE) all -s
	@./$(EXECUTABLE) < $(TEST_FOLDER)/test.code

.PHONY: test
