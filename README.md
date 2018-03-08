Toy Compiler Project
====================

This is a toy compiler that I am working on. It is written in C++. It uses the following libraries:

* flex      (lexer)
* bison     (parser)

The goal of this project is to turn a toy C-like language into MIPS assembly, which will then be assembled (with an assembler written by me) into machine code. This machine code can then run on a virtual machine (also created by me). It is an exercise for me to learn about compilers and computer architecture.

Testing
-------

No unit tests are currently being done, but you can run `make test` to build the project and run some sample code through the compiler.

Structure
---------

The compiler is split up into several folders.

folder      | content
------      | -------
src         | cpp
include     | hpp, ih
test        | code sample test, eventually unit tests
lang        | language specification for flex/bison
generated\* | generated files by flex/bison (changes will be overwritten)

:octocat:
