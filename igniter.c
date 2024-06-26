#include <stdio.h>
#include <stdlib.h>
#include "utils.h"
#include "opcodes.h"

struct expr {
    int opcode;
    char *operandName1;
    char *operandName2;
};

int main(int argc, char **argv) {

    // only support one input file with no options for now
    if (argc != 2) {
        printf("Usage: igniter <name of file to be compiled>");
        return 1;
    }

    char *filepath = argv[1];

    // load the file from memory, and parse it separately: leave IO ASAP
    // dynamic mem
    char *program = getFileChars(filepath);
    
    int progPtr = 0;
    int tokenPtr = 0;
    char currentChar = program[0];
    char tokenBuf[255];
    struct expr currentExpr;

    /*
    char * -> token
    token -> expr
    expr -> program

    token : char *
    expr : expr
    program : expr
    */
    
    // start parsing
    while (currentChar != '\0') {

        if (currentChar == 32) { printf("space "); }
        // lower and upppercase letters + underscore
        else if (currentChar >= 48 && currentChar <= 57
                 || currentChar >= 65 && currentChar <= 90
                 || currentChar == 95
                 || currentChar >= 97 && currentChar <= 122) {
            tokenBuf[tokenPtr++] = currentChar;
            printf("%c ", currentChar);
        }
        else {
            // also consider the context of the current characters - they could be comments or string literals
            // ignore this case for now

            switch (currentChar) {
                case 10: tokenPtr = 0; printf("CR "); break; // ignore
                case 13: tokenPtr = 0; printf("LF "); break; // ignore
                case 34: tokenPtr = 0; printf("\" "); break; // start of string
                case 39: printf("' "); break; // start of string
                case 40: printf("( "); break; // start of new expression
                case 41: printf(") "); break; // end of new expression
                case 44: printf(", "); break; // parameter separator
                case 46: printf(". "); break; // decimal separator
                case 58: printf(": "); break; // function type declare operator
                case 59: printf("; "); break; // end of sentence
                case 91: printf("[ "); break; // start of array
                case 92: printf("\\ "); break; // not too sure what this should be yet
                case 93: printf("] "); break; // end of array
                case 123: printf("{ "); break; // start of code block in local context
                case 125: printf("} "); break; // end of code block in local context

                // when encountering arithmetic and logic:
                // when scan on opcode and left operand (operand1) is finished, there are three valid possibilities
                // for what's after the right operand (operand2):  
                // 1. another arithmetic or logic operator exists; or
                // 2. a start of new expression operator `(` exists; or
                // 3. if a semicolon exists.
                // for case 1, check the precedence of the current operator against the next operator.
                // if the precedence is lower, bind everything on the left of the current sentence to operand 2
                // of the current expr.
                // if the precedence is higher, remember the name of the current expr and bind it to operand 1
                // of the next expr.
                // for case 2, bind everything in the new expression to operand 2 of the current expr.
                // for case 3, it's trivial.
                case 33: printf("! "); break; // start of unary NOT, or it could be the start of binary NEQ
                case 38: printf("& "); break; // start of binary AND
                case 124: printf("| "); break; // implying binary OR
                case 43: printf("+ "); break; // implying binary ADD
                case 45: printf("- "); break; // implying binary SUB
                case 42: printf("* "); break; // implying binary MULT
                case 47: printf("/ "); break; // implying binary DIV
                case 60: printf("< "); break; // implying binary LT, or it could be the start of binary LEQ
                case 61: printf("= "); break; // implying value assignment, or it could be the start of binary EQ
                case 62: printf("> "); break; // implying binary GT, or it could be the start of binary GEQ
                default: printf("Unknown token "); break;
            }
        }

        currentChar = program[++progPtr];
    }
    printf("\n");
    free(program);

    return 0;
}
