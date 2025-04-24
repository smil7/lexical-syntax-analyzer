#define _CRT_SECURE_NO_DEPRECATE
#include <stdio.h>
#include <ctype.h>
#include <iostream>
#include <fstream>
#include <string>
#include <filesystem>
using namespace std;

// Global Declarations
int temp = 0;
int charClass;
char lexeme[100];
char nextChar;
int lexLen;
int token;
int nextToken;
FILE* in_fp, * fopen();

// Lexical parser functions
void addChar();
void getChar();
void getNonBlank();
int lex();
int lex1();

// syntax parser functions
void statements();
void variables();
void display();
void comparsion_operators();
void math_operators();
void for_each_statement();
void is_condition();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define KEYWORD 3  
#define UNKNOWN 99

//Token codes

#define IDENT 12	// identifier
#define BEGIN_END 15
#define RIGHT_BRACKET 40 //]
#define LEFT_BRACKET  41  //[
#define LEFT_PARANTHESIS 42 // (
#define RIGHT_PARANTHESIS 43 // )
#define PERIOD 44 // .
#define COLON 45 // :
#define QUOTATION 46 // "
#define COMMA 47 // ,
#define ASSIGN_OP 48 // =

// arithmetic operations
#define PLUS 20 // plus
#define MINUS 21 // minus
#define DIV  22 // divide
#define MULTI 23 // multiply

// conditional operators
#define LESS 51 // less
#define GREATER 52  // greater
#define LESS_EQUAL 53 // less_equal
#define GREATER_EQUAL 54  // greater_equal
#define EQUAL_TO 55 // equal_to

// types of values
#define INTEGER 27    //int
#define STRING 29 //string

#define RESERVED 78


/* --------------------------------------------- lexical syntax analyzer---------------------------------------------------------- */
/* search_for - a function to search for different operators and parentheses
and return the token */
int search_for(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PARANTHESIS;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PARANTHESIS;
        break;
    case '[':
        addChar();
        nextToken = LEFT_BRACKET;
        break;
    case ']':
        addChar();
        nextToken = RIGHT_BRACKET;
        break;
    case '"':
        addChar();
        nextToken = QUOTATION;
        break;
    case ',':
        addChar();
        nextToken = COMMA;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP;
        break;
    case ':':
        addChar();
        nextToken = COLON;
        break;
    case '.':
        addChar();
        nextToken = PERIOD;
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

/* addChar - a function to add nextChar to lexeme */
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = 0;
    }
    else
        printf("Error - lexeme is too long \n");
}

/* getChar - a function to get the next character of
input and determine its character class */
void getChar() {
    if ((nextChar = getc(in_fp)) != EOF) {
        if (isalpha(nextChar))
            charClass = LETTER;

        else if (nextChar == '$')
            charClass = KEYWORD;

        else if (isdigit(nextChar))
            charClass = DIGIT;

        else
            charClass = UNKNOWN;
    }
    else
        charClass = EOF;
}

/* getNonBlank - a function to call getChar until it
returns a non-whitespace character */
void getNonBlank() {
    while (isspace(nextChar))
        getChar();
}

/* lex and lex1 functions are used for getting each word and converting it to a token based on our library of tokens
   - lex() is only used once in this program.
   - lex1() is mostly used.*/
int lex() {
    lexLen = 0; getNonBlank();
    switch (charClass) {
        
    case LETTER:
        if (token == QUOTATION) {
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = STRING;
            /*token = 0;*/
        }
        else {
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
        }
        break;
       
    case KEYWORD:
        if (nextToken == BEGIN_END) {
            addChar();
            getChar();
            while (charClass == LETTER) {
                addChar();
                getChar();
            }
            nextToken = BEGIN_END;
        }
        else {
            addChar();
            getChar();
            while (charClass == LETTER) {
                addChar();
                getChar();
            }
            nextToken = RESERVED;
        }
        break;
        
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INTEGER;
        break;
        
    case UNKNOWN:
        search_for(nextChar); getChar();
        break;
       
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    } 
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);

    if (nextToken != EOF)
        statements();


    return nextToken;
}

