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
char* getLexem(int lexemIndex, int lexemSize){

    //Verifying index bound
    if(lexemIndex!=-1){

        //Copying lexem from buffer to return lexem
        char* lexem= malloc(lexemSize);
        for(int i=lexemIndex,j=0;i<lexemSize;i++,j++){
            lexem[j]=lexemBuffer.lexemBuffer[i];
        }

        return lexem;

    }else{
        sendSystemError(INDEXOUTOFBOUNDS);
    }
    return NULL;
}
void pushLexem(char* lexem){

    int lexemIndex=0;
    while(lexem[lexemIndex]!='\0'){

        //Verify if lexem buffer reached the limit
        if(lexemBuffer.nextFreeIndex==lexemBuffer.bufferLength){
            reallocLexemBuffer();
        }
        lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex++]=lexem[lexemIndex++];
    }

    lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex]='\0';

}

void reallocLexemBuffer(){
    lexemBuffer.lexemBuffer=realloc(lexemBuffer.lexemBuffer,BUFFERDELTA);
    lexemBuffer.bufferLength+=BUFFERDELTA;
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