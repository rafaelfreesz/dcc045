//
// Created by Rafael on 11/5/2022.
//

#include "LexicalAnalyzer.h"
#include "SymbolTable.h"
#include "ErrorManager.h"

//Function to build Lexical Analyzer
void buildLexicalAnalyzer(const char* fileName){

    verifyFileConsistence(fileName);

    if((analyser.sourceFile= fopen(fileName,"r"))==NULL){
        sendSystemError(FILENOTFOUND);
    }

    buildSymbolTables();
    loadStream();
    analyser.lineCounter=1;

}

//Function to build Symbol Tables
void buildSymbolTables(){

    //Reserved words
    reservedWordsSymbolTable = c_buildSymbolTable();
    c_insertKey(reservedWordsSymbolTable, "typedef", TYPEDEF);
    c_insertKey(reservedWordsSymbolTable, "struct", STRUCT);
    c_insertKey(reservedWordsSymbolTable, "long", LONG);
    c_insertKey(reservedWordsSymbolTable, "int", INT);
    c_insertKey(reservedWordsSymbolTable, "float", FLOAT);
    c_insertKey(reservedWordsSymbolTable, "bool", BOOL);
    c_insertKey(reservedWordsSymbolTable, "char", CHAR);
    c_insertKey(reservedWordsSymbolTable, "double", DOUBLE);
    c_insertKey(reservedWordsSymbolTable, "if", IF);
    c_insertKey(reservedWordsSymbolTable, "while", WHILE);
    c_insertKey(reservedWordsSymbolTable, "switch", SWITCH);
    c_insertKey(reservedWordsSymbolTable, "break", BREAK);
    c_insertKey(reservedWordsSymbolTable, "print", PRINT);
    c_insertKey(reservedWordsSymbolTable, "readln", READLN);
    c_insertKey(reservedWordsSymbolTable, "return", RETURN);
    c_insertKey(reservedWordsSymbolTable, "throw", THROW);
    c_insertKey(reservedWordsSymbolTable, "try", TRY);
    c_insertKey(reservedWordsSymbolTable, "catch", CATCH);
    c_insertKey(reservedWordsSymbolTable, "case", CASE);
    c_insertKey(reservedWordsSymbolTable, "for", FOR);
    c_insertKey(reservedWordsSymbolTable, "else", ELSE);
    c_insertKey(reservedWordsSymbolTable, "default", DEFAULT);

    //Identifiers
    identifiersSymbolTable = c_buildSymbolTable();

    //Literals
    literalsSymbolTable = c_buildSymbolTable();


}

//Updating stream with BUFFERSIZE characters
void loadStream() {

    analyser.streamLength= (int)fread(analyser.stremBuffer, 1, BUFFERSIZE, analyser.sourceFile);

    //Verify if that stream is the last;
    if(analyser.streamLength<BUFFERSIZE){
        analyser.stremBuffer[analyser.streamLength]='\0';
    }

    analyser.bufferIndex=0;

}

