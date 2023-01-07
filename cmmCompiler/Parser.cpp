#include "Parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}
void Parser::matchOrSync(int token, int *nonTeminal) {
    if (token == this->token->token) {
        fprintf(stdout,"MATCH:");
        printToken(this->token);
        this->token = nextToken();
    } else {
        sync(nonTeminal);
    }
}
void Parser::match(int token) {

    if(token != FIRSTTOKEN) {
        if (token == this->token->token) {
            fprintf(stdout,"MATCH:");
            printToken(this->token);
            this->token = nextToken();
        } else {
            fprintf(stdout,"Unexpected token %s, expected: %s", translate(this->token->token), translate(token));
            printToken(this->token);
        }
    }else{
        this->token = nextToken();
    }
}
void Parser::sync(int *nonTerminal) {
    fprintf(stdout,"Syntactic Error: Given: %s", translate(this->token->token));
    while(this->token->token!=CMMEOF) {
        this->token=nextToken();
        for (int i = 1; i < nonTerminal[0]; i++) {
            if(this->token->token==nonTerminal[i]){
                fprintf(stdout,", expected: %s\n", translate(this->token->token));
                return;
            }
        }
    }
    fprintf(stdout,", expected: %s\n", translate(this->token->token));
}
char* strs(){
    return "123";
}
void Parser::parse() {

    Parser* parser = new Parser();
    parser->match(FIRSTTOKEN);
    parser->program();


    cout<<"SUCCESS!"<<endl;


}

//---------Parse Functions------------//

int F_program[]={1,CMMEOF};

void Parser::program() {

    fprintf(stdout,"Program\n");
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

        default: sync(F_program);

    }

}

int F_declPrefix[]={5,LEFTPARENTHESES,SEMICOLON,LEFTBRACKET,COMMA, CMMEOF};

void Parser::declprefix() {

    fprintf(stdout,"DeclPrefix\n");
    switch (this->token->token) {
        case INT:
        case LONG:
        case FLOAT:
        case DOUBLE:
        case CHAR:
        case BOOL:
        case ID:
            type();
            pointer();
            matchOrSync(ID,F_declPrefix);
            break;
        default:sync(F_declPrefix);



    }

}

int F_declSulfix[]={1,CMMEOF};

void Parser::declsulfix() {

    fprintf(stdout,"DeclSulfix\n");
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
        default:
            sync(F_declSulfix);

    }
}

int F_program2[]={1,CMMEOF};

void Parser::program2(){

    fprintf(stdout,"Program2\n");

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
            //epsilon
            return;
        default:
            sync(F_program2);
    }
}

int F_valDeclSulfix[]={9,TYPEDEF,LONG,INT,FLOAT,BOOL,ID,CHAR,DOUBLE,CMMEOF};


void Parser::varDeclSulfix(){

    fprintf(stdout,"VarDeclSulfix\n");
    switch (this->token->token) {
        case LEFTBRACKET:
        case COMMA:
        case SEMICOLON:
            array();
            idList2();
            matchOrSync(SEMICOLON,F_valDeclSulfix);
            break;
        default:sync(F_declSulfix);
    }
}

int F_varDecl2[]={2,RIGHTBRACE,CMMEOF};


void Parser::varDecl2(){

    fprintf(stdout,"VarDecl2\n");
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
            matchOrSync(ID,F_varDecl2);
            array();
            idList2();
            matchOrSync(SEMICOLON,F_varDecl2);
            varDecl2();
            break;
        case RIGHTBRACE:
            //epsilon
            return;
        default:
            sync(F_varDecl2);

    }
}

int F_functionDecl[]={9,TYPEDEF,LONG,INT,FLOAT,BOOL,ID,CHAR,DOUBLE,CMMEOF};

void Parser::functionDecl(){

    fprintf(stdout,"FunctionDecl\n");
    switch (this->token->token) {
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            formalList();
            matchOrSync(RIGHTPARENTHESES,F_functionDecl);
            matchOrSync(LEFTBRACE,F_functionDecl);
            functionBody();
            matchOrSync(RIGHTBRACE,F_functionDecl);
            break;
        default: sync(F_functionDecl);
        
    }

}

int F_functionBody[]={2,RIGHTBRACE,CMMEOF};


void Parser::functionBody() {

    fprintf(stdout,"FunctionBody\n");
    switch (this->token->token) {
        case LONG:
        case INT:
        case FLOAT:
        case BOOL:
        case CHAR:
        case DOUBLE:
            typeCompl();
            pointer();
            matchOrSync(ID,F_functionBody);
            array();
            idList2();
            matchOrSync(SEMICOLON,F_functionBody);
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
            //epsilon
            return;
        default:
            sync(F_functionBody);



    }
}

