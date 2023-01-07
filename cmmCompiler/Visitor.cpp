//
// Created by Rafael on 07/01/2023.
//

#include "Visitor.h"
//---- Program----
Program::Program(FunctionList *functionList, TypeList *typeList, VarList *varList) {
    this->functionList=functionList;
    this->typeList=typeList;
    this->varList=varList;
}

Program::~Program() {
    delete this->functionList;
    delete this->typeList;
    delete this->varList;
}

//---- VarList----
VarList::VarList(NameDecl *nameDecl, VarList *varList) {
    this->nameDecl= nameDecl;
    this->varList= varList;
}

VarList::~VarList() {
    delete this->nameDecl;
    delete this->varList;
}

//---- NameDecl----
NameDecl::NameDecl(Type *type, Token *id) {
    this->type=type;
    this->id=id;
}

NameDecl::~NameDecl() {
    delete this->type;
    delete this->id;
}

//---- FunctionList----
FunctionList::FunctionList(Type *type, Token *id, VarList *varList, StmtList *stmtList, FunctionList *functionList) {
    this->type=type;
    this->id=id;
    this->varList=varList;
    this->stmtList=stmtList;
    this->functionList=functionList;
}

FunctionList::~FunctionList() {

}

//---- TypeList----
TypeList::TypeList(VarList *varList, Token *id, TypeList *typeList) {
    this->varList=varList;
    this->id=id;
    this->typeList=typeList;
}

TypeList::~TypeList() {
    delete this->varList;
    delete this->id;
    delete this->typeList;
}

//---- Type----
Type::Type(Token *idOrPrimitive, Token *size, Pointer *pointer) {
    this->idOrPrimitive=idOrPrimitive;
    this->size=size;
    this->pointer=pointer;
}

Type::~Type() {
    delete this->idOrPrimitive;
    delete this->size;
    delete this->pointer;
}

//---- Pointer----
Pointer::Pointer(Type *type) {
    this->type=type;
}

Pointer::~Pointer() {
    delete this->type;
}

//---- StmtList----
StmtList::StmtList(Stmt *stmt, StmtList *stmtList) {
    this->stmt=stmt;
    this->stmtList=stmtList;
}

StmtList::~StmtList() {
    delete this->stmt;
    delete this->stmtList;
}

//---- If----
If::If(Exp *exp, Stmt *stmt, Stmt *stmt2) {
    this->exp=exp;
    this->stmt=stmt;
    this->stmt2=stmt2;
}

If::~If() {
    delete this->exp;
    delete this->stmt;
    delete this->stmt2;
}

//---- While----
While::While(Exp *exp, Stmt *stmt) {
    this->exp=exp;
    this->stmt=stmt;
}

While::~While() {
    delete this->exp;
    delete this->stmt;
}

//---- Switch----
Switch::Switch(Exp *exp, CaseBlock *caseBlock) {
    this->exp=exp;
    this->caseBlock=caseBlock;
}

Switch::~Switch() {
    delete this->exp;
    delete this->caseBlock;
}

//---- PrintLn----
PrintLn::PrintLn(ExpList *expList) {
    this->expList=expList;
}

PrintLn::~PrintLn() {
    delete this->expList;
}

//---- Read----
Read::Read(Exp *exp) {
    this->exp=exp;
}

Read::~Read() {
    delete this->exp;
}

//---- Return----
Return::Return(Exp *exp) {
    this->exp=exp;
}

Return::~Return() {
    delete this->exp;
}

//---- CaseBlock----
CaseBlock::CaseBlock(Token *num, StmtList *stmtList, CaseBlock *caseBlock) {
    this->num=num;
    this->stmtList=stmtList;
    this->caseBlock=caseBlock;
}

CaseBlock::~CaseBlock() {
    delete this->num;
    delete this->stmtList;
    delete this->caseBlock;
}

//---- ExpList----
ExpList::ExpList(Exp *exp, ExpList *expList) {
    this->exp=exp;
    this->expList=expList;
}

