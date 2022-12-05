#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void tokenize(string str, vector<string> &token_v, string DELIMITER);
string translate(string in);

int main(int argc, char *argv[]) {
    ifstream arq;
    string line;

    if(argc>1){
        arq.open(argv[1]);
    }else {
        arq.open("Test");
    }
    vector<string> nonTerminals;
    vector<vector<string>> terminals;

    while(getline(arq,line)){

        vector<string> sentences;

        tokenize(line,sentences," ::= ");
        nonTerminals.push_back(sentences.at(0));

        vector<string> newTerminals;
        tokenize(sentences.at(1),newTerminals," | ");

        terminals.push_back(newTerminals);

    }

    for(int i=0;i<nonTerminals.size();i++){
        cout << translate(nonTerminals.at(i)) << " -> ";
        for(int j=0;j<terminals.at(i).size();j++){

            vector<string> pieces;
            tokenize(terminals.at(i).at(j),pieces," ");

            if(j!=0) {
                cout << " | ";
            }
            for(int k=0;k<pieces.size();k++) {
                cout << translate(pieces.at(k));
                if(k!=(pieces.size()-1)){
                    cout<<" ";
                }
            }
            if(j==(terminals.at(i).size()-1)){
                cout<<".";
            }
            cout<<endl;
        }
    }

    return 0;
}

void tokenize(string str, vector<string> &token_v, string DELIMITER) {
    size_t start = str.find_first_not_of(DELIMITER), end=start;

    while (start != std::string::npos) {
        end = str.find(DELIMITER, start);
        token_v.push_back(str.substr(start, end-start));
        start = str.find_first_not_of(DELIMITER, end);
    }
}

string translate(string in){
    //Non-terminal productions
    if(in.at(0)=='<'){
        string ret="";

        for(int i=1;i<in.size()-1;i++){
            if(in.at(i)>96 && in.at(i)<123){
                ret+=in.at(i)-32;
            }else{
                ret+=in.at(i);
            }
        }
        return ret;

        //Terminal Productions
    } else if (in=="\"-\""){
        return "minus";
    }else if (in=="\"+\""){
        return "plus";
    }else if (in=="\"=\"" || in=="="){
        return "assign";
    }else if (in=="\"==\""){
        return "eq";
    }else if (in=="\"<\""){
        return "less";
    }else if (in=="\"<=\""){
        return "leq";
    }else if (in=="\">\""){
        return "great";
    }else if (in=="\">=\""){
        return "geq";
    }else if (in=="\"!\""){
        return "not";
    }else if (in=="\"!=\""){
        return "neq";
    }else if (in=="\"*\""){
        return "mult";
    }else if (in=="\"/\""){
        return "div";
    }else if (in=="\"%\""){
        return "mod";
    }else if (in=="\"&\""){
        return "ampersand";
    }else if (in=="\"&&\""){
        return "and";
    }else if (in=="\"|\""){
        return "pipe";
    }else if (in=="\"||\""){
        return "or";
    }else if (in=="*"){
        return "pointercontent";
    }else if (in=="\"->\""){
        return "pointerprop";
    }else if (in=="{"){
        return "leftbrace";
    }else if (in=="}"){
        return "rightbrace";
    }else if (in=="["){
        return "leftbracket";
    }else if (in=="]"){
        return "rightbracket";
    }else if (in=="("){
        return "leftparentheses";
    }else if (in==")"){
        return "rightparentheses";
    }else if (in==":" || in=="\":\""){
        return "colon";
    }else if (in==";"){
        return "semicolon";
    }else if (in=="." || in=="\".\""){
        return "point";
    }else if (in==","){
        return "comma";
    }else if (in=="typedef"){
        return in;
    }else if (in=="struct"){
        return in;
    }else if (in=="long"){
        return in;
    }else if (in=="int"){
        return in;
    }else if (in=="float"){
        return in;
    }else if (in=="bool"){
        return in;
    }else if (in=="char"){
        return in;
    }else if (in=="double"){
        return in;
    }else if (in=="if"){
        return in;
    }else if (in=="while"){
        return in;
    }else if (in=="switch"){
        return in;
    }else if (in=="break"){
        return in;
    }else if (in=="print"){
        return in;
    }else if (in=="readln"){
        return in;
    }else if (in=="return"){
        return in;
    }else if (in=="throw"){
        return in;
    }else if (in=="try"){
        return in;
    }else if (in=="catch"){
        return in;
    }else if (in=="case"){
        return in;
    }else if (in=="true"){
        return in;
    }else if (in=="false"){
        return in;
    }else if (in=="else"){
        return in;
    }else if (in=="ID"){
        return "id";
    }else if (in=="NUM"){
        return "num";
    }else if (in=="LITERAL"){
        return "literal";
    }else if (in=="'ASCII'"){
        return "ascii";
    }else if (in=="epsilon"){
        return "";
    }else{
        cout<<"Impossible to recognize "+in<<endl;
        exit(100);
    }

}