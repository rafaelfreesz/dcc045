#include <stdio.h>
#include "LexicalAnalyzer.h"


int main(int argc, char *argv[ ]) {



    buildLexicalAnalyzer("text.cmm");
    buildLexemBuffer();



    Token* token=nextToken();

    while(token->token!=EOF){
        printLexemBuffer();
        printToken(token);
        free(token);
    }


    return 0;
}
