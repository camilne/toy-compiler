miniC->MIPS Compiler Project
====================

This is a toy compiler that I am working on. It is written in C++. It uses the following libraries:

* flex      (lexer)
* bison     (parser)

The goal of this project is to turn a toy C-like language (miniC) into MIPS32 assembly. The output will then be assembled (with an assembler written by me) into machine code. This machine code can then run on a virtual machine (also created by me). It is an exercise with compilers and computer architecture.

Compilation
-----------

To build the project, make sure you have the libraries installed then run `make`. This will generate an executable called *compiler*. This accepts a program through `stdin` and outputs the compiled program to `stdout`.

The compiler currently supports a few command line options:

Flag         | Name    | Argument(s)  | Description
------       | ----    | -----------  | -----------
&lt;none&gt; |         | [files]      | specifies input files (max of one supported at the moment)
-v           | verbose | &lt;none&gt; | enables comments to be generated in the output file
-o           | output  | &lt;file&gt; | specifies an output file


Testing
-------

No unit tests are currently being done, but you can run `make test` (outputs to `stdout`) or `make out` (outputs to `a.asm`) to build the project and run some sample code through the compiler.

Documentation
-------------

You can generate documentation by running `doxygen Doxyfile` from the root directory. This will generate a docs folder with the documentation inside.

Structure
---------

The compiler is split up into several folders (generated folders are starred).

folder      | content
------      | -------
src         | cpp
include     | hpp, ih
test        | code samples, eventually unit tests
lang        | language specification for flex/bison
docs\*      | documentation generated by doxygen
generated\* | generated files by flex/bison (changes will be overwritten)

:octocat:
