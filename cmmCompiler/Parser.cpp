#include "Parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}
void Parser::error() {
    string transltation=translate(this->token->token);
    cout<<"Error! token "+ transltation<<endl;
    exit(100);
}
void Parser::match(int token) {

    if(token != FIRSTTOKEN) {
        if (token == this->token->token) {
            cout<<"---- "<<translate(token);
            this->token = nextToken();
            cout<<"----> "<< translate(this->token->token)<<" ---"<<endl;
        } else {
            cout<<"Unexpected token "<< translate(this->token->token)<<". Expected: "<<translate(token)<<endl;
            exit(100);
        }
    }else{
        this->token = nextToken();
        cout<<" ---- "<<translate(this->token->token)<<endl;
    }
}

void Parser::parse() {

    Parser* parser = new Parser();
    parser->match(FIRSTTOKEN);
    parser->program();
    cout<<"SUCCESS!"<<endl;


}

void Parser::program() {

    printf("PROGRAM\n");
    switch (this->token->token) {
        case DOUBLE:
        case CHAR:
        case ID:
        case BOOL:
        case FLOAT:
        case INT:
        case LONG:
            declprefix();
            declsulfix(); break;
        case TYPEDEF:
            typedecl();
            program(); break;
        case CMMEOF:
            match(CMMEOF);
            return;

        default: error();

    }

}

void Parser::declprefix() {

    printf("declprefix\n");
    type();
    pointer();
    match(ID);

}

void Parser::declsulfix() {

    printf("declsulfix\n");
    switch (this->token->token){

        case LEFTPARENTHESES:
            functionDecl();
            program2();
            break;

        case LEFTBRACKET:
        case COMMA:
        case SEMICOLON:
            varDeclSulfix();
            program();
            break;

    }

}

void Parser::program2(){

    printf("program2\n");

    switch (this->token->token) {
        case DOUBLE:
        case CHAR:
        case ID:
        case BOOL:
        case FLOAT:
        case INT:
        case LONG:
        case TYPEDEF:
            program();
            break;
        case CMMEOF:
            match(CMMEOF);
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }

}

void Parser::varDeclSulfix(){

    printf("varDeclSulfix\n");
    switch (this->token->token) {
        case LEFTBRACKET:
        case COMMA:
        case SEMICOLON:
            array();
            idList2();
            match(SEMICOLON);
            break;
        default:error();

    }

}

void Parser::varDecl(){

    printf("varDecl\n");

    switch (this->token->token) {
        case INT:
        case FLOAT:
        case LONG:
        case DOUBLE:
        case BOOL:
        case ID:
        case CHAR:
            type();
            pointer();
            match(ID);
            array();
            idList2();
            match(SEMICOLON);
            varDecl2();
            break;
        default: error();

    }


}

void Parser::varDecl2(){

    printf("varDecl2\n");
    switch (this->token->token) {
        case INT:
        case FLOAT:
        case LONG:
        case DOUBLE:
        case BOOL:
        case ID:
        case CHAR:
            type();
            pointer();
            match(ID);
            array();
            idList2();
            match(SEMICOLON);
            varDecl2();
            break;
        case RIGHTBRACE:
            cout<<"epsilon"<<endl; return;
        default:
            error();


    }


}

void Parser::functionDecl(){

    printf("functionDecl\n");
    switch (this->token->token) {
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            formalList();
            match(RIGHTPARENTHESES);
            match(LEFTBRACE);
            functionBody();
            match(RIGHTBRACE);
            break;
        default: error();
        
    }

}

