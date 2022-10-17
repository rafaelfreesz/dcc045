//
// Created by Rafael on 10/14/2022.
//

#include "SymbleTable.h"
void buildLexemBuffer(){
    lexemBuffer.lexemBuffer=(char*)malloc(BUFFERDELTA);
    lexemBuffer.bufferLength=BUFFERDELTA;
    lexemBuffer.nextFreeIndex=0;
}

//Return a lexem from Lexem Buffer by a gived index
char* getLexem(int lexemIndex, int lexemEnd){

    //Verifying index bound
    if(lexemIndex!=DEFAULTLEXEM){ //TODO Ao invez de DEFAULTLEXEM, voltar o prórpio caracter

        //Copying lexem from buffer to return lexem
        char* lexem= malloc(lexemEnd + 1);
        int j=0;
        for(int i=lexemIndex; i < lexemEnd; i++,j++){
            lexem[j]=lexemBuffer.lexemBuffer[i];
        }
        lexem[j]='\0';

        return lexem;

    }else{
        //sendSystemError(INDEXOUTOFBOUNDS);
    }
    return NULL;
}
void pushLexem(char *lexem, int lexemSize) {

    LexemBuffer * pointer=&lexemBuffer;//TODO APAGAR

    //Verify if lexem buffer reached the limit
    while(lexemBuffer.nextFreeIndex+lexemSize>lexemBuffer.bufferLength){
        reallocLexemBuffer();
    }

    for(int i=0;i<lexemSize;i++){
        lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex++]=lexem[i];
    }

    lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex]='_';

}

void reallocLexemBuffer(){
    lexemBuffer.bufferLength+=BUFFERDELTA;
    lexemBuffer.lexemBuffer=realloc(lexemBuffer.lexemBuffer,lexemBuffer.bufferLength);
}

int getNextFreeLexemIndex(){
    return lexemBuffer.nextFreeIndex;
}
int getBufferLength(){
    return lexemBuffer.bufferLength;
}
LexemBuffer * getLexemBuffer(){
    return &lexemBuffer;
}
void printLexemBuffer(){
    printf("--------------Lexem Buffer Data-----------\n");

    printf("Buffer Length: %d\n", lexemBuffer.bufferLength);
    printf("Next Free Index: %d\n", lexemBuffer.nextFreeIndex);
    printf("LexemBuffer: \n");

    for(int i=0;i<lexemBuffer.nextFreeIndex;i++){
        printf("%c",lexemBuffer.lexemBuffer[i]);
    }
    printf("\n");
}