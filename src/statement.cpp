/*
 * File: statement.cpp
 * -------------------
 * This file implements the constructor and destructor for
 * the Statement class itself.  Your implementation must do
 * the same for the subclasses you define for each of the
 * BASIC statements.
 */

#include <string>
#include "statement.h"
#include "exp.h"
#include "parser.h"
#include "simpio.h"
#include "string.h"
using namespace std;

/* Constant Variable  */

const int STOP = -999;

/* Implementation of the Statement class
 * -------------------------------------
 * The Statement class itself implements only those methods that
 * are not designated as pure virtual methods.
 */

Statement::Statement() {
    /* Empty */
}

Statement::~Statement() {
    /* Empty */
}

/*
 * Implementation notes: RemStmt
 * -----------------------------
 * The RemStmt class creates an object that handles comments within BASIC code.
 * Nothing is stored and so the subclass is trivial.
 *
 */

RemStmt::RemStmt(TokenScanner & scanner){

}

RemStmt::~RemStmt() {
    delete exp;
}

void RemStmt::execute(EvalState & state) {

}


/*
 * Implementation notes: LetStmt
 * -----------------------------
 * The LetStmt subclass creates an object that handles assignment operations in
 * BASIC. The scanner reads the first token as a variable name, ignores the equal
 * sign that follows - throwing an error if one does not - and evaluates the
 * expression on the right hand side of the equals sign. This variable and value
 * are stored as key and value in the symbolMap which belongs to the EvalState Class
 */

LetStmt::LetStmt(TokenScanner & scanner){
    var = scanner.nextToken();
    if(scanner.nextToken() != "=") {
        error("Improper LET statement. Enter line in the form of LET variable = expression");
    } else {
        exp = readE(scanner, 0);
        if (scanner.hasMoreTokens()) {
            error("Extraneous token " + scanner.nextToken());
        }
    }
}

LetStmt::~LetStmt() {
    delete exp;
}

void LetStmt::execute(EvalState & state) {
    state.setValue(var, exp->eval(state));
}

/*
 * Implementation notes: PrintStmt
 * -----------------------------
 * The PrintStmt subclass creates an object that stores the parsed
 * representation of the expression of an instance variable. The execute
 * method prints the expression to the console.
 */

PrintStmt::PrintStmt(TokenScanner & scanner){
    exp = readE(scanner, 0);
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

PrintStmt::~PrintStmt() {
    delete exp;
}

void PrintStmt::execute(EvalState & state) {
    cout << exp->eval(state) << endl;
}

/*
 * Implementation notes: InputStmt
 * -----------------------------
 * The InputStmt subclass takes a variable name from the console and then prompts
 * the user for a value to associate with that variable name. The program insists
 * that the user enters an integer otherwise an error is thown. In this version the
 * user cannot define a variable as a function of other previously defined variables.
 */

InputStmt::InputStmt(TokenScanner & scanner){
    var = scanner.nextToken();
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

InputStmt::~InputStmt() {
    delete exp;
}

void InputStmt::execute(EvalState & state) {
    value = getInteger(" ? ");
    state.setValue(var, value);
}
/*
 * Implementation notes: GotoStmt
 * -----------------------------
 *
 */

GotoStmt::GotoStmt(TokenScanner & scanner){
    lineNumber = stringToInteger(scanner.nextToken());
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

GotoStmt::~GotoStmt() {
    delete exp;
}

void GotoStmt::execute(EvalState & state) {
    state.setCurrentLine(lineNumber);
}

/*
 * Implementation notes: IfStmt
 * -----------------------------
 *
 */

IfStmt::IfStmt(TokenScanner & scanner){
    expLhs = readE(scanner, 0);
    op = scanner.nextToken();
    expRhs = readE(scanner, 0);
    if(toUpperCase(scanner.nextToken()) != "THEN") {
        error("Illegal Format: condition must be followed by THEN");
    }
    lineNumber = stringToInteger(scanner.nextToken());
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
}

IfStmt::~IfStmt() {
    delete expLhs;
    delete expRhs;
}

void IfStmt::execute(EvalState & state) {
    int evalLeft = expLhs->eval(state);
    int evalRight = expRhs->eval(state);
    if(((op == "=") && (evalLeft == evalRight)) ||
      ((op == ">") && (evalLeft > evalRight)) ||
      ((op == "<") && (evalLeft < evalRight)))   {
        state.setCurrentLine(lineNumber);
    }
}


/*
 * Implementation notes: EndStmt
 * -----------------------------
 *
 */

EndStmt::EndStmt(TokenScanner & scanner){
    if (scanner.hasMoreTokens()) {
        error("Extraneous token " + scanner.nextToken());
    }
    stopCondition = STOP;
}

EndStmt::~EndStmt() {
    delete exp;
}

void EndStmt::execute(EvalState & state) {
    state.setCurrentLine(stopCondition);
}