void Parser::functionBody() {

    printf("functionBody\n");
    switch (this->token->token) {
        case LONG:
        case INT:
        case FLOAT:
        case BOOL:
        case CHAR:
        case DOUBLE:
            typeCompl();
            pointer();
            match(ID);
            array();
            idList2();
            match(SEMICOLON);
            functionBody();
            break;
        case ID:
            match(ID);
            functionBody2();
            break;
        case PLUS:
        case NOT:
        case MINUS:
        case LEFTPARENTHESES:
        case FALSE:
        case TRUE:
        case MULT:
        case AMPERSAND:
        case LITERAL:
        case NUMFLOAT:
        case NUMINT:
        case LEFTBRACE:
        case THROW:
        case RETURN:
        case READLN:
        case PRINT:
        case BREAK:
        case SWITCH:
        case WHILE:
        case IF:
        case STRUCT:
            stmtCompl();
            stmtList2();
            break;
        case RIGHTBRACE:
            cout<<"epsilon"<<endl; return;



    }
}

void Parser::functionBody2() {

    printf("functionBody2\n");
    switch (this->token->token) {
        case ID:
            match(ID);
            pointer();
            match(ID);
            array();
            idList2();
            match(SEMICOLON);
            functionBody();
            break;
        case PLUS:
        case MINUS:
        case AMPERSAND:
        case MOD:
        case DIV:
        case PIPE:
        case GEQ:
        case GREAT:
        case LEQ:
        case LESS:
        case NEQ:
        case EQ:
        case AND:
        case OR:
        case ASSIGN:
            binOp();
            expr();
            match(SEMICOLON);
            stmtList2();
            break;
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            exprList();
            match(RIGHTPARENTHESES);
            match(SEMICOLON);
            stmtList2();
            break;
        case MULT:
            match(MULT);
            expr();
            functionBody3();
            break;


    }
}

void Parser::binOp() {

    printf("binOp\n");
    switch (this->token->token) {
        case PLUS:
            match(PLUS);
            break;
        case MINUS:
            match(MINUS);
            break;
        case AMPERSAND:
            match(AMPERSAND);
            break;
        case MOD:
            match(MOD);
            break;
        case DIV:
            match(DIV);
            break;
        case PIPE:
            match(PIPE);
            break;
        case GEQ:
            match(GEQ);
            break;
        case GREAT:
            match(GREAT);
            break;
        case LEQ:
            match(LEQ);
            break;
        case LESS:
            match(LESS);
            break;
        case NEQ:
            match(NEQ);
            break;
        case EQ:
            match(EQ);
            break;
        case AND:
            match(AND);
            break;
        case OR:
            match(OR);
            break;
        case ASSIGN:
            match(ASSIGN);
            break;
        
    }
}

void Parser::functionBody3() {
    printf("functionBody3\n");
    switch (this->token->token) {
        case COMMA:
            match(COMMA);
            idList2();
            match(SEMICOLON);
            functionBody();
            break;
        case SEMICOLON:
            match(SEMICOLON);
            functionBody();
            break;
        default:
            error();
    }

}

void Parser::idList(){

    printf("idList\n");
    switch (this->token->token) {
        case ID:
        case MULT:
            pointer();
            match(ID);
            array();
            idList2();
            break;
        default:
            error();
    }

}

void Parser::idList2(){

    printf("idList2\n");
    switch (this->token->token)
    {
        case COMMA:
            match(COMMA);
            pointer();
            match(ID);
            array();
            idList2();
            break;

        case SEMICOLON:
            cout<<"epsilon"<<endl; return;

        default:
            error();
    }



}

void Parser::typedecl() {

    printf("typedecl\n");
    switch (this->token->token) {
        case TYPEDEF:
            match(TYPEDEF);
            match(STRUCT);
            match(LEFTBRACE);
            type();
            idList();
            match(SEMICOLON);
            varDecl();
            match(RIGHTBRACE);
            match(ID);
            match(SEMICOLON);
            break;
        default:
            error();

    }

}

void Parser::array() {

    printf("array\n");
    switch (this->token->token) {
        case LEFTBRACKET:
            match(LEFTBRACKET);
            match(NUMINT);
            match(RIGHTBRACKET);
            array();
            break;

        case RIGHTPARENTHESES:
        case SEMICOLON:
        case COMMA:
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }

}

