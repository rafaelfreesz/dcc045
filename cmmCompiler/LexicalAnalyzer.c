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

    //Verify if that stream is the last;
    if(analyser.streamLength<BUFFERSIZE){
        analyser.eof=TRUE;
    }

    analyser.bufferIndex=0;

}

Token* nextToken(){
    Token *token= malloc(sizeof(Token));

    char *lexem=(char*)malloc(BUFFERSIZE);
    int lexemIndex=0;
    short foundToken=FALSE;
    short state=0;
    char* characterFound = getBufferCharacter(TRUE);

    while(!foundToken){
        switch (state) {
            case 0:
                if(isNumber(characterFound)){
                    state=45;
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else if(isLetter(characterFound)){
                    state=55;
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else if(isWhiteSpace(characterFound)){
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound==':'){
                    state=1;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound=='%'){
                    state=2;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound=='+'){
                    state=3;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound=='*'){
                    state=4;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound=='\0'){
                    state=5;
                    foundToken=TRUE;
                    //characterFound= getBufferCharacter(TRUE); TODO maybe doesn't work
                }else if(*characterFound=='{'){
                    state=6;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound=='}'){
                    state=7;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound=='['){
                    state=8;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound==']'){
                    state=9;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound=='('){
                    state=10;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound==')'){
                    state=11;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else if(*characterFound=='!'){
                    state=12;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='>'){
                    state=15;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='<'){
                    state=18;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='='){
                    state=21;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='/'){
                    state=26;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='"'){
                    state=31;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='\''){
                    state=33;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='|'){
                    state=36;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='&'){
                    state=39;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='-'){
                    state=42;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound==';'){
                    state=57;
                    characterFound= getBufferCharacter(TRUE);
                    foundToken=TRUE;
                }else{ //TODO tratar vazios tambem
                    sendLexicError(UNEXPECTEDENTRY);
                }
                break;
            case 12:
                if(*characterFound=='='){
                    state=13;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=14;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 15:
                if(*characterFound=='='){
                    state=16;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=17;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 18:
                if(*characterFound=='='){
                    state=20;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=20;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 21:
                if(*characterFound=='='){
                    state=23;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=22;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 36:
                if(*characterFound=='|'){
                    state=37;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=38;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 39:
                if(*characterFound=='&'){
                    state=40;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=41;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 42:
                if(*characterFound=='>'){
                    state=43;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=44;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 55:
                if(isLetter(characterFound) || isNumber(characterFound)){
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=56;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 26:
                if(*characterFound=='*'){
                    state=29;
                    characterFound= getBufferCharacter(TRUE);
                }else if (*characterFound=='/'){
                    state=25;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=27;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 25:
                if (*characterFound=='/'){
                    state=24;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    characterFound= getBufferCharacter(TRUE);
                }
                break;
            case 24:
                if (*characterFound=='n'){
                    state=0;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=25;
                    characterFound= getBufferCharacter(TRUE);
                }
                break;
            case 29:
                if (*characterFound=='*'){
                    state=28;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF);
                }else{
                    characterFound= getBufferCharacter(TRUE);
                }
                break;
            case 28:
                if (*characterFound=='\\'){
                    state=0;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=29;
                    characterFound= getBufferCharacter(TRUE);
                }
                break;
            case 31:
                if (*characterFound=='\\'){
                    state=32;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='"'){
                    state=35;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF);
                }else{
                    characterFound= getBufferCharacter(TRUE);
                }
                break;
            case 32:
                if (*characterFound=='b' || *characterFound=='0'|| *characterFound=='v'|| *characterFound=='\\'|| *characterFound=='"'
                     || *characterFound=='n'|| *characterFound=='r'|| *characterFound=='f'|| *characterFound=='t'|| *characterFound=='a'){
                    state=31;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF);
                }else{
                    state=49;
                    sendLexicError(UNEXPECTEDENTRY);
                }
                break;
            case 33:
                if (*characterFound=='\\'){
                    state=34;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF);
                }else if(*characterFound=='\''){
                    state=35;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=60;
                    characterFound= getBufferCharacter(TRUE);
                }
                break;
            case 34:
                if (*characterFound=='b' || *characterFound=='0'|| *characterFound=='v'|| *characterFound=='\\'|| *characterFound=='"'
                    || *characterFound=='n'|| *characterFound=='r'|| *characterFound=='f'|| *characterFound=='t'|| *characterFound=='a'){
                    state=31;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF);
                }else{
                    state=49;
                    sendLexicError(UNEXPECTEDENTRY);
                }
                break;
            case 60:
                if (*characterFound=='\''){
                    state=35;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF);
                }else{
                    state=49;
                    sendLexicError(UNEXPECTEDENTRY);
                }
                break;
            case 45:
                if (isNumber(*characterFound)){
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='.'){
                    state=51;
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='E'){
                    state=47;
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=46;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 47:
                if(*characterFound=='+'){
                    state=49;
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=48;
                    sendLexicError(MALFORMEDNUMBER);
                }
                break;
            case 49:
                if(isNumber(*characterFound)){
                    state=50;
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=48;
                    sendLexicError(MALFORMEDNUMBER);
                }
                break;
            case 50:
                if(isNumber(*characterFound)){
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=53;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 51:
                if(isNumber(*characterFound)){
                    state=52;
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=54;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;
            case 52:
                if(isNumber(*characterFound)){
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else if(*characterFound=='E'){
                    state=47;
                    lexem[lexemIndex++]=*characterFound;
                    characterFound= getBufferCharacter(TRUE);
                }else{
                    state=53;
                    foundToken=TRUE;
                    characterFound= getBufferCharacter(FALSE);
                }
                break;

        }
    }


    token->token=state;

    if(state==46 || state == 53 || state == 56 || state == 35) {
        lexem[lexemIndex]='\0';
        token->lexemIndex = lexemBuffer.nextFreeIndex;
        pushLexem(lexem);
        token->lexemSize=lexemBuffer.nextFreeIndex;
    }else{
        token->lexemIndex=DEFAULTLEXEM;
    }

    free(lexem);
    return token;

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
                }else if(!isNumber(&c) && !isLetter(&c)){
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


int isLetter(char* c){
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


int isWhiteSpace(char* c){
    return (*c==' ' || *c=='\t' || *c=='\n' || *c=='\r');
}

char* getBufferCharacter(int advance){

    //Testing if buffer reached limit
    if(analyser.bufferIndex>=BUFFERSIZE){
        loadStream(MAINBUFFER);
        analyser.bufferIndex=0;
    }

    if(advance){
        return &analyser.mainBuffer[analyser.bufferIndex++];
    }else{
        return &analyser.mainBuffer[analyser.bufferIndex];
    }
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


void printToken(Token* token){
    printf("--------------Token Data-----------\n");
    printf("Token number: %d\n",token->token);
    printf("Lexem Buffer Index: %d\n",token->lexemIndex);
    printf("Lexem Buffer Size: %d\n",token->lexemSize);
    printf("Lexem Buffer:\n");

    char* tokemLexem= getLexem(token->lexemIndex,token->lexemSize);
    printf("%s\n",tokemLexem);

    printf("-------------------------\n");
    free(tokemLexem);
}