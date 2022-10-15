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
#define DEFAULTLEXEM -1
#define TRUE 1
#define FALSE 0

//Jogar depois pra tabela de símbolos
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
#define ID 46



//Token struct
typedef struct{
    int token,lexemIndex, lexemSize;
}Token;

typedef struct {
    FILE* sourceFile;
    char stremBuffer[BUFFERSIZE];
    int bufferIndex, streamLength, eof;

}LexicalAnalyser;

static LexicalAnalyser analyser;

//Lexical Analyzer functions
void buildLexicalAnalyzer(char* fileName);
void loadStream();
int verifyFileConsistence(char* fileName);
Token* nextToken();
char *getBufferCharacter(int advance);

int isLetter(char* c);
int isNumber(char* c);
int isWhiteSpace(char* c);


//Testing Funcions
void printLexicalAnalyser();
void printToken(Token* token);
char* translateState(int state);

#endif //CMMCOMPILER_LEXICALANALYZER_H
