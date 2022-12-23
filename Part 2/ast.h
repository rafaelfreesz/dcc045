#ifndef CMMCOMPILER_AST_H
#define CMMCOMPILER_AST_H

#include "LexicalAnalyzer.h"

class Program;
class VarList;
class NameDecl;
class FunctionList;
class TypeList;
class Type;
class StatementList;
class Statement;
class If;
class While;
class Switch;
class Break;
class PrintLn;
class Read;
class Return;
class CaseBlock;
class Throw;
class ExpList;
class Try;
class Exp;
class Assign;
class Or;
class And;
class Eq;
class Neq;
class Less;
class Leq;
class Great;
class Geq;
class Plus;
class Minus;
class Pipe;
class Mult;
class Div;
class Mod;
class Ampersand;
class UnaryMinus;
class Not;
class UnaryPlus;
class Pointer;
class True;
class False;
class Call;
class Id;
class Num;
class Literal;
class Char;
class Bool;


class Statement {
	
};

class Exp {
	
};

class Program {
	
    public:
        FunctionList* functionList;
        TypeList* typeList;
        VarList* varList;

        Program(){

            printf("CREATED PROGRAM\n");
            this->functionList = NULL;
            this->typeList = NULL;
            this->varList = NULL;
        }

};

class VarList {
	
    public:
        NameDecl* nameDecl;
        VarList* next;

        VarList(NameDecl* nameDecl, VarList* next){
            printf("CREATED VARLIST\n");
            this->nameDecl = nameDecl;
            this->next = next;
        }

};
class NameDecl {
	
    public:
        Type* type;
        Id* id;

        NameDecl(Type* type, Id* id){

            printf("CREATED NAMEDECL\n");
            this->type = type;
            this-> id = id;
        }
};

class FunctionList {
	
    Type* type;
    Id* id;
    VarList* varList;
    VarList* paramList;
    StatementList* stmtList;
    FunctionList* next;

};

class TypeList {
	
};

class Type {
	
    public:
        Id* id;
        size_t size;

        Type(Id* id, size_t size){
            
            printf("CREATED TYPE\n");
            this->id = id;
            this->size = size;
        }

};

class ExpList {
	
    Exp* exp;
    ExpList* next;
    
};
class CaseBlock {
	
};

//Statements

class StatementList: public Statement{
	
    Statement* stmt;
    StatementList* next;
};

class If: public Statement{
	

};
class While: public Statement{
	
};
class Switch: public Statement{
	
};
class Break: public Statement{
	
};
class PrintLn: public Statement{
	
};
class Read: public Statement{
	
};
class Return: public Statement{
	
};
class Throw: public Statement{
	
};

class Call: public Statement{
	
};
class Try: public Statement{
	
};

//Epressions
class Assign: Exp{
	
};
class Or: Exp{
	
};
class And: Exp{
	
};
class Eq: Exp{
	
};
class Neq: Exp{
	
};
class Less: Exp{
	
};
class Leq: Exp{
	
};
class Great: Exp{
	
};
class Geq: Exp{
	
};
class Plus: Exp{
	
    public:
        Exp* exp1;
        Exp* exp2;

};
class Minus: Exp{
	
    public:
        Exp* exp1;
        Exp* exp2;
};
class Pipe: Exp{
	
};
class Mult: Exp{
	
    public:
        Exp exp1;
        Exp exp2;
};
class Div: Exp{
	
};
class Mod: Exp{
	
};
class Ampersand: Exp{
	
};
class UnaryMinus: Exp{
	
};
class Not: Exp{
	
};
class UnaryPlus: Exp{
	
};
class Pointer: Exp{
	
};
class True: Exp{
	
};
class False: Exp{
	
};
class Id: Exp{
	
    public:
        Token* token;

        Id(Token* token){
            
            printf("CREATED ID ");
            printToken(token);
            this->token = token;
        }

};
class Num: Exp{
	
};
class Literal: Exp{
	
};
class Char: Exp{
	
};
class Bool: Exp{
	
};






#endif //CMMCOMPILER_AST_H
