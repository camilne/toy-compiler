all:
	$(MAKE) grammar
	$(MAKE) lex
	$(MAKE) compile

lex:
	flex lex.l

grammar:
	bison -d grammar.y

compile:
	g++ -c grammar.tab.c
	g++ -c lex.yy.c
	g++ -c main.cpp
	g++ -std=c++11 -g3 grammar.tab.o lex.yy.o main.o -o compiler

run:
	$(MAKE) all
	./compiler < test/test.code
