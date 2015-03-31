# BASIC

This program is written in C++ and implements a minimal BASIC interpreter built with code for the integer expression evaluator written by Eric Roberts (contained in Chapter 19 of Programming Abstractions in C++ which can be found for free online). My original code is contained in the 'src' folder within the statement.cpp, statement.h, program.cpp, program.h, and BASIC.cpp files. All the support files necessary for a clean execution have been included. To execute Basic.cpp:

1. Download Qt Creator (a free platform) or use any other platform you prefer.
2. Right click on 'Assignment6.pro' file and direct the cursor to Qt Creator or your preferred platform.
3. Find Basic.cpp (located within the 'src' folder) and execute the code.

The main part of this implementation consisted of two main projects:

1. Defining the Statement class hierarchy, i.e. building an abstract superclass and the related subclasses for BASIC's main command line tools. These included simple statements such as RUN, PRINT, LIST, and CLEAR and much more interesting control statements like GOTO which forces an unconditional change in the program flow and the canonical IF-THEN statement. See statement.h and statement.cpp in the 'src' folder.

2. Building out the private section of the Program class and associated methods. See program.h and program.cpp files in the 'src' folder. Various constraints were put on my team in terms of the interpreter's efficiency, i.e. running time for search methods, so data structures had to be built and employed strategically. We utilized a hash map whose values were pointers to a doubly-linked list. 




