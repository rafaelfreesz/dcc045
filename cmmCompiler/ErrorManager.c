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

    }

    exit(code);

}