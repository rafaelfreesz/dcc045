#ifndef CMMCOMPILER_SymbolTable_H
#define CMMCOMPILER_SymbolTable_H

#include <stdlib.h>
#include "ErrorManager.h"

//Configuration of size
#define BUFFERDELTA 100
#define TABSIZE 499

//Tokens
#define SEMICOLON 57
#define COLON 1
#define MOD 2
#define PLUS 3
#define MULT 4
#define CMMEOF 5
#define NEQ 13
#define NOT 14
#define GEQ 16
#define GREAT 17
#define LESS 19
#define LEQ 20
#define ASSIGN 22
#define EQ 23
#define DIV 27
#define RIGHTPARENTHESES 11
#define LEFTPARENTHESES 10
#define RIGHTBRACKET 9
#define LEFTBRACKET 8
#define RIGHTBRACE 7
#define LEFTBRACE 6
#define POINT 54
#define POINTER 43
#define MINUS 44
#define AND 40
#define AMPERSAND 41
#define OR 37
#define PIPE 38
#define LITERAL 35
#define NUMFLOAT 53
#define NUMINT 46
#define ID 56
#define COMMA 58

//Reserved words Tokens
#define TYPEDEF 561
#define STRUCT 562
#define LONG 563
#define INT 564
#define FLOAT 565
#define BOOL 566
#define CHAR 567
#define DOUBLE 568
#define IF 569
#define WHILE 570
#define SWITCH 571
#define BREAK 572
#define PRINT 573
#define READLN 574
#define RETURN 575
#define THROW 576
#define TRY 577  
#define CATCH 578
#define CASE 579
#define FOR 580


//Definition of the table entry class
class TabEntry{

    public:

        size_t hashValue;
        TabEntry* prox;

        const char* lexem;
        size_t token;
        
        TabEntry(const char* lexem, size_t token); //Constructor

};

//Definition of the Symbol table class
class SymbolTable{

    public:

        TabEntry* symbolTable[TABSIZE];

        //Methods
        SymbolTable();
        size_t hashFunction(const char* lexem);
        void insertKey(const char* lexem, size_t token);
        TabEntry* searchKey(const char* lexem);
        size_t identifierOrReservedWord(const char* lexem);
        ~SymbolTable();

};

//Struct to dynamicaly store lexems along the stream read
typedef struct {
    char* lexemBuffer;
    size_t bufferLength;
    size_t nextFreeIndex;
}LexemBuffer;

//Lexem Buffer Functions
void buildLexemBuffer();
char* getLexem(size_t lexemIndex, size_t lexemEnd);
void pushLexem(char *lexem, size_t lexemSize);
void reallocLexemBuffer();
size_t getNextFreeLexemIndex();
size_t getBufferLength();
void deleteLexemBuffer();


#endif //CMMCOMPILER_SymbolTable_H
