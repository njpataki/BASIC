/*
 * File: statement.h
 * -----------------
 * This file defines the Statement abstract type.  In
 * the finished version, this file will also specify subclasses
 * for each of the statement types.  As you design your own
 * version of this class, you should pay careful attention to
 * the exp.h interface specified in Chapter 17, which is an
 * excellent model for the Statement class hierarchy.
 */

#ifndef _statement_h
#define _statement_h

#include "evalstate.h"
#include "exp.h"
#include "tokenscanner.h"

/*
 * Class: Statement
 * ----------------
 * This class is used to represent a statement in a program.
 * The model for this class is Expression in the exp.h interface.
 * Like Expression, Statement is an abstract class with subclasses
 * for each of the statement and command types required for the
 * BASIC interpreter.
 */

class Statement {

public:

/*
 * Constructor: Statement
 * ----------------------
 * The base class constructor is empty.  Each subclass must provide
 * its own constructor.
 */

   Statement();

/*
 * Destructor: ~Statement
 * Usage: delete stmt;
 * -------------------
 * The destructor deallocates the storage for this expression.
 * It must be declared virtual to ensure that the correct subclass
 * destructor is called when deleting a statement.
 */

   virtual ~Statement();

/*
 * Method: execute
 * Usage: stmt->execute(state);
 * ----------------------------
 * This method executes a BASIC statement.  Each of the subclasses
 * defines its own execute method that implements the necessary
 * operations.  As was true for the expression evaluator, this
 * method takes an EvalState object for looking up variables or
 * controlling the operation of the interpreter.
 */

   virtual void execute(EvalState & state) = 0;

};


/*
 * SubClass: RemStmt
 * ----------------------
 * This subclass does nothing since comments within the code
 * are for the client of BASIC and not for the program.
 */

class RemStmt : public Statement {

public:

/*
 * Constructor: RemStmt
 * Usage: Expression *exp = new RemStmt(scanner)
 * ----------------------------------
 *
 */

    RemStmt(TokenScanner & scanner);

/* Prototypes for the virtual methods overridden by this class */
    virtual ~RemStmt();
    virtual void execute(EvalState & state);

private:
    Expression *exp;
};


/*
 * SubClass: LetStmt
 * ----------------------
 * This subclass stores the value exp in the variable on the right hand side
 * of the equal sign to the symbolMap associated with the EvalState Class.
 */

class LetStmt : public Statement {

public:

/*
 * Constructor: LetStmt
 * Usage: Expression *exp = new LetStmt(scanner)
 * ----------------------------------
 *
 */

    LetStmt(TokenScanner & scanner);

/* Prototypes for the virtual methods overridden by this class */

    virtual ~LetStmt();
    virtual void execute(EvalState & state);

private:
    Expression *exp;
    std::string var;
};


/*
 * SubClass: PrintStmt
 * ----------------------
 * This subclass prints an expression to the console
 */

class PrintStmt : public Statement {

public:

/*
 *  Constructor: PrintStmt
 *  Usage: Expression *exp = new PrintStmt(scanner)
 *  ----------------------------------------------
 *  Prints the value exp to the console
 */

    PrintStmt(TokenScanner & scanner);


/*  Prototypes for the virtual methods overridden by this class */
    virtual ~PrintStmt();
    virtual void execute(EvalState & state);

private:
    Expression *exp;
};

/*
 * SubClass: InputStmt
 * ----------------------
 * This subclass prompts the user of the program for an expression after s/he
 * has entered a variable name. The value exp is then stored in the symbolMap associated
 * with the EvalState subclass.
 */

class InputStmt : public Statement {

public:

/*
 * Constructor: InputStmt
 * Usage: Expression *exp = new InputStmt(scanner)
 * ----------------------------------
 * Stores the value exp in EvalState's symbol map. The client of the program
 * must enter a variable name.
 */

    InputStmt(TokenScanner & scanner);

/* Prototypes for the virtual methods overridden by this class */
    virtual ~InputStmt();
    virtual void execute(EvalState & state);

private:
    Expression *exp;
    int value;
    std::string var;
};


/*
 * SubClass: GotoStmt
 * ----------------------
 *
 */

class GotoStmt : public Statement {

public:

/*
 * Constructor:
 * Usage:
 * ----------------------------------
 *
 */

    GotoStmt(TokenScanner & scanner);

/* Prototypes for the virtual methods overridden by this class */
    virtual ~GotoStmt();
    virtual void execute(EvalState & state);

private:
    int lineNumber;
    Expression *exp;
};




/*
 * SubClass: IfStmt
 * ----------------------
 *
 */

class IfStmt : public Statement {

public:

/*
 * Constructor:
 * Usage:
 * ----------------------------------
 *
 */
    IfStmt(TokenScanner & scanner);

/* Prototypes for the virtual methods overridden by this class */
    virtual ~IfStmt();
    virtual void execute(EvalState & state);

private:
    Expression *expLhs;
    Expression *expRhs;
    std::string op;
    int lineNumber;
};


/*
 * SubClass: EndStmt
 * ----------------------
 *
 */

class EndStmt : public Statement {

public:

/*
 * Constructor:
 * Usage:
 * ----------------------------------
 *
 */


    EndStmt(TokenScanner & scanner);

/* Prototypes for the virtual methods overridden by this class */
    virtual ~EndStmt();
    virtual void execute(EvalState & state);

private:
    int stopCondition;
    Expression *exp;
};


#endif
