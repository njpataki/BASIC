/*
 * File: Basic.cpp
 * ---------------
 * Name: NICHOLAS PATAKI
 * Section: KEREM
 * Assignment #6.
 *
 * Extension: Created doubly linked cell with previous link and next link to make insertion and deletion more efficient
 */

#include <cctype>
#include <iostream>
#include <string>
#include "console.h"
#include "exp.h"
#include "parser.h"
#include "program.h"
#include "tokenscanner.h"
#include "simpio.h"
#include "strlib.h"
#include "statement.h"
using namespace std;

/* Constant Variable  */

const int STOP = -999;

/* Function prototypes */

void processLine(string line, Program & program, EvalState & state);
bool userEntersProgramLine(string token);

/* Main program */

int main() {
    EvalState state;
    Program program;
    cout << "Welcome to BASIC. Type HELP if you need assistance." << endl;
    while (true) {
        try {
            processLine(getLine(), program, state);
        } catch (ErrorException & ex) {
            cerr << "Error: " << ex.getMessage() << endl;
        }
    }
    return 0;
}

/*
 * Function: processLine
 * Usage: processLine(line, program, state);
 * -----------------------------------------
 * Processes a single line entered by the user.  In this version,
 * the implementation does exactly what the interpreter program
 * does in Chapter 19: read a line, parse it as an expression,
 * and then print the result.  In your implementation, you will
 * need to replace this method with one that can respond correctly
 * when the user enters a program line (which begins with a number)
 * or one of the BASIC commands, such as LIST or RUN.
 */

void processLine(string line, Program & program, EvalState & state) {

    TokenScanner scanner;
    scanner.ignoreWhitespace();
    scanner.scanNumbers();
    scanner.setInput(line);
    string firstToken = toUpperCase(scanner.nextToken());
    int lineNumber = 0;
    Statement *stmt = NULL;

    if(stringIsReal(firstToken) && scanner.hasMoreTokens()) {

        lineNumber = stringToInteger(firstToken);
        stmt = parseStatement(scanner);
        program.addSourceLine(lineNumber, line);
        program.setParsedStatement(lineNumber, stmt);

    } else if (stringIsReal(firstToken) && !scanner.hasMoreTokens()){

        lineNumber = stringToInteger(firstToken);
        program.removeSourceLine(lineNumber);

    } else if (((firstToken == "INPUT") || (firstToken == "PRINT") || (firstToken == "LET"))
               && scanner.hasMoreTokens()) {

        scanner.saveToken(firstToken);
        stmt = parseStatement(scanner);
        stmt->execute(state);

    } else if (firstToken == "LIST" && !scanner.hasMoreTokens()) {

        lineNumber = program.getFirstLineNumber();
        while (lineNumber != -1) {
            cout << program.getSourceLine(lineNumber) << endl;
            lineNumber = program.getNextLineNumber(lineNumber);
        }

    } else if (firstToken == "CLEAR" && !scanner.hasMoreTokens()) {

        program.clear();
        state.clearVariableList();


    } else if (firstToken == "RUN") {

        lineNumber = program.getFirstLineNumber();
        state.setCurrentLine(lineNumber);
        while((lineNumber == -1) || (state.getCurrentLine() != STOP)) {
            if(lineNumber == -1) break;
            stmt = program.getParsedStatement(state.getCurrentLine());
            lineNumber = program.getNextLineNumber(state.getCurrentLine());
            state.setCurrentLine(lineNumber);
            stmt->execute(state);
        }

    } else if (firstToken == "HELP" && !scanner.hasMoreTokens()) {

        cout << "Available commands: " << endl;
        cout << "   RUN     - Runs the program" << endl;
        cout << "   LIST    - Lists the program" << endl;
        cout << "   CLEAR   - Clears the program" << endl;
        cout << "   HELP    - Prints this message" << endl;
        cout << "   QUIT    - Exits from the BASIC interpreter" << endl;
        cout << "   REM     - This statement is used for comments. Any text on the" << endl;
        cout << "             line after the keyword REM is ignored." << endl;
        cout << "   LET     - This statement is an assignment statement. The LET keyword is" << endl;
        cout << "             followed by a variable name, an equal sign, and an expression." << endl;
        cout << "   PRINT   - This statement is followed by an expression, whose value" << endl;
        cout << "             is printed to the console" << endl;
        cout << "   INPUT   - This statement is followed by a variable name and prompts" << endl;
        cout << "             the user for an input which is read and stored in the variable." << endl;
        cout << "   GOTO    - This statement is follwed by a line number and forces an" << endl;
        cout << "             unconditional change in the control flow of the program." << endl;
        cout << "   IF      - This statement has the syntax IF exp1 op exp2 THEN n where" << endl;
        cout << "             exp1 and exp2 are expressions and op is one of the conditional" << endl;
        cout << "             operators =, <, or >. If the condition holds, the program should " << endl;
        cout << "             continue from line n just as in the GOTO statement. If not, the" << endl;
        cout << "             program continues onto the next line." << endl;
        cout << "   END     - This statement marks the end of the program." << endl;


    } else if (firstToken == "QUIT" && !scanner.hasMoreTokens()) {

        bool userQuit = getYesOrNo("Are you sure you want to quit the program? ");
        if (userQuit) exit(0);

    } else {

        cout << "That command is not recognized. Please try again or ask for HELP" << endl;

    }
}