void Parser::formalList(){

    printf("formalList\n");
    switch (this->token->token)
    {
        case LONG:
        case INT:
        case FLOAT:
        case BOOL:
        case ID:
        case CHAR:
        case DOUBLE:
            type();
            pointer();
            match(ID);
            array();
            formalRest();
            break;

        case RIGHTPARENTHESES:
            cout<<"epsilon"<<endl; return;

        default:
            error();
    }


}

void Parser::formalRest(){

    printf("formalRest\n");
    switch (this->token->token)
    {
        case COMMA:
            match(COMMA);
            type();
            pointer();
            match(ID);
            array();
            formalRest();
            break;

        case RIGHTPARENTHESES:
            cout<<"epsilon"<<endl; return;

        default:
            error();
    }


}

void Parser::stmtList(){

    printf("stmtList\n");
    switch (this->token->token) {
        case ID:
        case NOT:
        case MINUS:
        case PLUS:
        case LEFTPARENTHESES:
        case FALSE:
        case TRUE:
        case MULT:
        case AMPERSAND:
        case LITERAL:
        case NUMINT:
        case NUMFLOAT:
        case TRY:
        case LEFTBRACE:
        case THROW:
        case RETURN:
        case READLN:
        case PRINT:
        case BREAK:
        case SWITCH:
        case WHILE:
        case ELSE:
        case IF:
            stmt();
            stmtList2();
            break;
        default:error();

        
    }


}

void Parser::stmtList2(){

    printf("stmtList2\n");
    switch (this->token->token)
    {
        case  IF:
        case  WHILE:
        case  SWITCH:
        case  BREAK:
        case  PRINT:
        case  READLN:
        case  RETURN:
        case  THROW:
        case  LEFTBRACE:
        case  TRY:
        case  ID:
        case  MINUS:
        case  NOT:
        case  PLUS:
        case  LEFTPARENTHESES:
        case  NUMINT:
        case  NUMFLOAT:
        case  LITERAL:
        case  AMPERSAND:
        case  MULT:
        case  TRUE:
        case  FALSE:
            stmt();
            stmtList2();
            break;

        case CASE:
        case RIGHTBRACE:
            cout<<"epsilon"<<endl; return;

        default:
            error();
    }

}

void Parser::stmt(){

    printf("stmt\n");
    switch (this->token->token)
    {
        case IF:
            match(IF);
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            stmt();
            match(ELSE);
            stmt();
            break;

        case WHILE:
            match(WHILE);
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            stmt();
            break;

        case SWITCH:
            match(WHILE);
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            match(LEFTBRACE);
            caseblock();
            match(RIGHTBRACE);
            break;

        case BREAK:
            match(BREAK);
            match(SEMICOLON);
            break;

        case PRINT:
            match(PRINT);
            match(LEFTPARENTHESES);
            exprList();
            match(RIGHTPARENTHESES);
            match(SEMICOLON);
            break;

        case READLN:
            match(READLN);
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            match(SEMICOLON);
            break;

        case RETURN:
            match(RETURN);
            expr();
            match(SEMICOLON);
            break;

        case THROW:
            match(THROW);
            match(SEMICOLON);
            break;

        case LEFTBRACE:
            match(LEFTBRACE);
            stmtList();
            match(RIGHTBRACE);
            break;

        case TRY:
            match(TRY);
            stmt();
            match(CATCH);
            match(LEFTPARENTHESES);
            match(RIGHTPARENTHESES);
            stmt();
            break;

        case ID:
            match(ID);
            stmt1();
            match(SEMICOLON);
            break;

        case MINUS:
        case NOT:
        case PLUS:
            unaryOp();
            stmtPrim3();
            match(SEMICOLON);
            break;

        case LEFTPARENTHESES:
        case FALSE:
        case TRUE:
        case MULT:
        case AMPERSAND:
        case LITERAL:
        case NUMINT:
        case NUMFLOAT:
            stmtPrim();
            stmt2();
            match(SEMICOLON);
            break;

        default:
            error();
    }

}
void Parser::stmtCompl(){

    printf("stmtCompl\n");
    switch (this->token->token)
    {
        case IF:
            match(IF);
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            stmt();
            match(ELSE);
            stmt();
            break;

        case WHILE:
            match(WHILE);
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            stmt();
            break;

        case SWITCH:
            match(WHILE);
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            match(LEFTBRACE);
            caseblock();
            match(RIGHTBRACE);
            break;

        case BREAK:
            match(BREAK);
            match(SEMICOLON);
            break;

        case PRINT:
            match(PRINT);
            match(LEFTPARENTHESES);
            exprList();
            match(RIGHTPARENTHESES);
            match(SEMICOLON);
            break;

        case READLN:
            match(READLN);
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            match(SEMICOLON);
            break;

        case RETURN:
            match(RETURN);
            expr();
            match(SEMICOLON);
            break;

        case THROW:
            match(THROW);
            match(SEMICOLON);
            break;

        case LEFTBRACE:
            match(LEFTBRACE);
            stmtList();
            match(RIGHTBRACE);
            break;

        case TRY:
            match(TRY);
            stmt();
            match(CATCH);
            match(LEFTPARENTHESES);
            match(RIGHTPARENTHESES);
            stmt();
            break;

        case MINUS:
        case NOT:
        case PLUS:
            unaryOp();
            stmtPrim3();
            match(SEMICOLON);
            break;

        case LEFTPARENTHESES:
        case FALSE:
        case TRUE:
        case MULT:
        case AMPERSAND:
        case LITERAL:
        case NUMINT:
        case NUMFLOAT:
            stmtPrim();
            stmt2();
            match(SEMICOLON);
            break;

        default:
            error();
    }

}

