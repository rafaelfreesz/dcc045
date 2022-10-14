#include <stdio.h>
#include "LexicalAnalyzer.h"


int main(int argc, char *argv[ ]) {

    int isThereArgumentForFile = 1;
    (argc > 1) ? buildLexicalAnalyzer(argv[1], isThereArgumentForFile) : buildLexicalAnalyzer(argv[1], !isThereArgumentForFile);

    while(1){

        int retorno = nextToken();
        printf("Token: %d\n", retorno);
        if(retorno == -1) break;
    }
    // int token = nextToken();
    // printf("%d", token);

    return 0;
}