int lex1() {
    lexLen = 0; getNonBlank();
    switch (charClass) {
        
    case LETTER:
        if (token == QUOTATION) {
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = STRING;
            /*token = 0;*/
        }
        else {
            addChar();
            getChar();
            while (charClass == LETTER || charClass == DIGIT) {
                addChar();
                getChar();
            }
            nextToken = IDENT;
        }
        break;
        
    case KEYWORD:
        addChar();
        getChar();
        while (charClass == LETTER) {
            addChar();
            getChar();
        }
        /*cout << "What is the word stored in the lexeme array? " << lexeme << endl;*/
        if ((lexeme[1] == 'b' && lexeme[2] == 'e' && lexeme[3] == 'g' && lexeme[4] == 'i' && lexeme[5] == 'n') ||
            (lexeme[1] == 'e' && lexeme[2] == 'n' && lexeme[3] == 'd'))
            nextToken = BEGIN_END;
        else
            nextToken = RESERVED;
        break;
       
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INTEGER;
        break;
        
    case UNKNOWN:
        search_for(nextChar); getChar();
        break;
    case EOF:
        nextToken = EOF;
        lexeme[0] = 'E';
        lexeme[1] = 'O';
        lexeme[2] = 'F';
        lexeme[3] = 0;
        break;
    }
    printf("Next token is: %d, Next lexeme is %s\n", nextToken, lexeme);
    if (nextToken == QUOTATION) {
        if (token == QUOTATION) {
            cout << "Exit <string>" << endl;
            token = 0;
        }
        else {
            cout << "Enter <string>" << endl;
            token = QUOTATION;
            lex1();
            if (nextToken == STRING)
                lex1();
        }
    }

    return nextToken;
}

/* -------------------------------------------------- syntax analyzer ----------------------------------- */


// <statments> --> <variables>. {<statements>}| <expression>. {<statements>} | <display>. {<statements>} | <is_condition> | <for_each_stmnt>
void statements() {
    printf("Enter <statements>\n");

    if (nextToken == PERIOD || nextToken == QUOTATION) 
        lex1();

    else if (nextToken == IDENT)
        variables();

    else if (nextToken == RESERVED) {
        if (lexeme[1] == 'i' && lexeme[2] == 's')
            is_condition();
        if (lexeme[1] == 'd' && lexeme[2] == 'i' && lexeme[3] == 's' && lexeme[4] == 'p' && lexeme[5] == 'l' && lexeme[6] == 'a' && lexeme[7] == 'y')
            display();
        if ((lexeme[1] == 'f' && lexeme[2] == 'o' && lexeme[3] == 'r'))
            for_each_statement();
        if ((lexeme[1] == 'p' && lexeme[2] == 'l' && lexeme[3] == 'u' && lexeme[4] == 's') ||
            (lexeme[1] == 'm' && lexeme[2] == 'i' && lexeme[3] == 'n' && lexeme[4] == 'u' && lexeme[5] == 's') ||
            (lexeme[1] == 'm' && lexeme[2] == 'u' && lexeme[3] == 'l' && lexeme[4] == 't' && lexeme[5] == 'i' && lexeme[6] == 'p' && lexeme[7] == 'l' && lexeme[8] == 'y') ||
            (lexeme[1] == 'd' && lexeme[2] == 'i' && lexeme[3] == 'v' && lexeme[4] == 'i' && lexeme[5] == 'd' && lexeme[6] == 'e'))
            math_operators();
        if ((lexeme[1] == 'l' && lexeme[2] == 'e' && lexeme[3] == 's' && lexeme[4] == 's') ||
            (lexeme[1] == 'g' && lexeme[2] == 'r' && lexeme[3] == 'e' && lexeme[4] == 'a' && lexeme[5] == 't' && lexeme[6] == 'e' && lexeme[7] == 'r') ||
            (lexeme[1] == 'g' && lexeme[2] == 'r' && lexeme[3] == 'e' && lexeme[4] == 'a' && lexeme[5] == 't' && lexeme[6] == 'e' && lexeme[7] == 'r' && lexeme[8] == '_'
                && lexeme[9] == 'e' && lexeme[10] == 'q' && lexeme[11] == 'u' && lexeme[12] == 'a' && lexeme[13] == 'l') ||
            (lexeme[1] == 'l' && lexeme[2] == 'e' && lexeme[3] == 's' && lexeme[4] == 's' && lexeme[5] == '_'
                && lexeme[6] == 'e' && lexeme[7] == 'q' && lexeme[8] == 'u' && lexeme[9] == 'a' && lexeme[10] == 'l') ||
            (lexeme[1] == 'e' && lexeme[2] == 'q' && lexeme[3] == 'u' && lexeme[4] == 'a' && lexeme[5] == 'l' && lexeme[6] == '_' && lexeme[7] == 't' && lexeme[7] == 'o'))
            comparsion_operators();
        if ((lexeme[1] == 'e' && lexeme[2] == 'a' && lexeme[3] == 'c' && lexeme[4] == 'h') ||
            (lexeme[1] == 'i' && lexeme[2] == 'n'))
            variables();
    }

    printf("Exit <statements>\n");
}

