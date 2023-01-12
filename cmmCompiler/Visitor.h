//
// Created by Rafael on 07/01/2023.
//

#ifndef CMMCOMPILER_VISITOR_H
#define CMMCOMPILER_VISITOR_H
#include "LexicalAnalyzer.h"

class Root;
class Program;
class VarList;
class NameDecl;
class FunctionList;
class TypeList;
class Type;
class TypeId;
class TypePrimitive;
class TypePointer;
class Pointer;
class StmtList;
class Stmt;
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
class ExpVal;
class Assign;
class NameExp;
class PointerValueExp;
class AdressValue;
class PointerValue;
class Array;
class Call;
class RelationalOp;
class AditionOp;
class MultiplicationOp;
class BooleanOp;
class BitwiseOp;
class True;
class False;
class Not;
class Sign;

class Visitor {
public:
    Visitor(){};
    virtual void visit (Program* program )=0;
    virtual void visit (VarList* varList)=0;
    virtual void visit (NameDecl* nameDecl)=0;
    virtual void visit (FunctionList* functionList)=0;
    virtual void visit (TypeList* typeList)=0;
    virtual void visit (Type* type)=0;
    virtual void visit (TypeId* typeId)=0;
    virtual void visit (TypePrimitive* typePrimitive)=0;
    virtual void visit (Pointer* pointer)=0;
    virtual void visit (StmtList* stmtList)=0;
    virtual void visit (Stmt* stmt)=0;
    virtual void visit (If* anIf)=0;
    virtual void visit (While* aWhile)=0;
    virtual void visit (Switch* aSwitch)=0;
    virtual void visit (Break* aBreak)=0;
    virtual void visit (PrintLn* printLn)=0;
    virtual void visit (Read* read)=0;
    virtual void visit (Return* aReturn)=0;
    virtual void visit (CaseBlock* caseBlock)=0;
    virtual void visit (Throw* aThrow)=0;
    virtual void visit (ExpList* expList)=0;
    virtual void visit (Try* aTry)=0;
    virtual void visit (Exp* exp)=0;
    virtual void visit (ExpVal* expVal)=0;
    virtual void visit (Assign* assign)=0;
    virtual void visit (NameExp* nameExp)=0;
    virtual void visit (PointerValueExp* pointerValueExp)=0;
    virtual void visit (AdressValue* adressValue)=0;
    virtual void visit (PointerValue* pointerValue)=0;
    virtual void visit (Array* array)=0;
    virtual void visit (Call* aConst)=0;
    virtual void visit (RelationalOp* relationalOp)=0;
    virtual void visit (AditionOp* aditionOp)=0;
    virtual void visit (MultiplicationOp* multiplicationOp)=0;
    virtual void visit (BooleanOp* booleanOp)=0;
    virtual void visit (BitwiseOp* bitwiseOp)=0;
    virtual void visit (True* aTrue)=0;
    virtual void visit (False* aFalse)=0;
    virtual void visit (Not* aNot)=0;
    virtual void visit (Sign* sign)=0;
    virtual void visit (Token* token)=0;

};

class ConcreteVisitor: public Visitor{
public:
    ConcreteVisitor(){this->depth=0;};
    ~ConcreteVisitor();
    void visit (Program* program ) override;
    void visit (VarList* varList) override;
    void visit (NameDecl* nameDecl) override;
    void visit (FunctionList* functionList) override;
    void visit (TypeList* typeList) override;
    void visit (Type* type) override;
    void visit (TypeId* typeId) override;
    void visit (TypePrimitive* typePrimitive) override;
    void visit (Pointer* pointer) override;
    void visit (StmtList* stmtList) override;
    void visit (Stmt* stmt) override;
    void visit (If* anIf) override;
    void visit (While* aWhile) override;
    void visit (Switch* aSwitch) override;
    void visit (Break* aBreak) override;
    void visit (PrintLn* printLn) override;
    void visit (Read* read) override;
    void visit (Return* aReturn) override;
    void visit (CaseBlock* caseBlock) override;
    void visit (Throw* aThrow) override;
    void visit (ExpList* expList) override;
    void visit (Try* aTry) override;
    void visit (Exp* exp) override;
    void visit (ExpVal* expVal) override;
    void visit (Assign* assign) override;
    void visit (NameExp* nameExp) override;
    void visit (PointerValueExp* pointerValueExp) override;
    void visit (AdressValue* adressValue) override;
    void visit (PointerValue* pointerValue) override;
    void visit (Array* array) override;
    void visit (Call* aConst) override;
    void visit (RelationalOp* relationalOp) override;
    void visit (AditionOp* aditionOp) override;
    void visit (MultiplicationOp* multiplicationOp) override;
    void visit (BooleanOp* booleanOp) override;
    void visit (BitwiseOp* bitwiseOp) override;
    void visit (True* aTrue) override;
    void visit (False* aFalse) override;
    void visit (Not* aNot) override;
    void visit (Sign* sign) override;
    void visit (Token* token) override;
    int depth;
    
};

