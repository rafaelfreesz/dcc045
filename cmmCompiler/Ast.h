#ifndef CMMCOMPILER_AST_H
#define CMMCOMPILER_AST_H

#include "LexicalAnalyzer.h"
#include "Visitor.h"

class Statement {};

class Exp : public Statement{

public:
    virtual void accept(Visitor *v) = 0;

};

class Type {

public:
    Id* id;
    size_t size;

    Type(Id* id, size_t size){

        this->id = id;
        this->size = size;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }

};

class ExpList {

public:
    Exp* exp;
    ExpList* next;

};

class VarList {

public:
    NameDecl* nameDecl;
    VarList* next;

    VarList(NameDecl* nameDecl, VarList* next){
        this->nameDecl = nameDecl;
        this->next = next;
    }

    void accept(Visitor *v){
        v->visit(this);
    }

};

class NameDecl {

public:
    Type* type;
    Id* id;

    NameDecl(Type* type, Id* id){
        this->type = type;
        this-> id = id;
    }

    void accept(Visitor *v){
        v->visit(this);
    }
};

class FunctionList {

public:
    Type* type;
    Id* id;
    VarList* varList;
    VarList* paramList;
    StatementList* stmtList;
    FunctionList* next;

    FunctionList(Type* type, Id* id, VarList* varList, StatementList* stmtList, FunctionList* next){
        printf("CREATED FUNCTIONLIST\n");
        this->type = type;
        this->id = id;
        this->varList = varList;

        this->paramList = paramList;
        this->stmtList = stmtList;
        this->next = next;


    }

    void accept(Visitor *v){
        v->visit(this);
    }

};

class TypeList {

public:
    VarList* varList;
    Id* id;
    TypeList* next;

    TypeList(VarList* varList, Id* id, TypeList* next){

        this->varList = varList;
        this->id = id;
        this->next = next;
    }

    void accept(Visitor *v){
        // v->visit(this);
    }

};

class Program {

public:
    FunctionList* functionList;
    TypeList* typeList;
    VarList* globalVarList;

    Program(){

        this->functionList = NULL;
        this->typeList = NULL;
        this->globalVarList = NULL;
    }

    void accept(Visitor *v){
        v->visit(this);
    }

};

class CaseBlock {

public:
    Exp* num;
    StatementList* statementList;
    CaseBlock* caseblock;
};

//Statements
class StatementList: public Statement{

public:
    Statement* stmt;
    StatementList* next;

    StatementList(Statement* stmt, StatementList* next){
        this->stmt = stmt;
        this->next = next;
    }

    void accept(Visitor *v){
        // v->visit(this);
    }
};

class If: public Statement{

public:


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
class Assign: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Assign(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }


};

class Or: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Or(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class And: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    And(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Eq: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Eq(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Neq: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Neq(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Less: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Less(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Leq: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Leq(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Great: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Great(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Geq: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Geq(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Plus: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Plus(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }

};
class Minus: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Minus(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Pipe: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Pipe(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Mult: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Mult(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Div: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Div(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Mod: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Mod(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class Ampersand: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Ampersand(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class UnaryMinus: public Exp{

public:
    Exp* exp1;

    UnaryMinus(Exp* exp1){
        this->exp1 = exp1;

    }

    void accept(Visitor *v){
        //v->visit(this);
    }

};
class Not: public Exp{

public:
    Exp* exp1;

    Not(Exp* exp1){
        this->exp1 = exp1;

    }

    void accept(Visitor *v){
        //v->visit(this);
    }
};
class UnaryPlus: public Exp{

public:
    Exp* exp1;

    UnaryPlus(Exp* exp1){
        this->exp1 = exp1;

    }

    void accept(Visitor *v){
        //v->visit(this);
    }

};

class Pointer: public Exp{

public:
    Exp* exp1;
    Exp* exp2;

    Pointer(Exp* exp1, Exp* exp2){
        this->exp1 = exp1;
        this->exp2 = exp2;
    }

    void accept(Visitor *v){
        //v->visit(this);
    }

};

class True: public Exp{


};
class False: public Exp{

};

class Num: public Exp{

};
class Literal: public Exp{

};
class Char: public Exp{

};
class Bool: public Exp{

};

class Id: public Exp{

public:
    Token* token;

    Id(Token* token){

        this->token = token;
    }

    void accept(Visitor *v){
        v->visit(this);
    }

};

#endif //CMMCOMPILER_AST_H
