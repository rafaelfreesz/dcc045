#include "Parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}

void Parser::match(int token) {
    if(token != FIRSTTOKEN) {
        if (token == this->token->token) {
            this->token = nextToken();
        } else {
            printf("Unexpected token %d \n", token);
            // exit(0);
        }
    }else{
        this->token = nextToken();
    }
}

void Parser::parse() {

    Parser* parser = new Parser();
    parser->match(FIRSTTOKEN);
    parser->program();


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

        default: printf("Error!");

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

        case LEFTBRACKET:
            varDeclSulfix();
            program();

    }

}

void Parser::program2(){

    printf("program2\n");
    if(this->token->token == CMMEOF){
        return;
    }else{

        program();
    }

}

void Parser::varDeclSulfix(){

    printf("varDeclSulfix\n");
    array();
    idList2();
    match(SEMICOLON);

}

void Parser::varDecl(){

    printf("varDecl\n");
    type();
    pointer();

    match(ID);

    array();
    idList2();

    match(SEMICOLON);
    varDecl2();

}

void Parser::varDecl2(){

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
        case IF :
        case WHILE :
        case SWITCH :
        case BREAK:
        case PRINT:
        case READLN:
        case RETURN:
        case THROW:
        case LEFTBRACE:
        case TRY:
            ///CONFLITO EPSILON IGNORADO PARA CASE ID
        case MINUS:
        case NOT:
        case PLUS:
        case LEFTPARENTHESES:
        case NUMFLOAT:
        case NUMINT:
        case LITERAL:
        case AMPERSAND:
        case MULT:
        case TRUE:
        case FALSE:
        case RIGHTBRACE:
            return;
        default:
            printf("Error\n");


    }


}

void Parser::functionDecl(){

    printf("functionDecl\n");
    match(LEFTPARENTHESES);
    formalList();
    match(RIGHTPARENTHESES);
    match(LEFTBRACE);
    varDecl2();
    stmtList2();

}

void Parser::idList(){

    printf("idList\n");
    pointer();
    match(ID);
    array();
    idList2();

}

void Parser::idList2(){

    switch (this->token->token)
    {
        case COMMA:
            printf("idList2\n");
            pointer();
            match(ID);
            array();
            idList2();
            break;

        case SEMICOLON:
            return;

        default:
            break;
    }



}

void Parser::typedecl() {

    printf("typedecl\n");
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
            return;
        default:
            printf("Error!\n");
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
            break;

        default:
            break;
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
            return;

        default:
            break;
    }


}

void Parser::stmtList(){

    printf("stmtList\n");
    stmt();
    stmtList2();

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
            return;

        default:
            break;
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
            match(SEMICOLON);
            break;

        case READLN:
            match(PRINT);
            match(LEFTPARENTHESES);
            exprList();
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
            stmtPrim();
            stmt2();
            match(SEMICOLON);
            break;

        default:
            break;
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
            break;
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
        case MULT:
            match(MULT);
            expr();
            stmt2();
            break;

        default:
            break;
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
            break;
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
            stmt2();
            break;

        default:
            break;
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
            stmt3();
            break;

        default:
            break;
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
            stmt4();
            break;

        default:
            break;
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
            stmt5();
            break;

        default:
            break;
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
            stmt6();
            break;

        default:
            break;
    }

}

void Parser::stmt6(){

    printf("stmt6\n");
    switch (this->token->token)
    {


        case LESS:
            match(LESS);
            expr();
            break;
        case LEQ:
            match(LEQ);
            expr();
            break;
        case GREAT:
            match(GREAT);
            expr();
            break;
        case GEQ:
            match(GEQ);
            expr();
            break;
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
            stmt7();
            break;

        default:
            break;
    }

}

void Parser::stmt7(){

    printf("stmt7\n");
    switch (this->token->token)
    {

        case PLUS:
            match(PLUS);
            expr();
            break;
        case MINUS:
            match(MINUS);
            expr();
            break;
        case PIPE:
            match(PIPE);
            expr();
            break;
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case POINT:
        case POINTER:
        case LEFTBRACKET:
            stmt8();
            break;

        default:
            break;
    }

}

