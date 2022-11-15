#include "ErrorManager.h"

//Announce a code-based system error
void sendSystemError(size_t code){

    printf("SYSTEM ERROR %zu: ",code);

    switch (code) {
        case FILENOTFOUND:
            fprintf(stderr, "File not Found\n");
            break;
        case FILENOTSUPPORTED:
            fprintf(stderr, "File not supported\n");
            break;
        case INDEXOUTOFBOUNDS:
            fprintf(stderr, "Index out of bounds\n");
            break;


    }

    exit(code);

}

//Announce a code-based lexic error
void sendLexicError(size_t code, size_t line){
    printf("LEXIC ERROR %zu in line %zu: ",code,line);

    switch (code) {
        case UNEXPECTEDENTRY:
            fprintf(stderr, "Unexpected Entry\n");
            break;
        case UNEXPECTEDEOF:
            fprintf(stderr, "Unexpected end of file\n");
            break;
        case MALFORMEDNUMBER:
            fprintf(stderr, "Malformed number\n");
            break;


    }
}