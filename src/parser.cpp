/*
 * File: parser.cpp
 * ----------------
 * Implements the parser.h interface.
 */

#include <iostream>
#include <string>
#include "error.h"
#include "exp.h"
#include "parser.h"
#include "strlib.h"
#include "tokenscanner.h"
using namespace std;

/*
 * Implementation notes: parseExp
 * ------------------------------
 * This code just reads an expression and then checks for extra tokens.
 */

Expression *parseExp(TokenScanner & scanner) {
   Expression *exp = readE(scanner);
   if (scanner.hasMoreTokens()) {
      error("parseExp: Found extra token: " + scanner.nextToken());
   }
   return exp;
}


/*
 * Implementation notes: parseStatement
 * ------------------------------
 * This code reads a statement and checks if the first tokens is one of the
 * seven legal statement forms. When a case match is made the constructor
 * for that sublass is called which reads the rest of the tokens in the line
 * and assemble them into a object of the appropriate subclass
 */

Statement *parseStatement(TokenScanner & scanner) {
    Statement *stmt = NULL;
    string nextToken = toUpperCase(scanner.nextToken());
    if (nextToken  == "REM") {
        stmt = new RemStmt(scanner);
    } else if (nextToken  == "LET") {
        stmt = new LetStmt(scanner);
    } else if (nextToken  == "PRINT") {
        stmt = new PrintStmt(scanner);
    } else if (nextToken  == "INPUT") {
        stmt = new InputStmt(scanner);
    } else if (nextToken  == "GOTO") {
        stmt = new GotoStmt(scanner);
    } else if (nextToken  == "IF") {
        stmt = new IfStmt(scanner);
    } else if (nextToken  == "END") {
        stmt = new EndStmt(scanner);
    } else {
        error(nextToken + " is not a valid command type");
    }
    return stmt;
}

/*
 * Implementation notes: readE
 * Usage: exp = readE(scanner, prec);
 * ----------------------------------
 * This version of readE uses precedence to resolve the ambiguity in
 * the grammar.  At each recursive level, the parser reads operators and
 * subexpressions until it finds an operator whose precedence is greater
 * than the prevailing one.  When a higher-precedence operator is found,
 * readE calls itself recursively to read in that subexpression as a unit.
 */

Expression *readE(TokenScanner & scanner, int prec) {
   Expression *exp = readT(scanner);
   string token;
   while (true) {
      token = scanner.nextToken();
      int newPrec = precedence(token);
      if (newPrec <= prec) break;
      Expression *rhs = readE(scanner, newPrec);
      exp = new CompoundExp(token, exp, rhs);
   }
   scanner.saveToken(token);
   return exp;
}

/*
 * Implementation notes: readT
 * ---------------------------
 * This function scans a term, which is either an integer, an identifier,
 * or a parenthesized subexpression.
 */

Expression *readT(TokenScanner & scanner) {
   string token = scanner.nextToken();
   TokenType type = scanner.getTokenType(token);
   if (type == WORD) return new IdentifierExp(token);
   if (type == NUMBER) return new ConstantExp(stringToInteger(token));
   if (token != "(") error("Illegal term in expression");
   Expression *exp = readE(scanner);
   if (scanner.nextToken() != ")") {
      error("Unbalanced parentheses in expression");
   }
   return exp;
}

/*
 * Implementation notes: precedence
 * --------------------------------
 * This function checks the token against each of the defined operators
 * and returns the appropriate precedence value.
 */

int precedence(string token) {
   //if (token == "=") return 1; // I'm still not clear about this!!!!
   if (token == "+" || token == "-") return 1;
   if (token == "*" || token == "/") return 2;
   return 0;
}
