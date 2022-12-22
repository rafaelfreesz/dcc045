//
// Created by Rafael on 11/5/2022.
//

#ifndef CMMCOMPILER_SYMBOLTABLE_H
#define CMMCOMPILER_SYMBOLTABLE_H


#include <stdlib.h>
#include "ErrorManager.h"

#define BUFFERDELTA 10
#define DEFAULTLEXEM -1
#define TABSIZE 499

#define ID 56
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
#define COMMA 58

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
#define ELSE 581

#ifdef __cplusplus
    class TabEntry{

    public:

        int hashValue;
        TabEntry* prox;

        const char* lexem;
        int token;

        TabEntry(const char* lexem, int token);

    };
#else
    typedef struct TabEntry TabEntry;
#endif

#ifdef __cplusplus
    class SymbolTable{

    public:

        TabEntry* symbolTable[TABSIZE];

        //Methods
        SymbolTable();
        ~SymbolTable();
        void printHashTable();
        int hashFunction(const char* lexem);
        void insertKey(const char* lexem, int token);
        TabEntry* searchKey(const char* lexem);
        int identifierOrReservedWord(const char* lexem);

    };
#else
typedef struct SymbolTable SymbolTable;
#endif

#ifdef __cplusplus
extern "C" {
#endif

    //Struct to dynamicaly store lexems along the stream read
    typedef struct {
        char* lexemBuffer;
        int bufferLength;
        int nextFreeIndex;
    }LexemBuffer;

    static LexemBuffer lexemBuffer;

    //Lexem Buffer Functions
    void buildLexemBuffer();
    char* getLexem(int lexemIndex, int lexemEnd);
    void pushLexem(char *lexem, int lexemSize);
    void reallocLexemBuffer();
    int getNextFreeLexemIndex();
    int getBufferLength();
    void printLexemBuffer();

    //--Wrapper Functions--//
    void c_deleteSymbolTable(SymbolTable* symbolTable);
    SymbolTable* c_buildSymbolTable();
    void c_insertKey(SymbolTable* symbolTable, const char* lexem, int token);
    int c_identifierOrReservedWord(SymbolTable *symbolTable, const char *lexem);
    TabEntry* c_getTabEntry(SymbolTable* symbolTable, int index);
    const char* c_getTabEntryLexem(TabEntry* tabEntry);
    int c_getTabEntryToken(TabEntry* tabEntry);
    TabEntry* c_getTabEntryProx(TabEntry* tabEntry);


#ifdef __cplusplus
}
#endif

#endif //CMMCOMPILER_SYMBOLTABLE_H