int F_functionBody2[]={2,RIGHTBRACE,CMMEOF};

void Parser::functionBody2() {

    fprintf(stdout,"FunctionBody2\n");
    switch (this->token->token) {
        case ID:
            match(ID);
            array();
            idList2();
            matchOrSync(SEMICOLON,F_functionBody2);
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
            matchOrSync(SEMICOLON,F_functionBody2);
            stmtList2();
            break;
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            exprList();
            matchOrSync(RIGHTPARENTHESES,F_functionBody2);
            matchOrSync(SEMICOLON,F_functionBody2);
            stmtList2();
            break;
        case MULT:
            match(MULT);
            expr();
            functionBody3();
            break;
        default:
            sync(F_functionBody2);


    }
}

int F_binOp[]={12,MINUS,NOT,PLUS,LEFTPARENTHESES,ID,NUMFLOAT,NUMINT,LITERAL,AMPERSAND,MULT,TRUE,FALSE,CMMEOF};

void Parser::binOp() {

    fprintf(stdout,"BinOp\n");
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
        default:
            sync(F_binOp);
        
    }
}

int F_functionBody3[]={2,RIGHTBRACE,CMMEOF};

void Parser::functionBody3() {
    fprintf(stdout,"FunctionBody3\n");
    switch (this->token->token) {
        case COMMA:
            match(COMMA);
            idList2();
            matchOrSync(SEMICOLON,F_functionBody3);
            functionBody();
            break;
        case SEMICOLON:
            match(SEMICOLON);
            functionBody();
            break;
        default:
            sync(F_functionBody3);
    }

}

int F_idList[]={2,SEMICOLON, CMMEOF};

void Parser::idList(){

    fprintf(stdout,"IdList\n");
    switch (this->token->token) {
        case ID:
        case MULT:
            pointer();
            matchOrSync(ID,F_idList);
            array();
            idList2();
            break;
        default:
            sync(F_idList);
    }

}

int F_idList2[]={2,SEMICOLON, CMMEOF};

void Parser::idList2(){

    fprintf(stdout,"IdList2\n");
    switch (this->token->token)
    {
        case COMMA:
            match(COMMA);
            pointer();
            matchOrSync(ID,F_idList2);
            array();
            idList2();
            break;

        case SEMICOLON:
            //epsilon
            return;

        default:
            sync(F_idList2);
    }



}

int F_typeDecl[]={9,TYPEDEF,LONG,INT,FLOAT,BOOL,ID,CHAR,DOUBLE,CMMEOF};

void Parser::typedecl() {

    fprintf(stdout,"TypeDecl\n");
    switch (this->token->token) {
        case TYPEDEF:
            match(TYPEDEF);
            matchOrSync(STRUCT,F_typeDecl);
            matchOrSync(LEFTBRACE,F_typeDecl);
            type();
            idList();
            matchOrSync(SEMICOLON,F_typeDecl);
            varDecl2();
            matchOrSync(RIGHTBRACE,F_typeDecl);
            matchOrSync(ID,F_typeDecl);
            matchOrSync(SEMICOLON,F_typeDecl);
            break;
        default:
            sync(F_typeDecl);

    }

}

int F_array[]={4,RIGHTPARENTHESES,SEMICOLON,COMMA,CMMEOF};

void Parser::array() {

    fprintf(stdout,"Array\n");
    switch (this->token->token) {
        case LEFTBRACKET:
            match(LEFTBRACKET);
            matchOrSync(NUMINT,F_array);
            matchOrSync(RIGHTBRACKET,F_array);
            array();
            break;

        case RIGHTPARENTHESES:
        case SEMICOLON:
        case COMMA:
            //epsilon
            return;
        default:
            sync(F_array);
    }

}

int F_formalList[]={2,RIGHTPARENTHESES,CMMEOF};

void Parser::formalList(){

    fprintf(stdout,"FormalList\n");
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
            matchOrSync(ID,F_formalList);
            array();
            formalRest();
            break;

        case RIGHTPARENTHESES:
            //epsilon
            return;

        default:
            sync(F_formalList);
    }


}

int F_formalRest[]={2,RIGHTPARENTHESES,CMMEOF};

