#ifndef CMMCOMPILER_LEXICALANALYZER_H
#define CMMCOMPILER_LEXICALANALYZER_H

#include "stdio.h"
#include "string.h"
#include "SymbolTable.h"
#include "ErrorManager.h"

#define BUFFERSIZE 512
#define ADVANCE 1
#define TRUE 1
#define FALSE 0

//Token struct
typedef struct{
    size_t token,lexemIndex, lexemSize;
}Token;


//Lexical Analyzer struct
typedef struct {
    FILE* sourceFile;
    char stremBuffer[BUFFERSIZE];
    size_t bufferIndex, streamLength, lineCounter;

}LexicalAnalyser;

//Lexical Analyzer functions
void buildLexicalAnalyzer(const char* fileName);
void deleteLexicalAnalyzer();
void loadStream();
void verifyFileConsistence(const char* fileName);
Token* nextToken();
char getBufferCharacter(size_t advance);

//Management of Symbol tables
void buildSymbolTables();
SymbolTable* getReservedWordsSymbolTablePointer();
SymbolTable* getLiteralsSymbolTable();
SymbolTable* getIdentifiersSymbolTable();

//TestFunctions
size_t isLetter(char c);
size_t isNumber(char c);
size_t isWhiteSpace(char c);



#endif //CMMCOMPILER_LEXICALANALYZER_H



