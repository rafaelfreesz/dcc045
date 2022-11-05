//
// Created by Rafael on 11/5/2022.
//

#ifndef CMMCOMPILER_ERRORMANAGER_H
#define CMMCOMPILER_ERRORMANAGER_H
#include <stdio.h>
#include <stdlib.h>
#define FILENOTFOUND 1
#define FILENOTSUPPORTED 2
#define INDEXOUTOFBOUNDS 3
#define UNEXPECTEDENTRY 4
#define UNEXPECTEDEOF 5
#define MALFORMEDNUMBER 6

void sendSystemError(int code);
void sendLexicError(int code, int line);
#endif //CMMCOMPILER_ERRORMANAGER_H