void Parser::formalRest(){

    fprintf(stdout,"FormalRest\n");
    switch (this->token->token)
    {
        case COMMA:
            match(COMMA);
            type();
            pointer();
            matchOrSync(ID,F_formalRest);
            array();
            formalRest();
            break;

        case RIGHTPARENTHESES:
            //epsilon
            return;

        default:
            sync(F_formalRest);
    }


}

int F_stmtList[]={3, CASE,RIGHTBRACE,CMMEOF};

void Parser::stmtList(){

    fprintf(stdout,"StmtList\n");
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
        default:sync(F_stmtList);

        
    }


}

int F_stmtList2[]={3,CASE,RIGHTBRACE,CMMEOF};

void Parser::stmtList2(){

    fprintf(stdout,"StmtList2\n");
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
            //epsilon
            return;

        default:
            sync(F_stmtList2);
    }

}

int F_stmt[]={27,CASE, ELSE, CATCH, IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LEFTBRACE, TRY, ID, MINUS, NOT, PLUS, LEFTPARENTHESES, NUMFLOAT, NUMINT, LITERAL, AMPERSAND, MULT, TRUE, FALSE, RIGHTBRACE, CMMEOF};

void Parser::stmt(){

    fprintf(stdout,"Stmt\n");
    switch (this->token->token)
    {
        case IF:
            match(IF);
            matchOrSync(LEFTPARENTHESES,F_stmt);
            expr();
            matchOrSync(RIGHTPARENTHESES,F_stmt);
            stmt();
            matchOrSync(ELSE,F_stmt);
            stmt();
            break;

        case WHILE:
            match(WHILE);
            matchOrSync(LEFTPARENTHESES,F_stmt);
            expr();
            matchOrSync(RIGHTPARENTHESES,F_stmt);
            stmt();
            break;

        case SWITCH:
            match(SWITCH);
            matchOrSync(LEFTPARENTHESES,F_stmt);
            expr();
            matchOrSync(RIGHTPARENTHESES,F_stmt);
            matchOrSync(LEFTBRACE,F_stmt);
            caseblock();
            matchOrSync(RIGHTBRACE,F_stmt);
            break;

        case BREAK:
            match(BREAK);
            matchOrSync(SEMICOLON,F_stmt);
            break;

        case PRINT:
            match(PRINT);
            matchOrSync(LEFTPARENTHESES,F_stmt);
            exprList();
            matchOrSync(RIGHTPARENTHESES,F_stmt);
            matchOrSync(SEMICOLON,F_stmt);
            break;

        case READLN:
            match(READLN);
            matchOrSync(LEFTPARENTHESES,F_stmt);
            expr();
            matchOrSync(RIGHTPARENTHESES,F_stmt);
            matchOrSync(SEMICOLON,F_stmt);
            break;

        case RETURN:
            match(RETURN);
            expr();
            matchOrSync(SEMICOLON,F_stmt);
            break;

        case THROW:
            match(THROW);
            matchOrSync(SEMICOLON,F_stmt);
            break;

        case LEFTBRACE:
            match(LEFTBRACE);
            stmtList();
            matchOrSync(RIGHTBRACE,F_stmt);
            break;

        case TRY:
            match(TRY);
            stmt();
            matchOrSync(CATCH,F_stmt);
            matchOrSync(LEFTPARENTHESES,F_stmt);
            matchOrSync(RIGHTPARENTHESES,F_stmt);
            stmt();
            break;

        case ID:
            match(ID);
            stmt1();
            matchOrSync(SEMICOLON,F_stmt);
            break;

        case MINUS:
        case NOT:
        case PLUS:
            unaryOp();
            stmtPrim3();
            matchOrSync(SEMICOLON,F_stmt);
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
            matchOrSync(SEMICOLON,F_stmt);
            break;

        default:
            sync(F_stmt);
    }

}

int F_stmtCompl[]={24,IF, WHILE, SWITCH, BREAK, PRINT, READLN, RETURN, THROW, LEFTBRACE, TRY, ID, MINUS, NOT, PLUS, LEFTPARENTHESES, NUMINT, NUMFLOAT, LITERAL, AMPERSAND, MULT, TRUE, FALSE, RIGHTBRACE, CMMEOF};