// <variables> --> <identifier> = <integer> | <string> | [<integer> {, <integer>}*] {<variables>}
void variables() {
    printf("Enter <variables>\n");
    lex1();

    while (nextToken == ASSIGN_OP) {
        lex1();
        if (nextToken == ASSIGN_OP)
            lex1();
        else if (nextToken == LEFT_BRACKET)
            lex1();
        else if (nextToken == INTEGER || nextToken == PERIOD || nextToken == QUOTATION)
            break;
        variables();
    }

    while (nextToken == LEFT_BRACKET)
        lex1();

    if (nextToken == INTEGER || nextToken == IDENT)
        variables();

    if (nextToken == RESERVED) {
        if (lexeme[1] == 'i' && lexeme[2] == 's')
            is_condition();
        else if (lexeme[1] == 'd' && lexeme[2] == 'i' && lexeme[3] == 's' && lexeme[4] == 'p' && lexeme[5] == 'l' && lexeme[6] == 'a' && lexeme[7] == 'y')
            display();
        else if ((lexeme[1] == 'f' && lexeme[2] == 'o' && lexeme[3] == 'r'))
            for_each_statement();
        else if ((lexeme[1] == 'p' && lexeme[2] == 'l' && lexeme[3] == 'u' && lexeme[4] == 's') ||
            (lexeme[1] == 'm' && lexeme[2] == 'i' && lexeme[3] == 'n' && lexeme[4] == 'u' && lexeme[5] == 's') ||
            (lexeme[1] == 'm' && lexeme[2] == 'u' && lexeme[3] == 'l' && lexeme[4] == 't' && lexeme[5] == 'i' && lexeme[6] == 'p' && lexeme[7] == 'l' && lexeme[8] == 'y') ||
            (lexeme[1] == 'd' && lexeme[2] == 'i' && lexeme[3] == 'v' && lexeme[4] == 'i' && lexeme[5] == 'd' && lexeme[6] == 'e'))
            math_operators();
        else if ((lexeme[1] == 'l' && lexeme[2] == 'e' && lexeme[3] == 's' && lexeme[4] == 's') ||
            (lexeme[1] == 'g' && lexeme[2] == 'r' && lexeme[3] == 'e' && lexeme[4] == 'a' && lexeme[5] == 't' && lexeme[6] == 'e' && lexeme[7] == 'r') ||
            (lexeme[1] == 'g' && lexeme[2] == 'r' && lexeme[3] == 'e' && lexeme[4] == 'a' && lexeme[5] == 't' && lexeme[6] == 'e' && lexeme[7] == 'r' && lexeme[8] == '_'
                && lexeme[9] == 'e' && lexeme[10] == 'q' && lexeme[11] == 'u' && lexeme[12] == 'a' && lexeme[13] == 'l') ||
            (lexeme[1] == 'l' && lexeme[2] == 'e' && lexeme[3] == 's' && lexeme[4] == 's' && lexeme[5] == '_'
                && lexeme[6] == 'e' && lexeme[7] == 'q' && lexeme[8] == 'u' && lexeme[9] == 'a' && lexeme[10] == 'l') ||
            (lexeme[1] == 'e' && lexeme[2] == 'q' && lexeme[3] == 'u' && lexeme[4] == 'a' && lexeme[5] == 'l' && lexeme[6] == '_' && lexeme[7] == 't' && lexeme[7] == 'o'))
            comparsion_operators();
        else if ((lexeme[1] == 'e' && lexeme[2] == 'a' && lexeme[3] == 'c' && lexeme[4] == 'h') ||
            (lexeme[1] == 'i' && lexeme[2] == 'n')) {
            lex1();
            variables();
        }
    }

    if (nextToken == QUOTATION)
        lex1();

    if (nextToken == IDENT)
        statements();

    if (nextToken == COMMA) {
        lex1();
        variables();
    }

    if (nextToken == RIGHT_BRACKET)
        lex1();

    if (nextToken == RIGHT_PARANTHESIS)
        lex1();

    printf("Exit <variables>\n");
}