class Root{
public:
    Root(){};
    ~Root(){};

    virtual void accept(Visitor* v)=0;
};

class Program: public Root{
public:
    Program(FunctionList* functionList, TypeList* typeList, VarList* varList);
    ~Program();

    FunctionList* functionList;
    FunctionList* lastFunctionList;
    TypeList* typeList;
    TypeList* lastTypeList;
    VarList* varList;
    VarList* lastVarList;
    bool pointed;
    void accept(Visitor* v) override {v->visit(this);};

};
class VarList: public Root{
public:
    VarList(NameDecl* nameDecl, VarList* varList);
    ~VarList();

    NameDecl* nameDecl;
    VarList* varList;
    void accept(Visitor* v) override {v->visit(this);};

};
class NameDecl: public Root{
public:
    NameDecl(Type* type, Token* id);
    ~NameDecl();
    
    Type* type;
    Token* id;
    void accept(Visitor* v) override {v->visit(this);};

};
class FunctionList: public Root{
public:

    FunctionList(Type *type, Token *id, VarList *varList1, VarList *varList2, StmtList *stmtList,
                 FunctionList *functionList);
    ~FunctionList();

    Type* type;
    Token* id;
    VarList* varList1;
    VarList* varList2;
    StmtList* stmtList;
    FunctionList* functionList;

    void accept(Visitor* v) override {v->visit(this);};
};

class TypeList: public Root{
public:
    TypeList(VarList *varList, Token *id, TypeList *typeList);
    ~TypeList();

    VarList* varList;
    Token * id;
    TypeList* typeList;

    void accept(Visitor* v) override {v->visit(this);};
};
class Type: public Root{
public:

    Type(){ printf("\t\tAST_TYPE\n");};
    ~Type(){};

    void accept(Visitor* v) override {v->visit(this);};

};
class TypeId: public Type{
public:

    TypeId(Token* id, Array* size);
    ~TypeId();

    Token* id;
    Array* size;

    void accept(Visitor* v) override {v->visit(this);};

};
class TypePrimitive: public Type{
public:

    TypePrimitive(Token *primitive, Array *size);
    ~TypePrimitive();

    Token* primitive;
    Array* size;

    void accept(Visitor* v) override {v->visit(this);};

};
class Pointer: public Type{
public:
    Pointer(Type* type);
    ~Pointer();

    Type* type;

    void accept(Visitor* v) override {v->visit(this);};
};

class StmtList: public Root{
public:
    StmtList(Stmt* stmt, StmtList* stmtList);
    ~StmtList();

    Stmt* stmt;
    StmtList* stmtList;

    void accept(Visitor* v) override {v->visit(this);};
};

class Stmt: public Root{
public:
    Stmt(){};
    ~Stmt(){};

    void accept(Visitor* v) override {v->visit(this);};
};

class If: public Stmt{
public:
    If(Exp* exp, Stmt* stmt, Stmt* stmt2);
    ~If();

    Exp* exp;
    Stmt* stmt;
    Stmt* stmt2;

    void accept(Visitor* v) override {v->visit(this);};
};
class While: public Stmt{
public:
    While(Exp* exp, Stmt* stmt);
    ~While();

    Exp* exp;
    Stmt* stmt;

    void accept(Visitor* v) override {v->visit(this);};
};

class Switch: public Stmt{
public:
    Switch(Exp* exp, CaseBlock* caseBlock);
    ~Switch();

    Exp* exp;
    CaseBlock* caseBlock;

    void accept(Visitor* v) override {v->visit(this);};
};

class Break: public Stmt{
public:
    Break(){};
    ~Break(){};

    void accept(Visitor* v) override {v->visit(this);};
};

class PrintLn: public Stmt{
public:
    PrintLn(ExpList* expList);
    ~PrintLn();

    ExpList* expList;

    void accept(Visitor* v) override {v->visit(this);};
};

class Read: public Stmt{
public:
    Read(Exp* exp);
    ~Read();

    Exp* exp;

    void accept(Visitor* v) override {v->visit(this);};
};

class Return: public Stmt{
public:
    Return(Exp* exp);
    ~Return();

    Exp* exp;

    void accept(Visitor* v) override {v->visit(this);};
};

class CaseBlock: public Stmt{
public:
    CaseBlock(Token* num, StmtList* stmtList, CaseBlock* caseBlock);
    ~CaseBlock();