void Parser::stmtCompl(){

    fprintf(stdout,"StmtCompl\n");
    switch (this->token->token)
    {
        case IF:
            match(IF);
            matchOrSync(LEFTPARENTHESES,F_stmtCompl);
            expr();
            matchOrSync(RIGHTPARENTHESES,F_stmtCompl);
            stmt();
            matchOrSync(ELSE,F_stmtCompl);
            stmt();
            break;

        case WHILE:
            match(WHILE);
            matchOrSync(LEFTPARENTHESES,F_stmtCompl);
            expr();
            matchOrSync(RIGHTPARENTHESES,F_stmtCompl);
            stmt();
            break;

        case SWITCH:
            match(SWITCH);
            matchOrSync(LEFTPARENTHESES,F_stmtCompl);
            expr();
            matchOrSync(RIGHTPARENTHESES,F_stmtCompl);
            matchOrSync(LEFTBRACE,F_stmtCompl);
            caseblock();

            matchOrSync(RIGHTBRACE,F_stmtCompl);
            break;

        case BREAK:
            match(BREAK);
            matchOrSync(SEMICOLON,F_stmtCompl);
            break;

        case PRINT:
            match(PRINT);
            matchOrSync(LEFTPARENTHESES,F_stmtCompl);
            exprList();
            matchOrSync(RIGHTPARENTHESES,F_stmtCompl);
            matchOrSync(SEMICOLON,F_stmtCompl);
            break;

        case READLN:
            match(READLN);
            matchOrSync(LEFTPARENTHESES,F_stmtCompl);
            expr();
            matchOrSync(RIGHTPARENTHESES,F_stmtCompl);
            matchOrSync(SEMICOLON,F_stmtCompl);
            break;

        case RETURN:
            match(RETURN);
            expr();
            matchOrSync(SEMICOLON,F_stmtCompl);
            break;

        case THROW:
            match(THROW);
            matchOrSync(SEMICOLON,F_stmtCompl);
            break;

        case LEFTBRACE:
            match(LEFTBRACE);
            stmtList();
            matchOrSync(RIGHTBRACE,F_stmtCompl);
            break;

        case TRY:
            match(TRY);
            stmt();
            matchOrSync(CATCH,F_stmtCompl);
            matchOrSync(LEFTPARENTHESES,F_stmtCompl);
            matchOrSync(RIGHTPARENTHESES,F_stmtCompl);
            stmt();
            break;

        case MINUS:
        case NOT:
        case PLUS:
            unaryOp();
            stmtPrim3();
            matchOrSync(SEMICOLON,F_stmtCompl);
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
            matchOrSync(SEMICOLON,F_stmtCompl);
            break;

        default:
            sync(F_stmtCompl);
    }

}

int F_stmtPrim[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmtPrim(){

    fprintf(stdout,"StmtPrim\n");
    switch (this->token->token)
    {
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            expr();
            matchOrSync(RIGHTPARENTHESES,F_stmtPrim);
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
            sync(F_stmtPrim);
    }

}

int F_stmtPrim2[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmtPrim2(){

    fprintf(stdout,"StmtPrim2\n");
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
            sync(F_stmtPrim2);
    }

}

int F_stmtPrim3[]={2,SEMICOLON,CMMEOF};

void Parser::stmtPrim3(){

    fprintf(stdout,"StmtPrim3\n");
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
            sync(F_stmtPrim3);
    }

}

int F_stmt1[]={2,SEMICOLON,CMMEOF};

void Parser::stmt1(){

    fprintf(stdout,"Stmt1\n");
    switch (this->token->token)
    {
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            exprList();
            matchOrSync(RIGHTPARENTHESES, F_stmt1);
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
            sync(F_stmt1);
    }


}

int F_stmt2[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmt2(){

    fprintf(stdout,"Stmt2\n");
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
            sync(F_stmt2);
    }

}

int F_stmt3[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmt3(){

    fprintf(stdout,"Stmt3\n");
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
            sync(F_stmt3);

    }

}

int F_stmt4[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmt4(){

    fprintf(stdout,"Stmt4\n");
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
            sync(F_stmt4);
    }

}

int F_stmt5[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmt5(){

    fprintf(stdout,"Stmt5\n");
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
            sync(F_stmt5);
    }

}

int F_stmt6[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmt6(){

    fprintf(stdout,"Stmt6\n");
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
            sync(F_stmt6);
    }

}

int F_stmt7[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmt7(){

    fprintf(stdout,"Stmt7\n");
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
            sync(F_stmt7);
    }

}

int F_stmt8[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmt8(){

    fprintf(stdout,"Stmt8\n");

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
            sync(F_stmt8);
    }

}

int F_stmt9[]={21, ASSIGN, OR, AND, EQ, NEQ, LESS, LEQ, GREAT, GEQ, PLUS, MINUS, PIPE, MULT, DIV, MOD, AMPERSAND, POINT, POINTER, LEFTBRACKET, SEMICOLON,CMMEOF};

