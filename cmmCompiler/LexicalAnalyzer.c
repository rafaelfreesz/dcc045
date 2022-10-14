//
// Created by Rafael on 10/11/2022.
//

#include "LexicalAnalyzer.h"


void buildLexicalAnalyzer(char* fileName){

    verifyFileConsistence(fileName);

    if((analyser.sourceFile= fopen(fileName,"r"))==NULL){
        sendSystemError(FILENOTFOUND);
    }

    analyser.referedBuffer=MAINBUFFER;
    loadStream(analyser.referedBuffer);

}

void loadStream(int bufferReference){

    if(bufferReference==MAINBUFFER){
        analyser.streamLength= fread(analyser.mainBuffer,1,BUFFERSIZE,analyser.sourceFile);
    }else{
        analyser.streamLength= fread(analyser.secondaryBuffer,1,BUFFERSIZE,analyser.sourceFile);
    }
    analyser.bufferIndex=0;

}

Token nextToken(){
    Token token;
    char lexem=malloc(BUFFERSIZE);
    short foundToken=0;

    while(!foundToken){




    }


}

int verifyFileConsistence(char* fileName){

    int i=0;
    int state=0;
    char c= fileName[i];

    while(state!=5 && state!=6){
        switch (state) {
            case 0:
                if(c=='.'){
                    state=1;
                }else if(!isNumber(&c) && !isDigit(&c)){
                    state=6;
                }
                break;
            case 1:
                if(c=='c'){
                    state=2;
                }else{
                    state=6;
                }
                break;
            case 2:
                if(c=='m'){
                    state=3;
                }else{
                    state=6;
                }
                break;
            case 3:
                if(c=='m'){
                    state=4;
                }else{
                    state=6;
                }
                break;

            case 4:
                if(c=='\0'){
                    state=5;
                }else{
                    state=6;
                }
                break;
        }
        c=fileName[++i];
    }

    if(state==6){
        sendSystemError(FILENOTSUPPORTED);
    }

}


int isDigit(char* c){
    if((*c>64 && *c<91) || (*c>96 && *c<123)){
        return TRUE;
    }
    return FALSE;
}

int isNumber(char* c){
    if(*c>47 && *c<58){
        return TRUE;
    }
    return FALSE;
}

void printLexicalAnalyser(){
    printf("--------------ALex Data-----------\n");
    printf("MainBuffer: %s\n",analyser.mainBuffer);
    printf("SecondaryBuffer: %s\n",analyser.secondaryBuffer);

    if(analyser.referedBuffer==MAINBUFFER) {
        printf("ReferedBuffer: MAINBUFFER\n");
    }else{
        printf("ReferedBuffer: SECONDARYBUFFER\n");
    }

    printf("StreamLength: %d\n",analyser.streamLength);
    printf("BufferIndex: %d\n",analyser.bufferIndex);
    printf("-------------------------\n");
}