void Parser::stmt8(){

    printf("stmt8\n");

    switch (this->token->token)
    {

        case MULT:
            match(MULT);
            expr();
            break;
        case DIV:
            match(DIV);
            expr();
            break;
        case MOD:
            match(MOD);
            expr();
            break;
        case AMPERSAND:
            match(AMPERSAND);
            expr();
            break;
        case POINT:
        case POINTER:
        case LEFTBRACKET:
            stmt9();
            break;

        default:
            break;
    }

}

void Parser::stmt9(){

    printf("stmt9");
    switch (this->token->token)
    {

        case POINT:
            match(POINT);
            expr();
            break;
        case POINTER:
            match(POINTER);
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
        case PIPE:
        case MULT:
        case DIV:
        case MOD:
        case AMPERSAND:
        case SEMICOLON:
            return;
        default:
            printf("Error\n");
    }

} //	assign or and eq neq less leq great geq plus minus pipe mult div mod ampersand point pointerprop leftbracket semicolon

void Parser::caseblock(){

    printf("caseblock");
    match(CASE);

    switch (this->token->token)
    {
        case NUMINT:
            match(NUMINT);
            break;
        case NUMFLOAT:
            match(NUMFLOAT);
            break;

        default:
            break;
    }

    match(COLON);
    stmtList();
    caseblock2();

}

void Parser::caseblock2(){

    printf("caseblock2");
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
            return;
        default:
            printf("Error!");
    }



}

void Parser::exprList(){

    printf("exprList");
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
        case RIGHTPARENTHESES:
            return;
        default:
            printf("Error!\n");

    }



}

void Parser::exprListTail(){

    printf("exprListTail");
    expr();
    exprListTail2();

}
//minus not plus leftparentheses id num literal ascii ampersand mult true false

void Parser::exprListTail2(){

    printf("exprListTail2");
    switch (this->token->token) {
        case COMMA:
            match(COMMA);
            exprListTail();
        case RIGHTPARENTHESES:
            return;
        default:
            printf("Error!\n");

    }

}

void Parser::expr(){

    printf("expr");
    expr1();
    expr_l();

}

void Parser::expr_l(){

    printf("expr_l");
    match(ASSIGN);
    expr1();
    expr_l();

}

void Parser::expr1(){

    printf("expr1");
    expr2();
    expr1_l();

}

void Parser::expr1_l(){

    printf("expr1_l");
    switch (this->token->token) {
        case OR:
            match(OR);
            expr2();
            expr1_l();
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
            return;
        default:
            printf("Error!\n");

    }

}

void Parser::expr2(){

    printf("expr2");
    expr3();
    expr2_l();

}

void Parser::expr2_l(){

    printf("expr2_l");
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
            return;
        default:
            printf("Error\n");
    }

}

void Parser::expr3(){

    printf("expr3");
    expr4();
    expr3_l();

}

void Parser::expr3_l(){

    printf("expr3_l");
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
            return;
        default:
            printf("Error\n");
    }

}

void Parser::expr4(){

    printf("expr4");
    expr5();
    expr4_l();

}

void Parser::expr4_l(){

    printf("expr4_l");
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
            return;
        default:
            printf("Error\n");
    }

}

void Parser::expr5(){

    printf("expr5");
    expr6();
    expr5_l();

}

void Parser::expr5_l(){

    printf("expr5_l");
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
            return;
        default:
            printf("Error\n");
    }

}

void Parser::expr6() {

    printf("expr6");
    switch(this->token->token){
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
            expr7();
            expr6_l();
    }

    //		minus not plus leftparentheses id num literal ascii ampersand mult true false
}

void Parser::expr6_l() {

    printf("expr6_l");
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
            return;
        default:
            printf("Error\n");

    }

}

void Parser::expr7() {

    printf("expr7");
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
            return;
        default:
            printf("Error\n");
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
            return;
        default:
            printf("Error\n");
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
            return;
        default: printf("Error\n");
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



void c_parse() {
    Parser::parse();
}