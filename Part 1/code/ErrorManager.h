#ifndef CMMCOMPILER_ERRORMANAGER_H
#define CMMCOMPILER_ERRORMANAGER_H
#include "stdio.h"
#include "stdlib.h"
#define FILENOTFOUND 1
#define FILENOTSUPPORTED 2
#define INDEXOUTOFBOUNDS 3
#define UNEXPECTEDENTRY 49
#define UNEXPECTEDEOF 30
#define MALFORMEDNUMBER 48

void sendSystemError(size_t code);
void sendLexicError(size_t code, size_t line);


#endif //CMMCOMPILER_ERRORMANAGER_H
