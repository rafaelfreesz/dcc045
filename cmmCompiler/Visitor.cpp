#include "Visitor.h"
#include "Ast.h"
#include "stdio.h"

void visitorPrintAST::visit(Program* program){

    if(program->globalVarList) program->globalVarList->accept(this);
    if(program->functionList) program->functionList->accept(this);
    // if(program->typeList) program->functionList->accept(this);

}

void visitorPrintAST::visit(VarList* varList){

    VarList* currentVarList = varList;
    while(currentVarList){
        printf("\t");
        currentVarList->nameDecl->accept(this);
        currentVarList = currentVarList->next;
    }

}

void visitorPrintAST::visit(FunctionList* functionList){

    FunctionList* currentFunctionList = functionList;

    while(currentFunctionList){
        currentFunctionList->id->accept(this);
        currentFunctionList->varList->accept(this);
        currentFunctionList = currentFunctionList->next;
    }

}

void visitorPrintAST::visit(NameDecl* nameDecl){

    if(nameDecl->id) nameDecl->id->accept(this);
}

void visitorPrintAST::visit(Id* id){

    printToken(id->token);

}
