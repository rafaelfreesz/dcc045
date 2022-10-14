//
// Created by Rafael on 10/11/2022.
//

#ifndef CMMCOMPILER_LEXICALANALYZER_H
#define CMMCOMPILER_LEXICALANALYZER_H

#include "stdio.h"
#include <string.h>
#include "SymbleTable.h"
#include "ErrorManager.h"

#define BUFFERSIZE 10
#define MAINBUFFER 0
#define SECONDARYBUFFER 1
#define TRUE 1
#define FALSE 0

//Jogar depois pra tabela de símbolos
#define SEMICOLON 57
#define COLON 1
#define MOD 2
#define PLUS 3
#define MULT 4
#define EOF 5
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
#define ID 46



//Token struct
typedef struct{
    char *token;
    char *lexem;

}Token;

typedef struct {
    FILE* sourceFile;
    char mainBuffer[BUFFERSIZE], secondaryBuffer[BUFFERSIZE];
    int referedBuffer, bufferIndex, streamLength;

}LexicalAnalyser;

static LexicalAnalyser analyser;

//Lexical Analyzer functions
void buildLexicalAnalyzer(char* fileName);
void loadStream(int bufferReference);
int verifyFileConsistence(char* fileName);
Token nextToken();

int isDigit(char* c);
int isNumber(char* c);


void printLexicalAnalyser();

#endif //CMMCOMPILER_LEXICALANALYZER_H
