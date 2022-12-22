//
// Created by Rafael on 11/5/2022.
//

#ifndef CMMCOMPILER_LEXICALANALYZER_H
#define CMMCOMPILER_LEXICALANALYZER_H
#include "stdio.h"
#include <string.h>
#include "SymbolTable.h"
#include "ErrorManager.h"

#define BUFFERSIZE 100
#define DEFAULTLEXEM -1
#define ADVANCE 1
#define TRUE 1
#define FALSE 0

void c_deleteSymbolTable(SymbolTable* symbolTable);

//Token struct
typedef struct{
    int token,lexemIndex, lexemSize;
}Token;

//Lexical Analyzer struct
typedef struct {
    FILE* sourceFile;
    char stremBuffer[BUFFERSIZE];
    int bufferIndex, streamLength, lineCounter;

}LexicalAnalyser;

static LexicalAnalyser analyser;
static SymbolTable* reservedWordsSymbolTable;
static SymbolTable* literalsSymbolTable;
static SymbolTable* identifiersSymbolTable;

//Lexical Analyzer functions
extern void buildLexicalAnalyzer(const char* fileName);
LexicalAnalyser * getLexPointer();
void loadStream();
void verifyFileConsistence(const char* fileName);
Token* nextToken();
char getBufferCharacter(int advance);

//SymbolTableFunctions
void buildSymbolTables();
SymbolTable* getReservedWordsSymbolTablePointer();
SymbolTable* getLiteralsSymbolTable();
SymbolTable* getIdentifiersSymbolTable();

//TestFunctions
int isLetter(char c);
int isNumber(char c);
int isWhiteSpace(char c);

extern void clearLexicalAnalyzer();
#endif //CMMCOMPILER_LEXICALANALYZER_H