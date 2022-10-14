//
// Created by Rafael on 10/14/2022.
//

#include "SymbleTable.h"
void buildLexemBuffer(){
    lexemBuffer.lexemBuffer=malloc(BUFFERDELTA);
    lexemBuffer.bufferLength=BUFFERDELTA;
    lexemBuffer.nextFreeIndex=0;
}

//Return a lexem from Lexem Buffer by a gived index
char* getLexem(int index){

    //Verifying index bound
    if(index<lexemBuffer.nextFreeIndex){

        int lexemSize=0;
        int lexemLimit=index;

        //Giving lexem size to malloc
        while(lexemBuffer.lexemBuffer[lexemLimit] != '\0'){
            lexemSize++;
            lexemLimit++;
        }

        char* lexem= malloc(lexemSize);

        //Copying lexem from buffer to return lexem
        int i=0;
        while(i < lexemSize){
            lexem[i++]=lexemBuffer.lexemBuffer[index++];
        }

        return lexem;

    }else{
        sendSystemError(INDEXOUTOFBOUNDS);
    }
    return NULL;
}
int pushLexem(char* lexem){

    int lexemIndex=0;

    while(lexem[lexemIndex]!='\0'){
        if(lexemBuffer.nextFreeIndex==lexemBuffer.bufferLength){
            reallocLexemBuffer();
        }
        lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex++]=lexem[lexemIndex++];
    }

    lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex++]='\0';

}

void reallocLexemBuffer(){
    lexemBuffer.lexemBuffer=realloc(lexemBuffer.lexemBuffer,BUFFERDELTA);
    lexemBuffer.bufferLength+=BUFFERDELTA;
}