#include "SymbolTable.h"
#include "string.h"

//Declare lexemBuffer
static LexemBuffer lexemBuffer;

//Function to build lexem buffer
void buildLexemBuffer(){
    lexemBuffer.lexemBuffer=(char*)malloc(BUFFERDELTA);
    lexemBuffer.bufferLength=BUFFERDELTA;
    lexemBuffer.nextFreeIndex=0;
}

//Return a lexem from Lexem Buffer by a gived begin and end index
char* getLexem(size_t lexemIndex, size_t lexemEnd){

    //Copying lexem from buffer to return lexem
    char* lexem= (char*)malloc(lexemEnd + 1);
    size_t j=0;
    for(size_t i=lexemIndex; i < lexemEnd; i++,j++){
        lexem[j]=lexemBuffer.lexemBuffer[i];
    }
    lexem[j]='\0';

    return lexem;

}

//Function that pushes lexem into lexemBuffer
void pushLexem(char *lexem, size_t lexemSize) {


    for(size_t i=0;i<lexemSize;i++){

        //Verify if lexem buffer reached the limit
        if(lexemBuffer.nextFreeIndex == lexemBuffer.bufferLength){
            reallocLexemBuffer();
        }

        lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex++]=lexem[i];
    }

    lexemBuffer.lexemBuffer[lexemBuffer.nextFreeIndex]='_';

}

//Function that reallocs the size of lexemBuffer in case of reaching the limit of size
void reallocLexemBuffer(){
    lexemBuffer.bufferLength += BUFFERDELTA;
    lexemBuffer.lexemBuffer = (char*)realloc(lexemBuffer.lexemBuffer, lexemBuffer.bufferLength + 1);
}

//Get next free index in the LexemBuffer
size_t getNextFreeLexemIndex(){
    return lexemBuffer.nextFreeIndex;
}

//Get the size of the LexemBuffer
size_t getBufferLength(){
    return lexemBuffer.bufferLength;
}

//Desallocate memory of the lexemBuffer
void deleteLexemBuffer(){
    free(lexemBuffer.lexemBuffer);
}

//SymbolTable methods

//Constructor
SymbolTable::SymbolTable(){
    
    for (size_t i = 0; i< TABSIZE; i++) {
        symbolTable[i] = NULL;
    }
}


//Implement the Polynomial rolling hash function
size_t SymbolTable::hashFunction(const char* lexem){    
    
    size_t n = strlen(lexem);
    const size_t p = 31;
    size_t hash = 0;
    long p_pow = 1;
    for(size_t i = 0; i < n; i++) {
        hash = (hash + abs((lexem[i] - 'a' + 1) * p_pow)) % TABSIZE;
        p_pow = (p_pow * p) % TABSIZE;
    }
    return hash;

    
    // return lexem % TABSIZE;

};

//Insert key into the hash structure of symbol table
void SymbolTable::insertKey(const char* lexem, size_t token) {

    size_t hashValue = hashFunction(lexem);

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


//Search for the key in the hash structure of symbol table
TabEntry* SymbolTable::searchKey(const char* lexem){

    size_t hashValue = hashFunction(lexem);

    //Found key
    if(symbolTable[hashValue] != NULL && strcmp(symbolTable[hashValue]->lexem, lexem) == 0 ){

        // printf("Found key at position %zu !\n", hashValue);
        return symbolTable[hashValue];

    }else{
        
        if(symbolTable[hashValue] == NULL) {
            // printf("Key not found !\n");
            return NULL;
        }
        
        TabEntry* currentEntry = symbolTable[hashValue]->prox;
        size_t brother = 0;
        while(currentEntry != NULL){
            
            if(strcmp(currentEntry->lexem, lexem) == 0){

                // printf("Found key at position %zu at %zu brother !\n", hashValue, brother);
                return currentEntry;

            }
            brother++;
            currentEntry = currentEntry->prox;
        }

        // printf("Key not found !\n");
        return NULL;

    }


};

//Function the verifies in the reserved word symbol table if the word is reserved
size_t SymbolTable::identifierOrReservedWord(const char* lexem){

    TabEntry* entry = searchKey(lexem);
    if(entry == NULL){

        return ID;

    }else{
        return entry->token;
    }
}

//Destructot of symbol table
SymbolTable::~SymbolTable(){
    
    for (size_t i = 0; i< TABSIZE; i++) {

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

//Constructor
TabEntry::TabEntry(const char* lexem, size_t token){

    this->lexem = lexem;
    this->token = token;
    this->prox = NULL;

}








