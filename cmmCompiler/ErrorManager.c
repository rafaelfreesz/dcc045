//
// Created by Rafael on 10/11/2022.
//

#include "ErrorManager.h"

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

void sendLexicError(int code){
    printf("LEXIC ERROR %d: ",code);

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

    exit(code);
}