void Parser::stmt9(){

    fprintf(stdout,"Stmt9\n");
    switch (this->token->token)
    {

        case POINT:
            match(POINT);
            matchOrSync(ID, F_stmt9);
            expr();
            break;
        case POINTER:
            match(POINTER);
            matchOrSync(ID,F_stmt9);
            expr();
            break;
        case LEFTBRACKET:
            match(LEFTBRACKET);
            expr();
            matchOrSync(RIGHTBRACKET,F_stmt9);
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
            //epsilon
            return;
        default:
            sync(F_stmt9);
    }

}

int F_caseBlock[]={2,RIGHTBRACE,CMMEOF};

void Parser::caseblock(){

    fprintf(stdout,"Saseblock\n");

    switch (this->token->token) {
        case CASE:
            match(CASE);
            switch (this->token->token)
            {
                case NUMINT:
                    match(NUMINT);
                    matchOrSync(COLON,F_caseBlock);
                    stmtList();
                    caseblock2();
                    break;
                case NUMFLOAT:
                    match(NUMFLOAT);
                    matchOrSync(COLON,F_caseBlock);
                    stmtList();
                    caseblock2();
                    break;
                default:
                    sync(F_caseBlock); //TODO ver oq fazer aqui);
            }
            break;
        default:
            sync(F_caseBlock);

    }

}

int F_caseBlock2[]={2,RIGHTBRACE,CMMEOF};

void Parser::caseblock2(){

    fprintf(stdout,"Caseblock2\n");

    switch (this->token->token) {
        case CASE:
            match(CASE);
            switch (this->token->token)
            {
                case NUMINT:
                    match(NUMINT);
                    matchOrSync(COLON,F_caseBlock2);
                    stmtList();
                    caseblock2();
                    break;
                case NUMFLOAT:
                    match(NUMFLOAT);
                    matchOrSync(COLON,F_caseBlock2);
                    stmtList();
                    caseblock2();
                    break;
                default:
                    sync(F_caseBlock2); //TODO ver oq fazer aqui
            }
            break;
        case RIGHTBRACE:
            //epsilon
            return;
        default:
            sync(F_caseBlock2);

    }





}

int F_exprList[]={2,RIGHTPARENTHESES,CMMEOF};

void Parser::exprList(){

    fprintf(stdout,"ExprList\n");
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
            //epsilon
            return;
        default:
            sync(F_exprList);

    }



}

int F_exprListTail[]={2,RIGHTPARENTHESES,CMMEOF};

void Parser::exprListTail() {


    fprintf(stdout,"ExprListTail\n");
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
            expr();
            exprListTail2();
            break;
        default:
            sync(F_exprListTail);


    }
}

int F_exprListTail2[]={2,RIGHTPARENTHESES,CMMEOF};

void Parser::exprListTail2(){

    fprintf(stdout,"ExprListTail2\n");
    switch (this->token->token) {
        case COMMA:
            match(COMMA);
            exprListTail();
            break;
        case RIGHTPARENTHESES:
            //epsilon
            return;
        default:
            sync(F_exprListTail2);

    }

}