ExpList::~ExpList() {
    delete this->exp;
    delete this->expList;
}

//---- Try----
Try::Try(Stmt *stmt, Stmt *stmt2) {
    this->stmt=stmt;
    this->stmt2=stmt2;
}

Try::~Try() {
    delete this->stmt;
    delete this->stmt2;
}

//---- ExpVal----
ExpVal::ExpVal(Token *val) {
    this->val=val;
}

ExpVal::~ExpVal() {
    delete this->val;
}

//---- Assign----
Assign::Assign(Exp *exp, Exp *exp2) {
    this->exp=exp;
    this->exp2=exp2;

}

Assign::~Assign() {
    delete this->exp;
    delete this->exp2;
}

//---- Name_Exp----
NameExp::NameExp(Exp *exp, Token *id) {
    this->exp=exp;
    this->id=id;
}

NameExp::~NameExp() {
    delete this->exp;
    delete this->id;
}

//---- PointerValue_Exp----
PointerValueExp::PointerValueExp(Exp *exp, Token *id) {
    this->exp=exp;
    this->id=id;
}

PointerValueExp::~PointerValueExp() {
    delete this->exp;
    delete this->id;
}

//---- AdressValue----
AdressValue::AdressValue(Exp *exp) {
    this->exp=exp;
}

AdressValue::~AdressValue() {
    delete this->exp;
}

//---- PointerValue----
PointerValue::PointerValue(Exp *exp) {
    this->exp=exp;
}

PointerValue::~PointerValue() {
    delete this->exp;
}

//---- Array----
Array::Array(Exp *exp, ExpList *expList) {
    this->exp=exp;
    this->expList=expList;
}

Array::~Array() {
    delete this->exp;
    delete this->expList;
}

//---- Call----
Call::Call(Token *id, ExpList *expList) {
    this->id=id;
    this->expList=expList;
}

Call::~Call() {
    delete this->id;
    delete this->expList;
}

//---- Relational_Op----
RelationalOp::RelationalOp(Token *opRel, Exp *exp, Exp *exp2) {
    this->opRel=opRel;
    this->exp=exp;
    this->exp2=exp2;
}

RelationalOp::~RelationalOp() {
    delete this->opRel;
    delete this->exp;
    delete this->exp2;
}

//---- Addition_Op----
AditionOp::AditionOp(Exp *exp, Exp *exp2) {
    this->exp=exp;
    this->exp2=exp2;
}

AditionOp::~AditionOp() {
    delete this->exp;
    delete this->exp2;
}

//---- Multiplication_Op----
MultiplicationOp::MultiplicationOp(Exp *exp, Exp *exp2) {
    this->exp=exp;
    this->exp2=exp2;
}

MultiplicationOp::~MultiplicationOp() {
    delete this->exp;
    delete this->exp2;
}

//---- Boolean_Op----
BooleanOp::BooleanOp(Token *booleanOp, Exp *exp, Exp *exp2) {
    this->booleanOp=booleanOp;
    this->exp=exp;
    this->exp2=exp2;
}

BooleanOp::~BooleanOp() {
    delete this->booleanOp;
    delete this->exp;
    delete this->exp2;
}

//---- Bitwise_Op----
BitwiseOp::BitwiseOp(Token *bitwiseOp, Exp *exp, Exp *exp2) {
    this->bitwiseOp=bitwiseOp;
    this->exp=exp;
    this->exp2=exp2;
}

BitwiseOp::~BitwiseOp() {
    delete this->bitwiseOp;
    delete this->exp;
    delete this->exp2;
}

//---- Not----
Not::Not(Exp *exp) {
    this->exp=exp;
}

Not::~Not() {
    delete this->exp;
}

//---- Sign----
Sign::Sign(Exp *exp) {
    this->exp=exp;
}

Sign::~Sign() {
    delete this->exp;
}

//------------Concrete Visitors---------------//