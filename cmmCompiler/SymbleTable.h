//
// Created by Rafael on 10/14/2022.
//

#ifndef CMMCOMPILER_SYMBLETABLE_H
#define CMMCOMPILER_SYMBLETABLE_H

#include <stdlib.h>
#include "ErrorManager.h"

#define BUFFERDELTA 10

typedef struct {
    char* lexemBuffer;
    int bufferLength;
    int nextFreeIndex;
}LexemBuffer;

static LexemBuffer lexemBuffer;

void buildLexemBuffer();
char* getLexem(int lexemIndex, int lexemEnd);
void pushLexem(char* lexem);
void reallocLexemBuffer();
int getNextFreeLexemIndex();
int getBufferLength();

void printLexemBuffer();


#endif //CMMCOMPILER_SYMBLETABLE_H
