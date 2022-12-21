//
// Created by Rafael on 12/19/2022.
//

#include "Utils.h"


void Utils::printToken(Token *token) {
    if(token->token >= 561 && token->token <= 581){

        printf("%s\n", translateState(token->token));

    }else{


        char* tokemLexem= getLexem(token->lexemIndex, token->lexemIndex + token->lexemSize);
        if(token->token==ID || token->token==NUMINT || token->token==NUMFLOAT || token->token==LITERAL){
            printf("%s.%s\n", translateState(token->token), tokemLexem);
        }else{
            printf("%s\n", translateState(token->token));
        }

        free(tokemLexem);
    }
}

void Utils::printLexicalAnalyser() {
    LexicalAnalyser* lex=getLexPointer();
    printf("--------------Lexical Analyzer Data-----------\n");
    printf("StreamLength: %d\n",lex->streamLength);
    printf("BufferIndex: %d\n",lex->bufferIndex);
    printf("StreamBuffer:\n");
    for(int i=0;i<lex->streamLength;i++){
        printf("%c",lex->stremBuffer[i]);
    }
    printf("\n-------------------------\n");
}

//Function to print Symbol Table data
void Utils::printSymbolTables() {
    printf("\nSYMBOL TABLE: RESERVED WORDS\n");
    printf("----------------------------------------\n");
    printf("LEXEM                   NUMERIC TOKEN\n\n");

    SymbolTable* pointer=getReservedWordsSymbolTablePointer();
    TabEntry * tabEntry;
    const char* lexem;

    for (int i = 0; i< TABSIZE; i++) {
        tabEntry = c_getTabEntry(pointer,i);

        if(tabEntry != NULL){

            lexem= c_getTabEntryLexem(tabEntry);

            int whiteSpacesNumber = 19 - strlen(lexem) + 6;
            printf(" %s", lexem);
            for(int j = 0; j < whiteSpacesNumber; j++) printf(" ");
            printf("%d", c_getTabEntryToken(tabEntry));

            TabEntry* currentEntry = c_getTabEntry(pointer,i);
            while(c_getTabEntryProx(currentEntry) != NULL){
                lexem= c_getTabEntryLexem(currentEntry);
                whiteSpacesNumber = 19 - strlen(lexem) + 6;
                printf(" %s", c_getTabEntryLexem(c_getTabEntryProx(currentEntry)));
                for(int j = 0; j < whiteSpacesNumber; j++) printf(" ");
                printf("%d", c_getTabEntryToken(c_getTabEntryProx(currentEntry)));
                currentEntry = c_getTabEntryProx(currentEntry);
            }
            printf("\n");
        }
    }

    pointer=getIdentifiersSymbolTable();

    printf("\nSYMBOL TABLE: IDENTIFIER\n");
    printf("----------------------------------------\n");
    printf("LEXEM                   \n\n");

    for (int i = 0; i< TABSIZE; i++) {

        if(c_getTabEntry(pointer,i)  != NULL){

            int whiteSpacesNumber = 19 - strlen(c_getTabEntryLexem(c_getTabEntry(pointer,i))) + 6;
            printf(" %s", c_getTabEntryLexem(c_getTabEntry(pointer,i)));

            TabEntry* currentEntry = c_getTabEntry(pointer,i);
            while(c_getTabEntryProx(currentEntry)){

                whiteSpacesNumber = 19 - strlen(c_getTabEntryLexem(c_getTabEntryProx(currentEntry))) + 6;
                printf(" %s", c_getTabEntryLexem(c_getTabEntryProx(currentEntry)));
                currentEntry = c_getTabEntryProx(currentEntry);
            }
            printf("\n");
        }
    }

    pointer=getLiteralsSymbolTable();

    printf("\nSYMBOL TABLE: LITERALS\n");
    printf("----------------------------------------\n");
    printf("LEXEM                   \n\n");

    for (int i = 0; i< TABSIZE; i++) {

        if(c_getTabEntry(pointer,i) != NULL){

            int whiteSpacesNumber = 19 - strlen(c_getTabEntryLexem(c_getTabEntry(pointer,i))) + 6;
            printf(" %s", c_getTabEntryLexem(c_getTabEntry(pointer,i)));

            TabEntry* currentEntry = c_getTabEntry(pointer,i);
            while(c_getTabEntryProx(currentEntry) != NULL){

                whiteSpacesNumber = 19 - strlen(c_getTabEntryLexem(c_getTabEntryProx(currentEntry))) + 6;
                printf(" %s", c_getTabEntryLexem(c_getTabEntryProx(currentEntry)));

                currentEntry = c_getTabEntryProx(currentEntry);
            }
            printf("\n");
        }
    }

}

//Translate a state or Hash number to referred string
const char *Utils::translateState(int state) {
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
            return "pointer";
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
