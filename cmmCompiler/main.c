#include <stdio.h>
#include "LexicalAnalyzer.h"


int main(int argc, char *argv[ ]) {

    buildLexicalAnalyzer("text2.cmm");
    LexicalAnalyser * pointer =getALexPointer(); //TODO apagar
    LexemBuffer  * lbPointer= getLexemBuffer();
    buildLexemBuffer();

    Token* token=nextToken();
    char* lexem= getLexem(token->lexemIndex,token->lexemIndex+token->lexemSize);
    while(token->token!=CMMEOF){

       // printLexicalAnalyser();
       // printLexemBuffer();
        printToken(token);
        //free(token);
        token=nextToken();
       // lexem= getLexem(token->lexemIndex,token->lexemIndex+token->lexemSize);
    }

    printToken(token);

    return 0;
}
