#ifndef CMMCOMPILER_PARSER_H
#define CMMCOMPILER_PARSER_H

// #include "Utils.h"
#include "LexicalAnalyzer.h"
#include "ast.h"


#define FIRSTTOKEN  -1

class Parser {
    public:

        Program* rootNodeAST;
        
        static void parse(); //Depois vai retornar a raiz da arvore
        void match(int token);

        //Nonterminal functions
        void program() ;
        void program2();
        void declprefix();
        void declsulfix() ;
        void varDeclSulfix();
        void varDecl();
        void varDecl2();

        void functionDecl();
        void functionBody();
        void functionBody2();
        void functionBody3();

        void binOp();

        void idList();
        void idList2();
        void typedecl() ;

        void array();

        void formalList();
        void formalRest();
        void stmt();
        void stmtCompl();
        void stmtList();
        void stmtList2();
        void stmtPrim();
        void stmtPrim2();
        void stmtPrim3();
        void stmt1();
        void stmt2();
        void stmt3();
        void stmt4();
        void stmt5();
        void stmt6();
        void stmt7();
        void stmt8();
        void stmt9();
        void caseblock();
        void caseblock2();
        void exprList();
        void exprListTail();
        void exprListTail2();
        void expr();
        void expr_l();
        void expr1();
        void expr1_l();
        void expr2();
        void expr2_l();
        void expr3();
        void expr3_l();
        void expr4();
        void expr4_l();
        void expr5();
        void expr5_l();
        void expr6() ;
        void expr6_l() ;
        void expr7() ;
        void expr8() ;
        void primary() ;
        void primary2() ;
        void primary3() ;
        void unaryOp() ;
        void pointer();
        Type* type() ;
        void typeCompl() ;


    private:
        Parser();
        ~Parser();
        Token* token;

};

#endif //CMMCOMPILER_PARSER_H