void Parser::stmtPrim(){

    printf("stmtPrim\n");
    switch (this->token->token)
    {
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            stmt2();
            break;

        case NUMINT:
        case NUMFLOAT:
        case LITERAL:
        case AMPERSAND:
        case MULT:
        case TRUE:
        case FALSE:
            stmtPrim2();
            break;

        default:
            error();
    }

}

void Parser::stmtPrim2(){

    printf("stmtPrim2\n");
    switch (this->token->token)
    {

        case NUMINT:
            match(NUMINT);
            stmt2();
            break;
        case NUMFLOAT:
            match(NUMFLOAT);
            stmt2();
            break;

        case LITERAL:
            match(LITERAL);
            stmt2();
            break;
        case TRUE:
            match(TRUE);
            stmt2();
            break;
        case FALSE:
            match(FALSE);
            stmt2();
            break;

        case AMPERSAND:
            match(AMPERSAND);
            expr();
            stmt2();
            break;
        case MULT:
            match(MULT);
            expr();
            stmt2();
            break;

        default:
            error();
    }

}

void Parser::stmtPrim3(){

    printf("stmtPrim3\n");
    switch (this->token->token)
    {

        case ID:
            match(ID);
            stmt1();
            break;

        case LEFTPARENTHESES:
        case NUMINT:
        case NUMFLOAT:
        case LITERAL:
        case AMPERSAND:
        case MULT:
        case TRUE:
        case FALSE:
            stmtPrim();
            stmt2();
            break;

        default:
            error();
    }

}

void Parser::stmt1(){

    printf("stmt1\n");
    switch (this->token->token)
    {
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            exprList();
            match(RIGHTPARENTHESES);
            break;

        case ASSIGN:
        case OR:
        case AND:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case POINT:
        case POINTER:
        case LEFTBRACKET:
        case SEMICOLON:
            stmt2();
            break;

        default:
            error();
    }


}

void Parser::stmt2(){

    printf("stmt2\n");
    switch (this->token->token)
    {

        case ASSIGN:
            match(ASSIGN);
            expr();
            break;
        case OR:
        case AND:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case POINT:
        case POINTER:
        case LEFTBRACKET:
        case SEMICOLON:
            stmt3();
            break;

        default:
            error();
    }

}

