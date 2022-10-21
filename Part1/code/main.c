#include <stdio.h>
#include "LexicalAnalyzer.h"

//Print Functions
void printToken(Token* token);
void printSymbolTables();
const char* translateState(int state);

int main(int argc, char *argv[ ]) {

    if(argc>1){
        buildLexicalAnalyzer(argv[1]);

        //Running lexical analyser uppon the input
        Token* token=nextToken();
        while(token->token!=CMMEOF && token->token!=UNEXPECTEDEOF){
        printToken(token);
        free(token);
        token=nextToken();
        }
        printToken(token);
        printSymbolTables();
        free(token);

        deleteLexicalAnalyzer();

    }else{
        fprintf(stdout, "No file given !");

    }

    return 0;
}

//Function to print Token data
void printToken(Token* token){

    if(token->token >= 561 && token->token <= 581){

        fprintf(stdout,"%s\n", translateState(token->token));

    }else{


        char* tokemLexem= getLexem(token->lexemIndex, token->lexemIndex + token->lexemSize);
        if(token->token==ID || token->token==NUMINT || token->token==NUMFLOAT || token->token==LITERAL){
            fprintf(stdout,"%s.%s\n", translateState(token->token), tokemLexem);
        }else{
            fprintf(stdout,"%s\n", translateState(token->token));
        }

        free(tokemLexem);
    }
}

//Function to print Symbol Table data
void printSymbolTables(){

    fprintf(stdout,"\nSYMBOL TABLE: RESERVED WORDS\n");
    fprintf(stdout,"----------------------------------------\n");
    fprintf(stdout,"LEXEM                   NUMERIC TOKEN\n\n");

    SymbolTable* pointer=getReservedWordsSymbolTablePointer();

    for (int i = 0; i< TABSIZE; i++) {
        
        if(pointer->symbolTable[i] != NULL){

            int whiteSpacesNumber = 19 - strlen(pointer->symbolTable[i]->lexem) + 6;
            fprintf(stdout," %s", pointer->symbolTable[i]->lexem);
            for(int j = 0; j < whiteSpacesNumber; j++) fprintf(stdout," ");
            fprintf(stdout,"%zu", pointer->symbolTable[i]->token);

            TabEntry* currentEntry = pointer->symbolTable[i];
            while(currentEntry->prox != NULL){

                whiteSpacesNumber = 19 - strlen(currentEntry->prox->lexem) + 6;
                fprintf(stdout," %s", currentEntry->prox->lexem);
                for(int j = 0; j < whiteSpacesNumber; j++) fprintf(stdout," ");
                fprintf(stdout,"%zu", currentEntry->prox->token);
                currentEntry = currentEntry->prox;
            }
            fprintf(stdout,"\n");
        }
    }

    pointer=getIdentifiersSymbolTable();

    fprintf(stdout,"\nSYMBOL TABLE: IDENTIFIER\n");
    fprintf(stdout,"----------------------------------------\n");
    fprintf(stdout,"LEXEM                   \n\n");

    for (int i = 0; i< TABSIZE; i++) {
        
        if(pointer->symbolTable[i] != NULL){

            fprintf(stdout," %s", pointer->symbolTable[i]->lexem);
            
            TabEntry* currentEntry = pointer->symbolTable[i];
            while(currentEntry->prox != NULL){

                fprintf(stdout," %s", currentEntry->prox->lexem);
                currentEntry = currentEntry->prox;
            }
            fprintf(stdout,"\n");
        }
    }
    
    pointer=getLiteralsSymbolTable();

    fprintf(stdout,"\nSYMBOL TABLE: LITERALS\n");
    fprintf(stdout,"----------------------------------------\n");
    fprintf(stdout,"LEXEM                   \n\n");

    for (int i = 0; i< TABSIZE; i++) {
        
        if(pointer->symbolTable[i] != NULL){

            fprintf(stdout," %s", pointer->symbolTable[i]->lexem);

            TabEntry* currentEntry = pointer->symbolTable[i];
            while(currentEntry->prox != NULL){

                fprintf(stdout," %s", currentEntry->prox->lexem);

                currentEntry = currentEntry->prox;
            }
            fprintf(stdout,"\n");
        }
    }

    

}

//Translate a state or Hash number to referred string
const char* translateState(int state){
    switch (state) {
        case 1:
            return "COLON";
        case 2:
            return "MOD";
        case 3:
            return "PLUS";
        case 4:
            return "MULT";
        case 5:
            return "CMMEOF";
        case 14:
            return "NOT";
        case 13:
            return "NEQ";
        case 17:
            return "GREAT";
        case 16:
            return "GEQ";
        case 20:
            return "LEQ";
        case 19:
            return "LESS";
        case 23:
            return "EQ";
        case 22:
            return "ASSIGN";
        case 27:
            return "DIV";
        case 35:
            return "LITERAL";
        case 11:
            return "RIGHTPARENTHESES";
        case 10:
            return "LEFTPARENTHESES";
        case 9:
            return "RIGHTBRACKET";
        case 8:
            return "LEFTBRACKET";
        case 7:
            return "RIGHTBRACE";
        case 6:
            return "LEFTBRACE";
        case 56:
            return "ID";
        case 54:
            return "POINT";
        case 53:
            return "NUMFLOAT";
        case 46:
            return "NUMINT";
        case 43:
            return "POINTER";
        case 44:
            return "MINUS";
        case 40:
            return "AND";
        case 41:
            return "AMBERSAND";
        case 37:
            return "OR";
        case 38:
            return "PIPE";
        case 57:
            return "SEMICOLON";
        case 58:
            return "COMMA";
        case 561:
            return "TYPEDEF";
        case 562:
            return "STRUCT";
        case 563:
            return "LONG";
        case 564:
            return "INT";
        case 565:
            return "FLOAT";
        case 566:
            return "BOOL";
        case 567:
            return "CHAR";
        case 568:
            return "DOUBLE";
        case 569:
            return "IF";
        case 570:
            return "WHILE";
        case 571:
            return "SWITCH";
        case 572:
            return "BREAK";
        case 573:
            return "PRINT";
        case 574:
            return "READLN";
        case 575:
            return "RETURN";
        case 576:
            return "THROW";
        case 577:
            return "TRY";
        case 578:
            return "CATCH";
        case 579:
            return "CASE";
        case 580:
            return "FOR";
        case 30:
            return "UNEXPECTEDEOF";
        case 48:
            return "MALFORMEDNUMBER";
        case 49:
            return "UNEXPECTEDENTRY";

    }
    return NULL;
}