//Search and Return the next required token
Token* nextToken(){
    Token* token = (Token*)malloc(sizeof(Token));

    int lexemSize =BUFFERDELTA;
    char *lexem=(char*)malloc(lexemSize);
    int lexemIndex=0;
    short foundToken=FALSE;
    short state=0;

    char characterFound = getBufferCharacter(ADVANCE);

    //Lookup the next token from a deterministic automaton
    while(!foundToken){

        //Realloc lexem string if needed
        if(lexemIndex==lexemSize){
            lexemSize+=BUFFERDELTA;
            lexem=(char*) realloc(lexem, lexemSize);
        }

        analyser.lineCounter+=(characterFound=='\n');


        switch (state) {
            case 0:
                if(isNumber(characterFound)){
                    state=45;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(isLetter(characterFound)){
                    state=55;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(isWhiteSpace(characterFound)){
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound==':'){
                    state=1;
                    foundToken=TRUE;
                }else if(characterFound=='%'){
                    state=2;
                    foundToken=TRUE;
                }else if(characterFound=='+'){
                    state=3;
                    foundToken=TRUE;
                }else if(characterFound=='*'){
                    state=4;
                    foundToken=TRUE;
                }else if(characterFound=='\0'){
                    state=5;
                    foundToken=TRUE;
                }else if(characterFound=='{'){
                    state=6;
                    foundToken=TRUE;
                }else if(characterFound=='}'){
                    state=7;
                    foundToken=TRUE;
                }else if(characterFound=='['){
                    state=8;
                    foundToken=TRUE;
                }else if(characterFound==']'){
                    state=9;
                    foundToken=TRUE;
                }else if(characterFound=='('){
                    state=10;
                    foundToken=TRUE;
                }else if(characterFound==')'){
                    state=11;
                    foundToken=TRUE;
                }else if(characterFound=='!'){
                    state=12;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='>'){
                    state=15;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='<'){
                    state=18;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='='){
                    state=21;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='/'){
                    state=26;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='"'){
                    state=31;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='\''){
                    state=33;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='|'){
                    state=36;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='&'){
                    state=39;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='-'){
                    state=42;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound==';'){
                    state=57;
                    foundToken=TRUE;
                }else if(characterFound==','){
                    state=58;
                    foundToken=TRUE;
                }else{
                    state=49;
                    sendLexicError(UNEXPECTEDENTRY,analyser.lineCounter);
                    foundToken=TRUE;
                }
                break;
            case 12:
                if(characterFound=='='){
                    state=13;
                    foundToken=TRUE;
                }else{
                    state=14;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 15:
                if(characterFound=='='){
                    state=16;
                    foundToken=TRUE;
                }else{
                    state=17;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 18:
                if(characterFound=='='){
                    state=20;
                    foundToken=TRUE;
                }else{
                    state=19;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 21:
                if(characterFound=='='){
                    state=23;
                    foundToken=TRUE;
                }else{
                    state=22;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 36:
                if(characterFound=='|'){
                    state=37;
                    foundToken=TRUE;
                }else{
                    state=38;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 39:
                if(characterFound=='&'){
                    state=40;
                    foundToken=TRUE;
                }else{
                    state=41;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 42:
                if(characterFound=='>'){
                    state=43;
                    foundToken=TRUE;
                }else{
                    state=44;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 55:
                if(isLetter(characterFound) || isNumber(characterFound)){
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    state=56;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 26:
                if(characterFound=='*'){
                    state=29;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if (characterFound=='/'){
                    state=25;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    state=27;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 25:
                if (characterFound=='\n'){
                    state=0;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    characterFound= getBufferCharacter(ADVANCE);
                }
                break;
            case 29:
                if (characterFound=='*'){
                    state=28;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF,analyser.lineCounter);
                    foundToken=TRUE;
                }else{
                    characterFound= getBufferCharacter(ADVANCE);
                }
                break;
            case 28:
                if (characterFound=='\\'){
                    state=0;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    state=29;
                    characterFound= getBufferCharacter(ADVANCE);
                }
                break;
            case 31:
                if (characterFound=='\\'){
                    state=32;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='"'){
                    state=35;
                    lexem[lexemIndex++]=characterFound;
                    foundToken=TRUE;
                }else if(characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF, analyser.lineCounter);
                    foundToken=TRUE;
                }else{
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }
                break;
            case 32:
                if (characterFound=='b' || characterFound=='0'|| characterFound=='v'|| characterFound=='\\'|| characterFound=='"'
                    || characterFound=='n'|| characterFound=='r'|| characterFound=='f'|| characterFound=='t'|| characterFound=='a'){
                    state=31;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF, analyser.lineCounter);
                    foundToken=TRUE;
                }else{
                    state=49;
                    sendLexicError(UNEXPECTEDENTRY, analyser.lineCounter);
                    foundToken=TRUE;
                }
                break;
            case 33:
                if (characterFound=='\\'){
                    state=34;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF,analyser.lineCounter);
                    foundToken=TRUE;
                }else if(characterFound=='\''){
                    state=35;
                    lexem[lexemIndex++]=characterFound;
                    foundToken=TRUE;
                }else{
                    state=60;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }
                break;
            case 34:
                if (characterFound=='b' || characterFound=='0'|| characterFound=='v'|| characterFound=='\\'|| characterFound=='"'
                    || characterFound=='n'|| characterFound=='r'|| characterFound=='f'|| characterFound=='t'|| characterFound=='a'){
                    state=31;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF,analyser.lineCounter);
                    foundToken=TRUE;
                }else{
                    state=49;
                    sendLexicError(UNEXPECTEDENTRY,analyser.lineCounter);
                    foundToken=TRUE;
                }
                break;
            case 60:
                if (characterFound=='\''){
                    state=35;
                    foundToken=TRUE;
                }else if(characterFound=='\0'){
                    state=30;
                    sendLexicError(UNEXPECTEDEOF,analyser.lineCounter);
                    foundToken=TRUE;
                }else{
                    state=49;
                    sendLexicError(UNEXPECTEDENTRY,analyser.lineCounter);
                    foundToken=TRUE;
                }
                break;
            case 45:
                if (isNumber(characterFound)){
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='.'){
                    state=51;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='E'){
                    state=47;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    state=46;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 47:
                if(characterFound=='+'){
                    state=49;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    state=48;
                    sendLexicError(MALFORMEDNUMBER,analyser.lineCounter);
                    foundToken=TRUE;
                }
                break;
            case 49:
                if(isNumber(characterFound)){
                    state=50;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    state=48;
                    sendLexicError(MALFORMEDNUMBER,analyser.lineCounter);
                    foundToken=TRUE;
                }
                break;
            case 50:
                if(isNumber(characterFound)){
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    state=53;
                    foundToken=TRUE;

                }
                break;
            case 51:
                if(isNumber(characterFound)){
                    state=52;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    state=54;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;
            case 52:
                if(isNumber(characterFound)){
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else if(characterFound=='E'){
                    state=47;
                    lexem[lexemIndex++]=characterFound;
                    characterFound= getBufferCharacter(ADVANCE);
                }else{
                    state=53;
                    foundToken=TRUE;
                    analyser.bufferIndex--;
                }
                break;

        }
    }


    token->token=state;
    lexem[lexemIndex]='\0';
    token->lexemIndex = getNextFreeLexemIndex();
    token->lexemSize=lexemIndex;

    if(state!=30 && state!=49 && state!=48){
        pushLexem(lexem, token->lexemSize);
    }


    const char* tokenLexem = getLexem(token->lexemIndex, token->lexemIndex + token->lexemSize);
    if(state == ID){

        token->token = c_identifierOrReservedWord(reservedWordsSymbolTable, tokenLexem);

        //If it is a identifier
        if(token->token < TYPEDEF || token->token > FOR) c_insertKey(identifiersSymbolTable, tokenLexem, ID);

    }else if(state == LITERAL){

        c_insertKey(literalsSymbolTable, tokenLexem, LITERAL);

    }

    free(lexem);
    return token;

}

//Testing if file has a consistent name
void verifyFileConsistence(const char* fileName){ //TODO Verificar e permitir nome.

    int i=0;
    int state=0;
    char c= fileName[i];

    while(state!=5 && state!=6){
        switch (state) {
            case 0:
                if(c=='.'){
                    state=1;
                }else if(!isNumber(c) && !isLetter(c)){
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

//Verify and return if char c is a Letter
int isLetter(char c){
    if((c>64 && c<91) || (c>96 && c<123)){
        return TRUE;
    }
    return FALSE;
}

//Verify and return if char c is a Number
int isNumber(char c){
    if(c>47 && c<58){
        return TRUE;
    }
    return FALSE;
}


//Verify and return if char c is a white space
int isWhiteSpace(char c){
    return (c==' ' || c=='\t' || c=='\n' || c=='\r');
}

//Return the next character from buffer
char getBufferCharacter(int advance){

    //Testing if buffer reached limit
    if(analyser.bufferIndex==BUFFERSIZE){
        loadStream();
        analyser.bufferIndex=0;
    }

    //If advance, match the next character
    if(advance){
        return analyser.stremBuffer[analyser.bufferIndex++];
    }else{
        return analyser.stremBuffer[analyser.bufferIndex];
    }
}

//Returnin a pointer to Lexical Analyzer
LexicalAnalyser * getLexPointer(){
    return &analyser;
}

//Returnin a pointer to Reserverd Words Symbol Table
SymbolTable* getReservedWordsSymbolTablePointer(){
    return reservedWordsSymbolTable;
}
//Returnin a pointer to Literals Symbol Table
SymbolTable* getLiteralsSymbolTable(){
    return literalsSymbolTable;
}
//Returnin a pointer to Identifiers Symbol Table
SymbolTable* getIdentifiersSymbolTable(){
    return identifiersSymbolTable;
}

void clearLexicalAnalyzer(){
    c_deleteSymbolTable(literalsSymbolTable);
    c_deleteSymbolTable(reservedWordsSymbolTable);
    c_deleteSymbolTable(identifiersSymbolTable);
}