void Parser::stmt3(){

    printf("stmt3\n");
    switch (this->token->token)
    {

        case OR:
            match(OR);
            expr();
            break;
        case ASSIGN:
        case AND:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case POINT:
        case POINTER:
        case LEFTBRACKET:
        case SEMICOLON:
            stmt4();
            break;

        default:
            error();

    }

}

void Parser::stmt4(){

    printf("stmt4\n");
    switch (this->token->token)
    {

        case AND:
            match(AND);
            expr();
            break;
        case ASSIGN:
        case OR:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case POINT:
        case POINTER:
        case LEFTBRACKET:
        case SEMICOLON:
            stmt5();
            break;

        default:
            error();
    }

}

void Parser::stmt5(){

    printf("stmt5\n");
    switch (this->token->token)
    {

        case EQ:
            match(EQ);
            expr();
            break;
        case NEQ:
            match(NEQ);
            expr();
            break;
        case ASSIGN:
        case OR:
        case AND:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case POINT:
        case POINTER:
        case LEFTBRACKET:
        case SEMICOLON:
            stmt6();
            break;

        default:
            error();
    }

}

void Parser::stmt6(){

    printf("stmt6\n");
    switch (this->token->token)
    {

        case GEQ:
            match(GEQ);
            expr();
            break;
        case GREAT:
            match(GREAT);
            expr();
            break;
        case LEQ:
            match(LEQ);
            expr();
            break;
        case LESS:
            match(LESS);
            expr();
            break;
        case EQ:
        case NEQ:
        case ASSIGN:
        case OR:
        case AND:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case POINT:
        case POINTER:
        case LEFTBRACKET:
        case SEMICOLON:
            stmt7();
            break;

        default:
            error();
    }

}

void Parser::stmt7(){

    printf("stmt7\n");
    switch (this->token->token)
    {

        case PIPE:
            match(PIPE);
            expr();
            break;
        case EQ:
        case NEQ:
        case ASSIGN:
        case OR:
        case AND:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case POINT:
        case POINTER:
        case LEFTBRACKET:
        case SEMICOLON:
            stmt8();
            break;

        default:
            error();
    }

}

void Parser::stmt8(){

    printf("stmt8\n");

    switch (this->token->token)
    {

        case MOD:
            match(MOD);
            expr();
            break;
        case DIV:
            match(DIV);
            expr();
            break;
        case NEQ:
        case ASSIGN:
        case OR:
        case AND:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case EQ:
        case AMPERSAND:
        case POINT:
        case POINTER:
        case LEFTBRACKET:
        case SEMICOLON:
            stmt9();
            break;

        default:
            error();
    }

}

void Parser::stmt9(){

    printf("stmt9\n");
    switch (this->token->token)
    {

        case POINT:
            match(POINT);
            match(ID);
            expr();
            break;
        case POINTER:
            match(POINTER);
            match(ID);
            expr();
            break;
        case LEFTBRACKET:
            match(LEFTBRACKET);
            expr();
            match(RIGHTBRACKET);
            expr();
            break;
        case ASSIGN:
        case OR:
        case AND:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case PLUS:
        case MINUS:
        case GEQ:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case SEMICOLON:
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }

}

void Parser::caseblock(){

    printf("caseblock\n");

    match(CASE);

    switch (this->token->token)
    {
        case NUMINT:
            match(NUMINT);
            match(COLON);
            stmtList();
            caseblock2();
            break;
        case NUMFLOAT:
            match(NUMFLOAT);
            match(COLON);
            stmtList();
            caseblock2();
            break;

        default:
            error();
    }

}

void Parser::caseblock2(){

    printf("caseblock2\n");
    switch (this->token->token)
    {
        case NUMINT:
            match(CASE);
            match(NUMINT);
            match(COLON);
            stmtList();
            caseblock2();
            break;
        case NUMFLOAT:
            match(CASE);
            match(NUMFLOAT);
            match(COLON);
            stmtList();
            caseblock2();
            break;
        case RIGHTBRACE:
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }



}

