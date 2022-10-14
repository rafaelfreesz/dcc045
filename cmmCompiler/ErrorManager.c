//
// Created by Rafael on 10/11/2022.
//

#include "ErrorManager.h"

void sendSystemError(int code){

    printf("ERROR %d: ",code);

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