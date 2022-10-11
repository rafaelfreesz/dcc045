//
// Created by Rafael on 10/11/2022.
//

#include "LexicalAnalyzer.h"


void buildLexicalAnalyzer(char* fileName){

    if((analyser.sourceFile= fopen(fileName,"r"))==NULL){
        sendSystemError(FILENOTFOUND);
    }

    analyser.bufferRef.referedBuffer=MAINBUFFER;
    analyser.bufferRef.bufferIndex=0;

}

Token nextToken(){
    Token token;
    char lexem=malloc(BUFFERSIZE);
    short foundToken=0;

    while(!foundToken){




    }


}