// <is_condition> --> $is <compare>: $begin <statements> $end
void is_condition() {
    printf("Enter <is_condition>\n");

    if (nextToken == RESERVED) {
        lex1();
        /*lex1();*/

        if (nextToken == IDENT)
            variables();
    }

    if (nextToken == COLON)
        lex1();

    while (nextToken == BEGIN_END) {
        if (lexeme[1] == 'e' && lexeme[2] == 'n' && lexeme[3] == 'd') 
            break;
        lex1();
        while (nextToken == RESERVED) {
            if (lexeme[1] == 'i' && lexeme[2] == 's') 
                statements();
            else if (lexeme[1] == 'd' && lexeme[2] == 'i' && lexeme[3] == 's' && lexeme[4] == 'p' && lexeme[5] == 'l' && lexeme[6] == 'a' && lexeme[7] == 'y')
                statements();
            else if ((lexeme[1] == 'f' && lexeme[2] == 'o' && lexeme[3] == 'r') ||
                (lexeme[1] == 'e' && lexeme[2] == 'a' && lexeme[3] == 'c' && lexeme[4] == 'h') ||
                (lexeme[1] == 'i' && lexeme[2] == 'n'))
                statements();
        }
        while (nextToken == IDENT) {
            statements();
            lex1();
        }
    }
    if (nextToken == PERIOD) {
        token = BEGIN_END;
        lex1();
    }

    printf("Exit <is_condition>\n");
}

// <for_each_stmnt> --> $for $each <identifier> $in <identifier>: $begin <statements> $end
void for_each_statement() {
    cout << "Enter <for_each_statement>" << endl;

    lex1();
    if (nextToken == RESERVED) {
        if (lexeme[1] == 'e' && lexeme[2] == 'a' && lexeme[3] == 'c' && lexeme[4] == 'h')
            lex1();
        variables();
    }

    if (nextToken == COLON) {
        lex1();
    }

    while (nextToken == BEGIN_END) {
        if (lexeme[1] == 'e' && lexeme[2] == 'n' && lexeme[3] == 'd') {
            token++;
            break;
        }
        lex1();
        while (nextToken == RESERVED) {
            if (lexeme[1] == 'i' && lexeme[2] == 's')
                statements();
            else if (lexeme[1] == 'd' && lexeme[2] == 'i' && lexeme[3] == 's' && lexeme[4] == 'p' && lexeme[5] == 'l' && lexeme[6] == 'a' && lexeme[7] == 'y')
                statements();
            else if ((lexeme[1] == 'f' && lexeme[2] == 'o' && lexeme[3] == 'r') || 
                     (lexeme[1] == 'e' && lexeme[2] == 'a' && lexeme[3] == 'c' && lexeme[4] == 'h') ||
                     (lexeme[1] == 'i' && lexeme[2] == 'n'))
                statements();
        }
        while (nextToken == IDENT) {
            statements();
            lex1();
        }
    }
    if (token == BEGIN_END) {
        lex1();
    }
    else if (token >= 2) {
        token = 0;
        lex1();
    }

    cout << "Exit <for_each_statement>" << endl;
}

