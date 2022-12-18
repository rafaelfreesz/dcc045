#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

void tokenize(string str, vector<string> &token_v, string DELIMITER);
string translate(string in);
string reverseTranslate(string in);
bool isNonTerminal(string s);
void grammarToTool();
void firstFollowSets();

int main(int argc, char *argv[]) {

    //firstFollowSets();
    grammarToTool();
    return 0;
}

void firstFollowSets(){
    ifstream arq;
    string line;
    ofstream output("outputfile");
    arq.open("firstFollow");

    while(getline(arq,line)){
        vector<string> elements;
        tokenize(line, elements, " | ");

        vector<string> first;
        tokenize(elements.at(1),first," ");

        vector<string> follow;
        tokenize(elements.at(2),follow," ");

        output<<elements.at(0) + " ||| ";

        for(string str: first){
            output<<reverseTranslate(str)+" ";
        }

        output<<"||| ";

        for(string str: follow){
            output<<reverseTranslate(str)+" ";
        }
        output<<endl;

    }
}

void grammarToTool(){
    ifstream arq;
    string line;


    arq.open("Test");

    vector<string> nonTerminals;
    vector<vector<string>> terminals;

    while(getline(arq,line)){

        if(line!="" && line.substr(0,2)!="\\\\") {
            vector<string> sentences;

            tokenize(line, sentences, " ::= ");
            nonTerminals.push_back(sentences.at(0));

            vector<string> newTerminals;
            tokenize(sentences.at(1), newTerminals, " | ");

            terminals.push_back(newTerminals);
        }

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
}
void tokenize(string str, vector<string> &token_v, string DELIMITER) {
    size_t start = str.find_first_not_of(DELIMITER), end=start;

    while (start != std::string::npos) {
        end = str.find(DELIMITER, start);
        token_v.push_back(str.substr(start, end-start));
        start = str.find_first_not_of(DELIMITER, end);
    }
}
string reverseTranslate(string in){
    //Non-terminal productions
    if (in=="minus"){
        return "\"-\"";
    }else if (in=="plus"){
        return "\"+\"";
    }else if (in=="assign"){
        return "\"=\"";
    }else if (in=="eq"){
        return "\"==\"";
    }else if (in=="less"){
        return "\"<\"";
    }else if (in=="leq"){
        return "\"<=\"";
    }else if (in=="great"){
        return "\">\"";
    }else if (in=="geq"){
        return "\">=\"";
    }else if (in=="not"){
        return "\"!\"";
    }else if (in=="neq"){
        return "\"!=\"";
    }else if (in=="mult"){
        return "\"*\"";
    }else if (in=="div"){
        return "\"/\"";
    }else if (in=="mod"){
        return "\"%\"";
    }else if (in=="ampersand"){
        return "\"&\"";
    }else if (in=="and"){
        return "\"&&\"";
    }else if (in=="pipe"){
        return "\"|\"";
    }else if (in=="or"){
        return "\"||\"";
    }else if (in=="pointercontent"){
        return "*";
    }else if (in=="pointerprop"){
        return "\"->\"";
    }else if (in=="leftbrace"){
        return "{";
    }else if (in=="rightbrace"){
        return "}";
    }else if (in=="leftbracket"){
        return "[";
    }else if (in=="rightbracket"){
        return "]";
    }else if (in=="leftparentheses"){
        return "(";
    }else if (in=="rightparentheses"){
        return ")";
    }else if (in=="colon"){
        return "\":\"";
    }else if (in=="semicolon"){
        return ";";
    }else if (in=="point"){
        return "\".\"";
    }else if (in=="comma"){
        return ",";
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
    }else if (in=="id"){
        return "ID";
    }else if (in=="num"){
        return "NUM";
    }else if (in=="literal"){
        return "LITERAL";
    }else if (in=="ascii"){
        return "'ASCII'";
    }else if (in=="epsilon"){
        return "";
    }else if (in=="emptyset"){
        return in;
    }else{
        cout<<"Impossible to recognize "+in<<endl;
        exit(100);
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
    }else if (in=="\"=\""){
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
    }else if (in=="\":\""){
        return "colon";
    }else if (in==";"){
        return "semicolon";
    }else if (in=="\".\""){
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

bool isNonTerminal(string s){
    return s.at(0)=='<' && s.at(s.size()-1)=='>';
}

bool nonTerminalIsNullable(string nonTerminal, vector<string> nonTerminals, vector<vector<string>> terminals){
    for(int i=0;i<nonTerminals.size();i++){
        if(nonTerminals.at(i)==nonTerminal){
            for(int j=0;j<terminals.size();j++){
                if(terminals.at(i).at(j)=="epsilon"){
                    return true;
                }
            }
                return false;
        }
    }
    cout<<"NonTerminal " + nonTerminal + " not founded"<<endl;
    exit(99);
}

void calculateFirstSet(vector<string> nonTerminals, vector<vector<string>> terminals){

    vector<vector<string>> firstSets;

    for(int i=0;i<nonTerminals.size();i++){
        vector<string> firstSet;
        firstSets.push_back(firstSet);
    }

    bool changed;

    do{
        changed= false;

        for(int i=0;i<nonTerminals.size();i++){

            for(int j=0;j<terminals.at(i).size();j++){

                vector<string> prod;
                tokenize( terminals.at(i).at(j), prod," ");

                for(int k=0;k<prod.size();k++) {
                    // Verifying epsilon production
                    if (prod.at(0) == "epsilon" || !isNonTerminal(prod.at(0))) {
                        firstSets.at(i).push_back("epsilon");
                        changed= true;
                        break;

                    //Verifying nonTerminal conditions
                    }else {
                        firstSets.at(i).push_back(prod.at(k));

                        if(!nonTerminalIsNullable(prod.at(k),nonTerminals,terminals)){

                        }

                    }

                }



            }
        }


    }while(changed);
}