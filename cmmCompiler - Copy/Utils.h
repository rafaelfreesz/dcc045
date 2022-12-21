//
// Created by Rafael on 12/19/2022.
//

#ifndef CMMCOMPILER_UTILS_H
#define CMMCOMPILER_UTILS_H
//#include "LexicalAnalyzer.h"

#ifdef __cplusplus
extern "C" {
#include "SymbolTable.h"
#include "LexicalAnalyzer.h"
}


class Utils {
public:
    static void printToken(Token* token);
    static void printLexicalAnalyser();
    static void printSymbolTables();
    static const char* translateState(int state);
};

#endif
#endif //CMMCOMPILER_UTILS_H