int F_expr[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr(){ //TODO FAZER SWITCH

    fprintf(stdout,"Expr\n");

    switch (this->token->token) {
        case ID:
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
            expr1();
            expr_l();
            break;
        default:
            sync(F_expr);

    }


}

int F_expr_l[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr_l(){

    fprintf(stdout,"Expr_l\n");

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
            //epsilon
            return;
        default:
            sync(F_expr_l);

    }

}

int F_expr1[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr1(){

    fprintf(stdout,"Expr1\n");
    switch (this->token->token) {
        case ID:
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
            expr2();
            expr1_l();
            break;
        default:
            sync(F_expr1);

    }


}

int F_expr1_l[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr1_l(){

    fprintf(stdout,"Expr1_l\n");
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
            //epsilon
            return;
        default:
            sync(F_expr1_l);

    }

}

int F_expr2[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr2(){

    fprintf(stdout,"Expr2\n");
    switch (this->token->token) {
        case ID:
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
            expr3();
            expr2_l();
            break;
        default:
            sync(F_expr2);

    }

}

int F_expr2_l[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr2_l(){

    fprintf(stdout,"Expr2_l\n");
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
            //epsilon
            return;
        default:
            sync(F_expr2_l);
    }

}

int F_expr3[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr3(){

    fprintf(stdout,"Expr3\n");
    switch (this->token->token) {
        case ID:
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
            expr4();
            expr3_l();
            break;
        default:
            sync(F_expr3);

    }


}

int F_expr3_l[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr3_l(){

    fprintf(stdout,"Expr3_l\n");
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
            //epsilon
            return;
        default:
            sync(F_expr3_l);
    }

}

int F_expr4[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr4(){

    fprintf(stdout,"Expr4\n");
    switch (this->token->token) {
        case ID:
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
            expr5();
            expr4_l();
            break;
        default:
            sync(F_expr4);

    }


}

int F_expr4_l[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr4_l(){

    fprintf(stdout,"Expr4_l\n");
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
            //epsilon
            return;
        default:
            sync(F_expr4_l);
    }

}

int F_expr5[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr5(){

    fprintf(stdout,"Expr5\n");
    switch (this->token->token) {
        case ID:
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
            expr6();
            expr5_l();
            break;
        default:
            sync(F_expr5);

    }


}

int F_expr5_l[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr5_l(){

    fprintf(stdout,"Expr5_l\n");
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
            //epsilon
            return;
        default:
            sync(F_expr5_l);
    }

}

int F_expr6[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr6() {

    fprintf(stdout,"Expr6\n");
    switch (this->token->token) {
        case ID:
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
            expr7();
            expr6_l();
            break;
        default:
            sync(F_expr6);

    }


}

int F_expr6_l[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr6_l() {

    fprintf(stdout,"Expr6_l\n");
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
            //epsilon
            return;
        default:
            sync(F_expr6_l);

    }

}

int F_expr7[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr7() {

    fprintf(stdout,"Expr7\n");
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
            break;
        default:
            sync(F_expr7);
    }

    //	leftparentheses id num literal ascii ampersand mult true false
}

int F_expr8[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::expr8() {

    fprintf(stdout,"Expr8\n");
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
            break;
        default:
            sync(F_expr8);
    }

}

int F_primary[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::primary() {

    fprintf(stdout,"Primary\n");

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
        default:
            sync(F_primary);
    }
}
int F_primary2[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::primary2() {

    fprintf(stdout,"Primary2\n");
    switch(this->token->token){
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            exprList();
            matchOrSync(RIGHTPARENTHESES,F_primary2);
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
            //epsilon
            return;
        default:
            sync(F_primary2);
    }

}

int F_primary3[]={24,SEMICOLON,ASSIGN,OR,AND,EQ,NEQ,LESS,LEQ,GREAT,GEQ,PLUS,MINUS,PIPE,MULT,DIV,MOD,AMPERSAND,COMMA,POINTER,POINT,LEFTBRACKET,RIGHTBRACKET,RIGHTPARENTHESES,CMMEOF};

void Parser::primary3() {

    fprintf(stdout,"Primary3\n");
    switch(this->token->token){
        case POINTER:
            match(POINTER);
            matchOrSync(ID,F_primary3);
            primary3();
            break;
        case POINT:
            match(POINT);
            matchOrSync(ID,F_primary3);
            primary3();
            break;
        case LEFTBRACKET:
            match(LEFTBRACKET);
            expr();
            matchOrSync(RIGHTBRACKET,F_primary3);
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
            //epsilon
            return;
        default:
            sync(F_primary3);
    }

}

int F_unaryOp[]={13,MINUS,NOT,PLUS,LEFTPARENTHESES,ID,NUMINT,NUMFLOAT,LITERAL,AMPERSAND,MULT,TRUE,FALSE,CMMEOF};

void Parser::unaryOp() {

    fprintf(stdout,"UnaryOp\n");
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
        default:
            sync(F_unaryOp);
    }
}

int F_pointer[]={2,ID,CMMEOF};

void Parser::pointer() {

    fprintf(stdout,"Pointer\n");
    switch (this->token->token) {
        case MULT:
            match(MULT);
            break;
        case ID:
            //epsilon
            return;
        default: sync(F_pointer);
    }
}

int F_type[]={3,POINTER,ID,CMMEOF};

void Parser::type() {

    fprintf(stdout,"Type\n");

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
        default:
            sync(F_type);

    }
}

int F_typeCompl[]={3,POINTER,ID,CMMEOF};

void Parser::typeCompl() {

    fprintf(stdout,"TypeCompl\n");
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
        default:
            sync(F_typeCompl);

    }
}


void c_parse() {
    Parser::parse();
}

char* Parser::translate(int token) {
    switch (token) {
        case ID: return "id";
        case SEMICOLON: return ";";
        case COLON: return ":";
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