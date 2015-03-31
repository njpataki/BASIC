
/*
 * File: program.cpp
 * -----------------
 * This file is a stub implementation of the program.h interface
 *
 */

#include <string>
#include "program.h"
#include "statement.h"
#include "hashmap.h"
#include "error.h"
using namespace std;

Program::Program() {

}

Program::~Program() {

}

void Program::clear() {
    basicMap.clear();
    head = NULL;
    tail = NULL;
}

void Program::addSourceLine(int lineNumber, string line) {
    Cell *cp = new Cell;
    cp->data.lineNumber = lineNumber;
    cp->data.line = line;
    insertCellToList(cp);
    basicMap.put(lineNumber, cp);

}

void Program::removeSourceLine(int lineNumber) {
    if(basicMap.containsKey(lineNumber)) {
        removeCellFromList(lineNumber);
        basicMap.remove(lineNumber);
    }
}

string Program::getSourceLine(int lineNumber) {
    if (basicMap.containsKey(lineNumber)) {
        return basicMap.get(lineNumber)->data.line;
    } else {
        return "";
    }
}

void Program::setParsedStatement(int lineNumber, Statement *stmt) {
    if(!basicMap.containsKey(lineNumber)) {
        error("This line number does not exist");
    } else {
        basicMap[lineNumber]->data.parsedLine = stmt;
    }
}

Statement *Program::getParsedStatement(int lineNumber) {
    if(!basicMap.containsKey(lineNumber)) {
        return NULL;
    } else {
        return basicMap.get(lineNumber)->data.parsedLine;
    }
}

int Program::getFirstLineNumber() {
   if (!basicMap.isEmpty()) {
       return head->data.lineNumber;
   } else {
       return -1;
   }
}

int Program::getNextLineNumber(int lineNumber) {
    if(!basicMap.containsKey(lineNumber)) return -1;
    if(basicMap.get(lineNumber)->nextlink == NULL) {
        return -1;
    } else {
        return basicMap.get(lineNumber)->nextlink->data.lineNumber;
    }
}
