//
// Created by Rafael on 11/5/2022.
//

#include "SymbolTable.h"
#include "string.h"

//Function to build lexem buffer
void buildLexemBuffer(){
    lexemBuffer.lexemBuffer=(char*)malloc(BUFFERDELTA);
    lexemBuffer.bufferLength=BUFFERDELTA;
    lexemBuffer.nextFreeIndex=0;
}

//Return a lexem from Lexem Buffer by a gived begin and end index
char* getLexem(int lexemIndex, int lexemEnd){

    //Verifying index bound
    if(lexemIndex!=DEFAULTLEXEM){

        //Copying lexem from buffer to return lexem
        char* lexem= (char*)malloc(lexemEnd + 1);
        int j=0;
        for(int i=lexemIndex; i < lexemEnd; i++,j++){
            lexem[j]=lexemBuffer.lexemBuffer[i];
        }
        lexem[j]='\0';

        return lexem;

    }

    return NULL;
}
void pushLexem(char *lexem, int lexemSize) {


    for(int i=0;i<lexemSize;i++){
        //Verify if lexem buffer reached the limit
        if(lexemBuffer.nextFreeIndex == lexemBuffer.bufferLength){
            reallocLexemBuffer();
        }

        lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex++]=lexem[i];
    }

    lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex]='_';

}

void reallocLexemBuffer(){
    lexemBuffer.bufferLength += BUFFERDELTA;
    lexemBuffer.lexemBuffer = (char*)realloc(lexemBuffer.lexemBuffer, lexemBuffer.bufferLength + 1);
}

int getNextFreeLexemIndex(){
    return lexemBuffer.nextFreeIndex;
}
int getBufferLength(){
    return lexemBuffer.bufferLength;
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


//SymbolTable methods
SymbolTable::SymbolTable(){

    for (int i = 0; i< TABSIZE; i++) {
        symbolTable[i] = NULL;
    }
}

void SymbolTable::printHashTable(){

    for (int i = 0; i< TABSIZE; i++) {

        if(symbolTable[i] == NULL){
            printf("----\n");
        }else{
            printf("[%s | %d]-> ", symbolTable[i]->lexem, symbolTable[i]->token);

            TabEntry* currentEntry = this->symbolTable[i];
            while(currentEntry->prox != NULL){
                printf("[%s | %d]-> ", currentEntry->prox->lexem, currentEntry->prox->token);
                currentEntry = currentEntry->prox;
            }
            printf("\n");
        }
    }

}

int SymbolTable::hashFunction(const char* lexem){

    short n = strlen(lexem);
    const int p = 31;
    int hash = 0;
    long p_pow = 1;
    for(int i = 0; i < n; i++) {
        hash = (hash + abs((lexem[i] - 'a' + 1) * p_pow)) % TABSIZE;
        p_pow = (p_pow * p) % TABSIZE;
    }
    return hash;


    // return lexem % TABSIZE;

};

void SymbolTable::insertKey(const char* lexem, int token) {

    int hashValue = hashFunction(lexem);

    //Collision
    if(symbolTable[hashValue] != NULL){

        //Insert at beginning if the lexem is different
        if(strcmp(symbolTable[hashValue]->lexem, lexem) != 0){

            TabEntry* newEntry = new TabEntry(lexem, token);
            newEntry->prox = symbolTable[hashValue]->prox;
            symbolTable[hashValue]->prox = newEntry;
        }

    }else{
        symbolTable[hashValue] = new TabEntry(lexem, token);
    }

}

TabEntry* SymbolTable::searchKey(const char* lexem){

    int hashValue = hashFunction(lexem);

    //Found key
    if(symbolTable[hashValue] != NULL && strcmp(symbolTable[hashValue]->lexem, lexem) == 0 ){

        // printf("Found key at position %d !\n", hashValue);
        return symbolTable[hashValue];

    }else{

        if(symbolTable[hashValue] == NULL) {
            // printf("Key not found !\n");
            return NULL;
        }

        TabEntry* currentEntry = symbolTable[hashValue]->prox;
        int brother = 0;
        while(currentEntry != NULL){

            if(strcmp(currentEntry->lexem, lexem) == 0){

                // printf("Found key at position %d at %d brother !\n", hashValue, brother);
                return currentEntry;

            }
            brother++;
            currentEntry = currentEntry->prox;
        }

        // printf("Key not found !\n");
        return NULL;

    }


};

int SymbolTable::identifierOrReservedWord(const char* lexem){

    TabEntry* entry = searchKey(lexem);
    if(entry == NULL){
        return ID;
    }else{
        return entry->token;
    }
}

SymbolTable::~SymbolTable(){

    for (int i = 0; i< TABSIZE; i++) {

        if(symbolTable[i] != NULL){

            TabEntry* currentEntry = symbolTable[i];
            while(currentEntry->prox != NULL){

                TabEntry* entryToBeDeleted = currentEntry;
                currentEntry = currentEntry->prox;
                delete entryToBeDeleted;
            }

        }


    }
}

//TabEntry methods
TabEntry::TabEntry(const char* lexem, int token){

    this->lexem = lexem;
    this->token = token;
    this->prox = NULL;

}

//---Wrapper Functions---//

void c_deleteSymbolTable(SymbolTable* symbolTable){
    delete symbolTable;
}

SymbolTable* c_buildSymbolTable() {
    return new SymbolTable();
}

void c_insertKey(SymbolTable *symbolTable, const char *lexem, int token) {
    symbolTable->insertKey(lexem,token);
}
int c_identifierOrReservedWord(SymbolTable *symbolTable, const char *lexem) {
    return symbolTable->identifierOrReservedWord(lexem);
}
TabEntry* c_getTabEntry(SymbolTable* symbolTable, int index){
    return symbolTable->symbolTable[index];
}
const char* c_getTabEntryLexem(TabEntry* tabEntry){
    return tabEntry->lexem;
}
int c_getTabEntryToken(TabEntry* tabEntry){
    return tabEntry->token;
}

TabEntry* c_getTabEntryProx(TabEntry* tabEntry){
    return tabEntry->prox;
}