void Parser::exprList(){

    printf("exprList\n");
    switch (this->token->token) {
        case MINUS:
        case NOT:
        case PLUS:
        case LEFTPARENTHESES:
        case ID:
        case NUMINT:
        case NUMFLOAT:
        case LITERAL:
        case AMPERSAND:
        case MULT:
        case TRUE:
        case FALSE:
            exprListTail();
            break;
        case RIGHTPARENTHESES:
            cout<<"epsilon"<<endl; return;
        default:
            error();

    }



}

void Parser::exprListTail(){

    printf("exprListTail\n");
    expr();
    exprListTail2();

}
//minus not plus leftparentheses id num literal ascii ampersand mult true false

void Parser::exprListTail2(){

    printf("exprListTail2\n");
    switch (this->token->token) {
        case COMMA:
            match(COMMA);
            exprListTail();
            break;
        case RIGHTPARENTHESES:
            cout<<"epsilon"<<endl; return;
        default:
            error();

    }

}

void Parser::expr(){

    printf("expr\n");
    expr1();
    expr_l();

}

void Parser::expr_l(){

    printf("expr_l\n");

    switch (this->token->token) {
        case ASSIGN:
            match(ASSIGN);
            expr1();
            expr_l();
            break;
        case AND:
        case SEMICOLON:
        case OR:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case COMMA:
        case RIGHTPARENTHESES:
        case POINTER:
        case POINT:
        case LEFTBRACKET:
        case RIGHTBRACKET:
            cout<<"epsilon"<<endl; return;
        default:
            error();

    }

}

void Parser::expr1(){

    printf("expr1\n");
    expr2();
    expr1_l();

}

void Parser::expr1_l(){

    printf("expr1_l\n");
    switch (this->token->token) {
        case OR:
            match(OR);
            expr2();
            expr1_l();
            break;
        case AND:
        case SEMICOLON:
        case ASSIGN:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case COMMA:
        case RIGHTPARENTHESES:
        case POINTER:
        case POINT:
        case LEFTBRACKET:
        case RIGHTBRACKET:
            cout<<"epsilon"<<endl; return;
        default:
            error();

    }

}

void Parser::expr2(){

    printf("expr2\n");
    expr3();
    expr2_l();

}

void Parser::expr2_l(){

    printf("expr2_l\n");
    switch (this->token->token) {
        case AND:
            match(AND);
            expr3();
            expr2_l();
            break;
        case SEMICOLON:
        case ASSIGN:
        case OR:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case COMMA:
        case RIGHTPARENTHESES:
        case POINTER:
        case POINT:
        case LEFTBRACKET:
        case RIGHTBRACKET:
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }

}

void Parser::expr3(){

    printf("expr3\n");
    expr4();
    expr3_l();

}

void Parser::expr3_l(){

    printf("expr3_l\n");
    switch (this->token->token)
    {
        case EQ:
            match(EQ);
            expr4();
            expr3_l();
            break;
        case NEQ:
            match(NEQ);
            expr4();
            expr3_l();
            break;
        case SEMICOLON:
        case ASSIGN:
        case OR:
        case AND:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case COMMA:
        case RIGHTPARENTHESES:
        case POINTER:
        case POINT:
        case LEFTBRACKET:
        case RIGHTBRACKET:
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }

}

void Parser::expr4(){

    printf("expr4\n");
    expr5();
    expr4_l();

}

void Parser::expr4_l(){

    printf("expr4_l\n");
    switch (this->token->token)
    {
        case LESS:
            match(LESS);
            expr5();
            expr4_l();
            break;
        case LEQ:
            match(LEQ);
            expr5();
            expr4_l();
            break;
        case GREAT:
            match(GREAT);
            expr5();
            expr4_l();
            break;
        case GEQ:
            match(GEQ);
            expr5();
            expr4_l();
            break;
        case SEMICOLON:
        case ASSIGN:
        case OR:
        case AND:
        case EQ:
        case NEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case COMMA:
        case RIGHTPARENTHESES:
        case POINTER:
        case POINT:
        case LEFTBRACKET:
        case RIGHTBRACKET:
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }

}

