/*
 * File: program.h
 * ---------------
 * This interface exports a Program class for storing a BASIC program.
 *
 */

#ifndef _program_h
#define _program_h

#include <string>
#include "statement.h"
#include "hashmap.h"
using namespace std;

/*
 * This class stores the lines in a BASIC program.  Each line
 * in the program is stored in order according to its line number.
 * Moreover, each line in the program is associated with two
 * components:
 *
 * 1. The source line, which is the complete line (including the
 *    line number) that was entered by the user.
 *
 * 2. The parsed representation of that statement, which is a
 *    pointer to a Statement.
 */

class Program {

public:

/*
 * Constructor: Program
 * Usage: Program program;
 * -----------------------
 * Constructs an empty BASIC program.
 */

   Program();

/*
 * Destructor: ~Program
 * Usage: usually implicit
 * -----------------------
 * Frees any heap storage associated with the program.
 */

   ~Program();

/*
 * Method: clear
 * Usage: program.clear();
 * -----------------------
 * Removes all lines from the program.
 */

   void clear();

/*
 * Method: addSourceLine
 * Usage: program.addSourceLine(lineNumber, line);
 * -----------------------------------------------
 * Adds a source line to the program with the specified line number.
 * If that line already exists, the text of the line replaces
 * the text of any existing line and the parsed representation
 * (if any) is deleted.  If the line is new, it is added to the
 * program in the correct sequence.
 */

   void addSourceLine(int lineNumber, std::string line);

/*
 * Method: removeSourceLine
 * Usage: program.removeSourceLine(lineNumber);
 * --------------------------------------------
 * Removes the line with the specified number from the program,
 * freeing the memory associated with any parsed representation.
 * If no such line exists, this method simply returns without
 * performing any action.
 */

   void removeSourceLine(int lineNumber);

/*
 * Method: getSourceLine
 * Usage: string line = program.getSourceLine(lineNumber);
 * -------------------------------------------------------
 * Returns the program line with the specified line number.
 * If no such line exists, this method returns the empty string.
 */

   std::string getSourceLine(int lineNumber);

/*
 * Method: setParsedStatement
 * Usage: program.setParsedStatement(lineNumber, stmt);
 * ----------------------------------------------------
 * Adds the parsed representation of the statement to the statement
 * at the specified line number.  If no such line exists, this
 * method raises an error.  If a previous parsed representation
 * exists, the memory for that statement is reclaimed.
 */

   void setParsedStatement(int lineNumber, Statement *stmt);

/*
 * Method: getParsedStatement
 * Usage: Statement *stmt = program.getParsedStatement(lineNumber);
 * ----------------------------------------------------------------
 * Retrieves the parsed representation of the statement at the
 * specified line number.  If no value has been set, this method
 * returns NULL.
 */

   Statement *getParsedStatement(int lineNumber);

/*
 * Method: getFirstLineNumber
 * Usage: int lineNumber = program.getFirstLineNumber();
 * -----------------------------------------------------
 * Returns the line number of the first line in the program.
 * If the program has no lines, this method returns -1.
 */

   int getFirstLineNumber();

/*
 * Method: getNextLineNumber
 * Usage: int nextLine = program.getNextLineNumber(lineNumber);
 * ------------------------------------------------------------
 * Returns the line number of the first line in the program whose
 * number is larger than the specified one, which must already exist
 * in the program.  If no more lines remain, this method returns -1.
 */

   int getNextLineNumber(int lineNumber);

private:

   /*Type for a doubly linked list cell where pointers point to previous cell or next cell in the list */

    struct BasicStruct {
     std::string line = "";
     Statement *parsedLine = NULL;
     int lineNumber = 0;
    };

    struct Cell {
      BasicStruct data;
      Cell *nextlink = NULL;
      Cell *previouslink = NULL;
    };

    /*Instance Variables */
    //XXXX BEGINNING ENTRY FOR DOUBLY LINKED LIST XXXX////
    HashMap<int, Cell *> basicMap;
    Cell *head = NULL;
    Cell *tail = NULL;

    /* Private Methods */

/*
 * Method: insertCellToList();
 * Usage: insertCellToList(cp);
 * ------------------------------------------------------------
 *  Inserts cell into a doubly linked list.
 */


    void insertCellToList(Cell *cp) {
        if(head==NULL) {
            head = cp;
            tail = cp;
        } else if(cp->data.lineNumber > tail->data.lineNumber) {
            cp->previouslink = tail;
            tail->nextlink = cp;
            tail = cp;
        } else if(cp->data.lineNumber < head->data.lineNumber) {
            cp->nextlink = head;
            head->previouslink = cp;
            head = cp;
        } else if(cp->data.lineNumber == head->data.lineNumber &&
                  cp->data.lineNumber == tail->data.lineNumber) {
            delete head;
            head = cp;
            tail = cp;
        } else if(cp->data.lineNumber == head->data.lineNumber) {
            cp->nextlink = head->nextlink;
            head->nextlink->previouslink = cp;
            delete head;
            head = cp;
        } else if(cp->data.lineNumber == tail->data.lineNumber) {
            tail->previouslink->nextlink = cp;
            cp->previouslink = tail->previouslink;
            delete tail;
            tail = cp;
        } else {
            Cell *current = head;
            while(current != tail) {
                if(cp->data.lineNumber < current->nextlink->data.lineNumber) {
                    current->nextlink->previouslink = cp;
                    cp->nextlink = current->nextlink;
                    current->nextlink = cp;
                    cp->previouslink = current;
                    break;
                } else {
                    current = current->nextlink;
                }
            }
        }

    }

/*
 * Method: removeCellFromList();
 * Usage: removeCellFromList(cp);
 * ------------------------------------------------------------
 *  Removes cell from a doubly linked list.
 */



    void removeCellFromList(int lineNumber) {
        if(head->data.lineNumber == lineNumber &&
           tail->data.lineNumber == lineNumber) {
               Cell *temp = head;
               head = NULL;
               tail = NULL;
               delete temp;
        } else if(head->data.lineNumber == lineNumber) {
               Cell *temp = head->nextlink;
               temp->previouslink = NULL;
               delete head;
               head = temp;
       } else if (tail->data.lineNumber == lineNumber) {
               Cell *temp = tail->previouslink;
               temp->nextlink = NULL;
               delete tail;
               tail = temp;
       } else {
            Cell *current = head;
            while(current != tail) {
                if (current->data.lineNumber == lineNumber) {
                    current->previouslink->nextlink = current->nextlink;
                    current->nextlink->previouslink = current->previouslink;
                    break;
                } else {
                    current = current->nextlink;
                }
            }
       }
    }
};

#endif
