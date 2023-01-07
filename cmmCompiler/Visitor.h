//
// Created by Rafael on 07/01/2023.
//

#ifndef CMMCOMPILER_VISITOR_H
#define CMMCOMPILER_VISITOR_H

class Program;
class VarList;
class NameDecl;
class FunctionList;
class TypeList;
class Type;
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
    Visitor();
    virtual void visit (Program* program )=0;
    virtual void visit (VarList* varList)=0;
    virtual void visit (NameDecl* nameDecl)=0;
    virtual void visit (FunctionList* functionList)=0;
    virtual void visit (TypeList* typeList)=0;
    virtual void visit (Type* type)=0;
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

};

class ConcreteVisitor: public Visitor{
public:
    ConcreteVisitor();
    ~ConcreteVisitor();
    void visit (Program* program ) override;
    void visit (VarList* varList) override;
    void visit (NameDecl* nameDecl) override;
    void visit (FunctionList* functionList) override;
    void visit (TypeList* typeList) override;
    void visit (Type* type) override;
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
    
};

#endif //CMMCOMPILER_VISITOR_H
