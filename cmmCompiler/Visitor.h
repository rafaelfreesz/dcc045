#ifndef CMMCOMPILER_VISITOR_H
#define CMMCOMPILER_VISITOR_H

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


class Visitor {

public:

    virtual void visit(Program* Program) = 0;
    virtual void visit(VarList* varList) = 0;
    virtual void visit(NameDecl* nameDecl) = 0;
    virtual void visit(FunctionList* functionList) = 0;
    // virtual void visit(TypeList* typeList) = 0;
    // virtual void visit(Type* type) = 0;
    // virtual void visit(StatementList* statementList) = 0;
    // virtual void visit(Statement* statement) = 0;
    // virtual void visit(If* if_) = 0;
    // virtual void visit(While* while_) = 0;
    // virtual void visit(Switch* switch_) = 0;
    // virtual void visit(Break* break_) = 0;
    // virtual void visit(PrintLn* printLn_) = 0;
    // virtual void visit(Read* read) = 0;
    // virtual void visit(Return* return_) = 0;
    // virtual void visit(CaseBlock* caseBlock) = 0;
    // virtual void visit(Throw* throw_) = 0;
    // virtual void visit(ExpList* expList) = 0;
    // virtual void visit(Try* try_) = 0;
    // virtual void visit(Exp* exp) = 0;
    // virtual void visit(Assign* assign) = 0;
    // virtual void visit(Or* or_) = 0;
    // virtual void visit(And* and) = 0;
    // virtual void visit(Eq* eq) = 0;
    // virtual void visit(Neq* neq) = 0;
    // virtual void visit(Less* less) = 0;
    // virtual void visit(Leq* leq) = 0;
    // virtual void visit(Great* great) = 0;
    // virtual void visit(Geq* geq) = 0;
    // virtual void visit(Plus* plus) = 0;
    // virtual void visit(Minus* minus) = 0;
    // virtual void visit(Pipe* pipe) = 0;
    // virtual void visit(Mult* mult) = 0;
    // virtual void visit(Div* div) = 0;
    // virtual void visit(Mod* mod) = 0;
    // virtual void visit(Ampersand* ampersand) = 0;
    // virtual void visit(UnaryMinus* unaryMinus) = 0;
    // virtual void visit(Not* not_) = 0;
    // virtual void visit(UnaryPlus* unaryPlus) = 0;
    // virtual void visit(Pointer* pointer) = 0;
    // virtual void visit(True* true_) = 0;
    // virtual void visit(False* false_) = 0;
    // virtual void visit(Call* call) = 0;
    virtual void visit(Id* id) = 0;
    // virtual void visit(Num* num) = 0;
    // virtual void visit(Literal* literal) = 0;
    // virtual void visit(Char* char_) = 0;
    // virtual void visit(Bool* booL) = 0;


};

class visitorPrintAST: public Visitor{

public:
    virtual void visit(Program* Program);
    virtual void visit(VarList* varList);
    virtual void visit(NameDecl* nameDecl);
    virtual void visit(FunctionList* functionList);
    // virtual void visit(TypeList* typeList);
    // virtual void visit(Type* type);
    // virtual void visit(StatementList* statementList);
    // virtual void visit(Statement* statement);
    // virtual void visit(If* if_);
    // virtual void visit(While* while_);
    // virtual void visit(Switch* switch_);
    // virtual void visit(Break* break_);
    // virtual void visit(PrintLn* printLn_);
    // virtual void visit(Read* read);
    // virtual void visit(Return* return_);
    // virtual void visit(CaseBlock* caseBlock);
    // virtual void visit(Throw* throw_);
    // virtual void visit(ExpList* expList);
    // virtual void visit(Try* try_);
    // virtual void visit(Exp* exp);
    // virtual void visit(Assign* assign);
    // virtual void visit(Or* or_);
    // virtual void visit(And* and);
    // virtual void visit(Eq* eq);
    // virtual void visit(Neq* neq);
    // virtual void visit(Less* less);
    // virtual void visit(Leq* leq);
    // virtual void visit(Great* great);
    // virtual void visit(Geq* geq);
    // virtual void visit(Plus* plus);
    // virtual void visit(Minus* minus);
    // virtual void visit(Pipe* pipe);
    // virtual void visit(Mult* mult);
    // virtual void visit(Div* div);
    // virtual void visit(Mod* mod);
    // virtual void visit(Ampersand* ampersand);
    // virtual void visit(UnaryMinus* unaryMinus);
    // virtual void visit(Not* not_);
    // virtual void visit(UnaryPlus* unaryPlus);
    // virtual void visit(Pointer* pointer);
    // virtual void visit(True* true_);
    // virtual void visit(False* false_);
    // virtual void visit(Call* call);
    virtual void visit(Id* id);
    // virtual void visit(Num* num);
    // virtual void visit(Literal* literal);
    // virtual void visit(Char* char_);
    // virtual void visit(Bool* booL);


};



#endif //CMMCOMPILER_AST_H
