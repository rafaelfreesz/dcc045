//
// Created by Rafael on 10/14/2022.
//

#ifndef CMMCOMPILER_SYMBLETABLE_H
#define CMMCOMPILER_SYMBLETABLE_H

#include <stdlib.h>
#include "ErrorManager.h"

#define BUFFERDELTA 10
#define DEFAULTLEXEM -1
/*
 * TODO Três tabelas de símbolos: Palavras reservadas, identificadores e literais;
 * */
typedef struct {
    char* lexemBuffer;
    int bufferLength;
    int nextFreeIndex;
}LexemBuffer;

static LexemBuffer lexemBuffer;

void buildLexemBuffer();
char* getLexem(int lexemIndex, int lexemEnd);
void pushLexem(char *lexem, int lexemSize);
void reallocLexemBuffer();
int getNextFreeLexemIndex();
int getBufferLength();
LexemBuffer * getLexemBuffer();

void printLexemBuffer();


#endif //CMMCOMPILER_SYMBLETABLE_H