    Token* num;
    StmtList* stmtList;
    CaseBlock* caseBlock;

    void accept(Visitor* v) override {v->visit(this);};
};

class Throw: public Stmt{
public:
    Throw(){};
    ~Throw(){};

    void accept(Visitor* v) override {v->visit(this);};

};

class ExpList: public Root{
public:
    ExpList(Exp* exp, ExpList* expList);
    ~ExpList();

    Exp* exp;
    ExpList* expList;

    void accept(Visitor* v) override {v->visit(this);};
};

class Try: public Root{
public:
    Try(Stmt* stmt, Stmt* stmt2);
    ~Try();

    Stmt* stmt;
    Stmt* stmt2;

    void accept(Visitor* v) override {v->visit(this);};
};

class Exp: public Root{
public:
    Exp(){};
    ~Exp(){};

    void accept(Visitor* v) override {v->visit(this);};
};

class ExpVal: public Exp{
public:
    ExpVal(Token* val);
    ~ExpVal();

    Token * val;

    void accept(Visitor* v) override {v->visit(this);};
};

class Assign: public Exp{
public:
    Assign(Exp* exp, Exp* exp2);
    ~Assign();

    Exp* exp;
    Exp* exp2;

    void accept(Visitor* v) override {v->visit(this);};
};

class NameExp: public Exp{
public:
    NameExp(Exp* exp, Token* id);
    ~NameExp();

    Exp* exp;
    Token * id;

    void accept(Visitor* v) override {v->visit(this);};

};

class PointerValueExp: public Exp{
public:
    PointerValueExp(Exp* exp, Token* id);
    ~PointerValueExp();

    Exp* exp;
    Token * id;

    void accept(Visitor* v) override {v->visit(this);};

};

class AdressValue: public Exp{
public:
    AdressValue(Exp* exp);
    ~AdressValue();

    Exp* exp;

    void accept(Visitor* v) override {v->visit(this);};
};

class PointerValue: public Exp{
public:
    PointerValue(Exp* exp);
    ~PointerValue();

    Exp* exp;

    void accept(Visitor* v) override {v->visit(this);};

};

class Array: public Exp{
public:
    Array(Exp* exp, Array *array);
    ~Array();

    Exp* exp;
    Array* array;

    void accept(Visitor* v) override {v->visit(this);};

};

class Call: public Exp{
public:
    Call(Token* id, ExpList* expList);
    ~Call();

    Token * id;
    ExpList* expList;

    void accept(Visitor* v) override {v->visit(this);};
};

class RelationalOp: public Exp{
public:
    RelationalOp(Token* opRel, Exp* exp, Exp* exp2);
    ~RelationalOp();

    Token* opRel;
    Exp* exp;
    Exp* exp2;

    void accept(Visitor* v) override {v->visit(this);};
};

class AditionOp: public Exp{
public:
    AditionOp(Exp* exp, Exp* exp2); //TODO por que precisa do OP_ADD se a classe ja sabe que é add?
    ~AditionOp();

    Exp* exp;
    Exp* exp2;

    void accept(Visitor* v) override {v->visit(this);};
};

class MultiplicationOp: public Exp{
public:
    MultiplicationOp(Exp* exp, Exp* exp2); //TODO por que precisa do OP_ADD se a classe ja sabe que é mult?
    ~MultiplicationOp();

    Exp* exp;
    Exp* exp2;

    void accept(Visitor* v) override {v->visit(this);};
};

class BooleanOp: public Exp{
public:
    BooleanOp(Token *booleanOp, Exp* exp, Exp* exp2);
    ~BooleanOp();

    Token * booleanOp;
    Exp* exp;
    Exp* exp2;

    void accept(Visitor* v) override {v->visit(this);};
};

class BitwiseOp: public Exp{
public:
    BitwiseOp(Token *bitwiseOp, Exp* exp, Exp* exp2);
    ~BitwiseOp();

    Token * bitwiseOp;
    Exp* exp;
    Exp* exp2;

    void accept(Visitor* v) override {v->visit(this);};
};

class True: public Exp{
public:
    True(){};
    ~True(){};

    void accept(Visitor* v) override {v->visit(this);};
};

class False: public Exp{
public:
    False(){};
    ~False(){};

    void accept(Visitor* v) override {v->visit(this);};
};

class Not: public Exp{
public:
    Not(Exp* exp);
    ~Not();

    Exp* exp;

    void accept(Visitor* v) override {v->visit(this);};
};

class Sign: public Exp{
public:
    Sign(Exp* exp);
    ~Sign();

    Exp* exp;

    void accept(Visitor* v) override {v->visit(this);};
};

#endif //CMMCOMPILER_VISITOR_H