// <math_operation> --> <operand> $(plus | minus | multiply | divide | modulus) <operand>
void math_operators() {
    cout << "Enter <math_operators>" << endl;

    if (nextToken == RESERVED) {
        if (lexeme[1] == 'p' && lexeme[2] == 'l' && lexeme[3] == 'u' && lexeme[4] == 's') {
            cout << "Add the two numbers." << endl;
        }

        else if (lexeme[1] == 'm' && lexeme[2] == 'i' && lexeme[3] == 'n' && lexeme[4] == 'u' && lexeme[5] == 's') {
            cout << "Subtract the two numbers" << endl;
        }

        else if (lexeme[1] == 'm' && lexeme[2] == 'u' && lexeme[3] == 'l' && lexeme[4] == 't' && lexeme[5] == 'i' && lexeme[6] == 'p' && lexeme[7] == 'l' && lexeme[8] == 'y') {
            cout << "Multiply the two numbers" << endl;
        }

        else if (lexeme[1] == 'd' && lexeme[2] == 'i' && lexeme[3] == 'v' && lexeme[4] == 'i' && lexeme[5] == 'd' && lexeme[6] == 'e') {
            cout << "Divide the two numbers" << endl;
        }
    }
    lex1();

    if (nextToken == IDENT)
        variables();

    printf("Exit <math_operators>\n");
}

// <compare> --> <operand> $(less | greater| less_equal | greater_equal| equal_to) <operand>
void comparsion_operators() {
    cout << "Enter <comparsion_operators>" << endl;

    if (nextToken == RESERVED) {
        if (lexeme[1] == 'l' && lexeme[2] == 'e' && lexeme[3] == 's' && lexeme[4] == 's') {
            cout << "Is it less than?" << endl;
        }

        else if (lexeme[1] == 'g' && lexeme[2] == 'r' && lexeme[3] == 'e' && lexeme[4] == 'a' && lexeme[5] == 't' && lexeme[6] == 'e' && lexeme[7] == 'r') {
            cout << "Is it greater than?" << endl;
        }

        else if (lexeme[1] == 'g' && lexeme[2] == 'r' && lexeme[3] == 'e' && lexeme[4] == 'a' && lexeme[5] == 't' && lexeme[6] == 'e' && lexeme[7] == 'r' && lexeme[8] == '_'
            && lexeme[9] == 'e' && lexeme[10] == 'q' && lexeme[11] == 'u' && lexeme[12] == 'a' && lexeme[13] == 'l') {
            cout << "Is it greater than or equal to?" << endl;
        }

        else if (lexeme[1] == 'l' && lexeme[2] == 'e' && lexeme[3] == 's' && lexeme[4] == 's' && lexeme[5] == '_'
            && lexeme[6] == 'e' && lexeme[7] == 'q' && lexeme[8] == 'u' && lexeme[9] == 'a' && lexeme[10] == 'l') {
            cout << "Is it less than or equal to?" << endl;
        }
        else if (lexeme[1] == 'e' && lexeme[2] == 'q' && lexeme[3] == 'u' && lexeme[4] == 'a' && lexeme[5] == 'l' && lexeme[6] == '_' && lexeme[7] == 't' && lexeme[7] == 'o') {
            cout << "Is it equal to?" << endl;
        }
    }

    lex1();

    if (nextToken == IDENT)
        variables();

    printf("Exit <comparsion_operators>\n");
}

// $display({<integer> | <string> | <identifier>)} [, {<identifier> | <integer> | <string> }])
void display() {
    printf("Enter <display>\n");

    lex1();

    if (nextToken == LEFT_PARANTHESIS)
        lex1();

    if (nextToken == IDENT)
        variables();

    if (nextToken == RIGHT_PARANTHESIS) {
        cout << "welcommee right part" << endl;
        lex1();
    }

    printf("Exit <display>\n");
}

int main()
{
    if ((in_fp = fopen("example-1.txt", "r")) == NULL) {
        printf("ERROR - cannot open example-1.txt \n");
    }

    else {
        getChar();
        do {
            lex();
        }
        while (nextToken != EOF);
    }
    return 0;
    return 0;
}