void Parser::expr5(){

    printf("expr5\n");
    expr6();
    expr5_l();

}

void Parser::expr5_l(){

    printf("expr5_l\n");
    switch (this->token->token)
    {
        case PLUS:
            match(PLUS);
            expr6();
            expr5_l();
            break;
        case MINUS:
            match(MINUS);
            expr6();
            expr5_l();
            break;
        case PIPE:
            match(PIPE);
            expr6();
            expr5_l();
            break;
        case SEMICOLON:
        case ASSIGN:
        case OR:
        case AND:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case COMMA:
        case RIGHTPARENTHESES:
        case POINTER:
        case POINT:
        case LEFTBRACKET:
        case RIGHTBRACKET:
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }

}

void Parser::expr6() {

    printf("expr6\n");
    expr7();
    expr6_l();

}

void Parser::expr6_l() {

    printf("expr6_l\n");
    switch(this->token->token){
        case MULT:
            match(MULT);
            expr7();
            expr6_l();
            break;
        case DIV:
            match(DIV);
            expr7();
            expr6_l();
            break;
        case MOD:
            match(MOD);
            expr7();
            expr6_l();
            break;
        case AMPERSAND:
            match(AMPERSAND);
            expr7();
            expr6_l();
            break;
        case SEMICOLON:
        case ASSIGN:
        case OR:
        case AND:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case COMMA:
        case RIGHTPARENTHESES:
        case POINTER:
        case POINT:
        case LEFTBRACKET:
        case RIGHTBRACKET:
            cout<<"epsilon"<<endl; return;
        default:
            error();

    }

}

void Parser::expr7() {

    printf("expr7\n");
    switch(this->token->token){
        case PLUS:
        case MINUS:
        case NOT:
            unaryOp();
            expr7();
            break;
        case LEFTPARENTHESES:
        case ID:
        case NUMINT:
        case NUMFLOAT:
        case LITERAL:
        case AMPERSAND:
        case MULT:
        case TRUE:
        case FALSE:
            expr8();
    }

    //	leftparentheses id num literal ascii ampersand mult true false
}

void Parser::expr8() {

    printf("expr8\n");
    switch(this->token->token){
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            expr();
            match(RIGHTPARENTHESES);
            primary3();
            break;
        case ID:
        case NUMFLOAT:
        case NUMINT:
        case LITERAL:
        case AMPERSAND:
        case MULT:
        case TRUE:
        case FALSE:
            primary();
    }

}

void Parser::primary() {

    printf("primary\n");

    switch(this->token->token){
        case ID:
            match(ID);
            primary2();
            primary3();
            break;
        case NUMINT:
            match(NUMINT);
            primary3();
            break;
        case NUMFLOAT:
            match(NUMFLOAT);
            primary3();
            break;
        case LITERAL:
            match(LITERAL);
            primary3();
            break;
        case AMPERSAND:
            match(AMPERSAND);
            expr();
            primary3();
            break;
        case MULT:
            match(MULT);
            expr();
            primary3();
            break;
        case TRUE:
            match(TRUE);
            primary3();
            break;
        case FALSE:
            match(FALSE);
            primary3();
            break;
    }
}

void Parser::primary2() {

    printf("primary2\n");
    switch(this->token->token){
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            exprList();
            match(RIGHTPARENTHESES);
            break;
        case SEMICOLON:
        case ASSIGN:
        case OR:
        case AND:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case COMMA:
        case RIGHTPARENTHESES:
        case POINTER:
        case POINT:
        case LEFTBRACKET:
        case RIGHTBRACKET:
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }

}

