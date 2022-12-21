//
// Created by Rafael on 12/19/2022.
//

#include "Parser.h"

Parser::Parser() {

}

Parser::~Parser() {

}

void Parser::match(int token) {
    if(token != FIRSTTOKEN) {
        if (token == this->token->token) {
            delete this->token;
            this->token = nextToken();
        } else {
            printf("Unexpected Token \n");
        }
    }else{
        this->token=nextToken();
    }
}

void Parser::parse() {

    Parser* parser = new Parser();
    parser->match(FIRSTTOKEN);
    parser->program(parser->token->token);


}

void Parser::program(int token) {
    
    switch (token) {
        case DOUBLE:
            declprefix(token);
            declsulfix(token); break;
        case CHAR:
            declprefix(token);
            declsulfix(token); break;
        case ID:
            declprefix(token);
            declsulfix(token); break;
        case BOOL:
            declprefix(token);
            declsulfix(token); break;
        case FLOAT:
            declprefix(token);
            declsulfix(token); break;
        case INT:
            declprefix(token);
            declsulfix(token); break;
        case LONG:
            declprefix(token);
            declsulfix(token); break;
        case TYPEDEF:
            typedecl(token);
            program(token); break;
        default: printf("Error!");

    }

}


void Parser::declprefix(int token) {
    switch (token) {
        case DOUBLE:
            type(token);
            pointer(token);
            match(ID); break;
        case CHAR:
            type(token);
            pointer(token);
            match(ID); break;
        case ID:
            type(token);
            pointer(token);
            match(ID); break;
        case BOOL:
            type(token);
            pointer(token);
            match(ID); break;
        case FLOAT:
            type(token);
            pointer(token);
            match(ID); break;
        case INT:
            type(token);
            pointer(token);
            match(ID); break;
        case LONG:
            type(token);
            pointer(token);
            match(ID); break;
        default: printf("Error!");

    }
}

void Parser::declsulfix(int token) {
    switch (token) {
        case LEFTBRACKET:
            vardeclsulfix(LEFTBRACKET);
            program(token);
            match(ID); break;
        case CHAR:
            type(token);
            pointer(token);
            match(ID); break;
        case ID:
            type(token);
            pointer(token);
            match(ID); break;
        case BOOL:
            type(token);
            pointer(token);
            match(ID); break;
        case FLOAT:
            type(token);
            pointer(token);
            match(ID); break;
        case INT:
            type(token);
            pointer(token);
            match(ID); break;
        case LONG:
            type(token);
            pointer(token);
            match(ID); break;
        default: printf("Error!");

    }
}

void Parser::expr6() {
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

    }

}
void Parser::expr7() {
    switch(this->token->token){
        case PLUS:
        case MINUS:
        case NOT:
            unaryop();
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
    switch(this->token->token){
        case LEFTPARENTHESES:
            match(LEFTPARENTHESES);
            exprlist();
            match(RIGHTPARENTHESES);
            break;
    }
}

void Parser::primary3() {
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
    }
}

void Parser::unaryOp() {
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
    match(MULT);
}

void Parser::type() {
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

