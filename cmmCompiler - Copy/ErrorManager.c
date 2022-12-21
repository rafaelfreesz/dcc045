//
// Created by Rafael on 11/5/2022.
//

#include "ErrorManager.h"

//Announce a code-based system error
void sendSystemError(int code){

    printf("SYSTEM ERROR %d: ",code);

    switch (code) {
        case FILENOTFOUND:
            printf("File not Found\n");
            break;
        case FILENOTSUPPORTED:
            printf("File not supported\n");
            break;
        case INDEXOUTOFBOUNDS:
            printf("Index out of bounds\n");
            break;


    }

    exit(code);

}

//Announce a code-based lexic error
void sendLexicError(int code, int line){
    printf("LEXIC ERROR %d in line %d: ",code,line);

    switch (code) {
        case UNEXPECTEDENTRY:
            printf("Unexpected Entry\n");
            break;
        case UNEXPECTEDEOF:
            printf("Unexpected end of file\n");
            break;
        case MALFORMEDNUMBER:
            printf("Malformed number\n");
            break;


    }
}