void Parser::primary3() {

    printf("primary3\n");
    switch(this->token->token){
        case POINTER:
            match(POINTER);
            match(ID);
            primary3();
            break;
        case POINT:
            match(POINT);
            match(ID);
            primary3();
            break;
        case LEFTBRACKET:
            match(LEFTBRACKET);
            expr();
            match(RIGHTBRACKET);
            primary3();
            break;
        case SEMICOLON:
        case ASSIGN:
        case OR:
        case AND:
        case EQ:
        case NEQ:
        case LESS:
        case LEQ:
        case GREAT:
        case GEQ:
        case PLUS:
        case MINUS:
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case COMMA:
        case RIGHTPARENTHESES:
        case RIGHTBRACKET:
            cout<<"epsilon"<<endl; return;
        default:
            error();
    }

}

void Parser::unaryOp() {

    printf("unaryOp\n");
    switch(this->token->token){
        case MINUS:
            match(MINUS);
            break;
        case NOT:
            match(NOT);
            break;
        case PLUS:
            match(PLUS);
            break;
    }
}

void Parser::pointer() {

    printf("pointer\n");
    switch (this->token->token) {
        case MULT:
            match(MULT);
            break;
        case ID:
            cout<<"epsilon"<<endl; return;
        default: error();
    }
}

void Parser::type() {

    printf("type\n");
    switch(this->token->token){
        case LONG:
            match(LONG);
            break;
        case INT:
            match(INT);
            break;
        case FLOAT:
            match(FLOAT);
            break;
        case BOOL:
            match(BOOL);
            break;
        case ID:
            match(ID);
            break;
        case CHAR:
            match(CHAR);
            break;
        case DOUBLE:
            match(DOUBLE);
            break;

    }
}
void Parser::typeCompl() {

    printf("typeCompl\n");
    switch(this->token->token){
        case LONG:
            match(LONG);
            break;
        case INT:
            match(INT);
            break;
        case FLOAT:
            match(FLOAT);
            break;
        case BOOL:
            match(BOOL);
            break;
        case CHAR:
            match(CHAR);
            break;
        case DOUBLE:
            match(DOUBLE);
            break;

    }
}

string Parser::translate(int token) {
    switch (token) {
        case ID: return "id";
        case SEMICOLON: return ";";
        case COLON: return ".";
        case MOD: return "%";
        case PLUS: return "+";
        case MULT: return "*";
        case CMMEOF: return "eof";
        case NEQ: return "!=";
        case NOT: return "!";
        case GEQ: return ">=";
        case LESS: return "<";
        case GREAT: return ">";
        case LEQ: return "<=";
        case ASSIGN: return "=";
        case EQ: return "==";
        case DIV: return "/";
        case RIGHTPARENTHESES: return ")";
        case LEFTPARENTHESES: return "(";
        case RIGHTBRACE: return "}";
        case LEFTBRACE: return "{";
        case RIGHTBRACKET: return "}";
        case LEFTBRACKET: return "{";
        case POINT: return ".";
        case POINTER: return "->";
        case MINUS: return "-";
        case AND: return "&&";
        case OR: return "||";
        case PIPE: return "|";
        case LITERAL: return "literal";
        case NUMFLOAT: return "numfloat";
        case NUMINT: return "numint";
        case COMMA: return ",";
        case TYPEDEF: return "typedef";
        case STRUCT: return "struct";
        case LONG: return "long";
        case INT: return "int";
        case FLOAT: return "float";
        case DOUBLE: return "double";
        case BOOL: return "bool";
        case CHAR: return "char";
        case IF: return "if";
        case WHILE: return "while";
        case SWITCH: return "switch";
        case BREAK: return "break";
        case PRINT: return "print";
        case READLN: return "readln";
        case RETURN: return "return";
        case THROW: return "throw";
        case TRY: return "try";
        case CATCH: return "cath";
        case CASE: return "case";
        case FOR: return "for";
        case ELSE: return "else";
        default: return "whrong";

    }
}


void c_parse() {
    Parser::parse();
}