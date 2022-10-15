#include <stdio.h>
#include "LexicalAnalyzer.h"


int main(int argc, char *argv[ ]) {



    buildLexicalAnalyzer("text.cmm");
    buildLexemBuffer();

    Token* token=nextToken();

    while(token->token!=CMMEOF){
        printLexemBuffer();
        printToken(token);
        //free(token);
        token=nextToken();
    }


    return 0;
}
