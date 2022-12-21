//
// Created by Rafael on 12/19/2022.
//

#ifndef CMMCOMPILER_PARSER_H
#define CMMCOMPILER_PARSER_H
#include "Utils.h"
#define FIRSTTOKEN  -1
#ifdef __cplusplus

class Parser {
public:

    static void parse(); //Depois vai retornar a raiz da arvore
    void match(int token);

    //Nonterminal functions
    void program(int token);
    void declprefix(int token);
    void declsulfix(int token);
    void typedecl(int token);
    void type(int token);
    void pointer(int token);
    void vardeclsulfix(int token);

private:
    Parser();
    ~Parser();
    Token* token;

};
#else
typedef struct Parse Parse;
#endif

#ifdef __cplusplus
extern "C" {
#include "LexicalAnalyzer.h"
#endif
    void c_parse();

#ifdef __cplusplus
}
#endif

#endif //CMMCOMPILER_PARSER_H
