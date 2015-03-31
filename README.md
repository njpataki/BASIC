# BASIC
This program implements a minimal BASIC interpreter built with code for the integer expression evaluator written by 
Eric Roberts and contained in Chapter 19 of Programming Abstractions in C++ (found for free online).

The main part of this implementation consisted of two main projects:

1. Defining the Statement class hierarchy, i.e. building an abstract superclass and the related subclasses for BASIC's main command line tools. These included simple statements such as RUN, PRINT, LIST, and CLEAR and much more interesting control statements like GOTO which forces an unconditional change in the program flow and the canonical IF-THEN statement. See statement.h and statement.cpp in the 'src' folder.

2. Building out the private section of the Program class and associated methods. See program.h and program.cpp files in the 'src' folder. Various constraints were put on my team in terms of the interpreter's efficiency, i.e. running time for search methods, so data structures had to be built and employed strategically. We utilized a hash map whose values were pointers to a doubly-linked list. 




