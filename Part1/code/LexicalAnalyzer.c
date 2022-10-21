#include "LexicalAnalyzer.h"
#include "SymbolTable.h"

//Declare variables of the analyser and symbolTables
static LexicalAnalyser analyser;
static SymbolTable* reservedWordsSymbolTable;
static SymbolTable* literalsSymbolTable;
static SymbolTable* identifiersSymbolTable;


//Function to build Lexical Analyzer
void buildLexicalAnalyzer(const char* fileName){

    verifyFileConsistence(fileName);

    if((analyser.sourceFile= fopen(fileName,"r"))==NULL){
        sendSystemError(FILENOTFOUND);
    }

    buildLexemBuffer();
    buildSymbolTables();
    loadStream();
    analyser.lineCounter=1;

}

//Destructor of Lexical analyser and the tables
void deleteLexicalAnalyzer(){

    delete reservedWordsSymbolTable;
    delete literalsSymbolTable;
    delete identifiersSymbolTable;
    deleteLexemBuffer();
}

//Function to build Symbol Tables
void buildSymbolTables(){

    //Reserved words symbol table
    reservedWordsSymbolTable = new SymbolTable();
    reservedWordsSymbolTable->insertKey("typedef", TYPEDEF);
    reservedWordsSymbolTable->insertKey("struct", STRUCT);
    reservedWordsSymbolTable->insertKey("long", LONG);
    reservedWordsSymbolTable->insertKey("int", INT);
    reservedWordsSymbolTable->insertKey("float", FLOAT);
    reservedWordsSymbolTable->insertKey("bool", BOOL);
    reservedWordsSymbolTable->insertKey("char", CHAR);
    reservedWordsSymbolTable->insertKey("double", DOUBLE);
    reservedWordsSymbolTable->insertKey("if", IF);
    reservedWordsSymbolTable->insertKey("while", WHILE);
    reservedWordsSymbolTable->insertKey("switch", SWITCH);
    reservedWordsSymbolTable->insertKey("break", BREAK);
    reservedWordsSymbolTable->insertKey("print", PRINT);
    reservedWordsSymbolTable->insertKey("readln", READLN);
    reservedWordsSymbolTable->insertKey("return", RETURN);
    reservedWordsSymbolTable->insertKey("throw", THROW);
    reservedWordsSymbolTable->insertKey("try", TRY);
    reservedWordsSymbolTable->insertKey("catch", CATCH);
    reservedWordsSymbolTable->insertKey("case", CASE);
    reservedWordsSymbolTable->insertKey("for", FOR);

    //Identifiers symbol table
    identifiersSymbolTable = new SymbolTable();

    //Literals symbol table
    literalsSymbolTable = new SymbolTable();


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
    
    size_t lexemSize =BUFFERDELTA;
    char *lexem=(char*)malloc(lexemSize);
    size_t lexemIndex=0;
    size_t foundToken=FALSE;
    size_t state=0;

    char characterFound = getBufferCharacter(ADVANCE);

    //Lookup the next token from a deterministic automaton
    while(!foundToken){
        
        //Realloc lexem string if needed
        if(lexemIndex==lexemSize){
            lexemSize+=BUFFERDELTA;
            lexem=(char*) realloc(lexem, lexemSize);
        }

        //Count up lines
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
                }else if(characterFound=='.'){
                    state=51;
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
                if(characterFound=='+' || characterFound=='-'){
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

    if(state!=UNEXPECTEDEOF && state!=UNEXPECTEDENTRY && state!=MALFORMEDNUMBER){
        pushLexem(lexem, token->lexemSize);
    }
    

    const char* tokenLexem = getLexem(token->lexemIndex, token->lexemIndex + token->lexemSize);
    if(state == ID){

        token->token = reservedWordsSymbolTable->identifierOrReservedWord(tokenLexem);

        //If it is a identifier
        if(token->token < TYPEDEF || token->token > FOR) identifiersSymbolTable->insertKey(tokenLexem, ID);  

    }else if(state == LITERAL){

        literalsSymbolTable->insertKey(tokenLexem, LITERAL);
    
    }

    free(lexem);
    return token;

}

//Testing if file has a consistent name
void verifyFileConsistence(const char* fileName){

    const char *lastDotOccurrence  = strrchr(fileName, '.');

    if(lastDotOccurrence) { //If file has extension

        //Other files are not supported
        if((strcmp(lastDotOccurrence, ".cmm") != 0)) sendSystemError(FILENOTSUPPORTED);

    }
    
    //Check if the file was open successfully
    if((analyser.sourceFile= fopen(fileName,"r"))==NULL){
        sendSystemError(FILENOTFOUND);
    }

}

//Verify and return if char c is a Letter
size_t isLetter(char c){
    if((c>64 && c<91) || (c>96 && c<123)){
        return TRUE;
    }
    return FALSE;
}

//Verify and return if char c is a Number
size_t isNumber(char c){
    if(c>47 && c<58){
        return TRUE;
    }
    return FALSE;
}


//Verify and return if char c is a white space
size_t isWhiteSpace(char c){
    return (c==' ' || c=='\t' || c=='\n' || c=='\r');
}

//Return the next character from buffer
char getBufferCharacter(size_t advance){

    //Testing if buffer reached limit
    if(analyser.bufferIndex==BUFFERSIZE){
        loadStream();
        analyser.bufferIndex=0;
    }

    //If advance, consume the next character
    if(advance){
        return analyser.stremBuffer[analyser.bufferIndex++];
    }else{
        return analyser.stremBuffer[analyser.bufferIndex];
    }
}

//Returning a pointer to Reserverd Words Symbol Table
SymbolTable* getReservedWordsSymbolTablePointer(){
    return reservedWordsSymbolTable;
}
//Returning a pointer to Literals Symbol Table
SymbolTable* getLiteralsSymbolTable(){
    return literalsSymbolTable;
}
//Returning a pointer to Identifiers Symbol Table
SymbolTable* getIdentifiersSymbolTable(){
    return identifiersSymbolTable;
}



