/*-----------------------------------------------------------------
 filename: find_set.cpp
 Compile: g++ -Wall -W -pedantic -o find_set find_set.cpp
 ------------------------------------------------------------------*/

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
#include <array>
#include <iomanip>
using namespace std;


/* Variables */
ifstream fin;
ofstream fout;

vector<string> nonterminals;
vector<string> productions;
vector<int> num_productions;
int num_nonterminals = 0;

array<bool,27> yn_first;
array<bool,27> yn_follow;

vector<string> first_set (27);
vector<string> follow_set (27);

/*Function declarations */
void find_first(int);
void find_follow(int);

int main(){
    /* Open the grammar file to read */
    fin.open("grammar.txt");
    if (fin.fail()) {
        cout << "Input file opening failed." << endl;
        exit(1);
    }
    /* Open the output file to write */
    fout.open("set.txt");
    if (fout.fail()) {
        cout << "Output file opening failed." << endl;
        exit(1);
    }
    /*-----------------------------------------------------------------------*/
    int count = 0;
    string s1;
    while (! fin.eof()) {
        getline(fin, s1);
        if (isupper(s1.front())) {
            num_nonterminals++;
            nonterminals.push_back(s1);
            if(num_nonterminals == 1){
                continue;
            }
            num_productions.push_back(count);
            count = 0;
        }
        else if(isspace(s1.front())){
            count++;
            productions.push_back(s1);
        }
    }
    num_productions.push_back(count);
    for (size_t k = 0; k < productions.size(); k++) {     //去掉前面的空白
        productions.at(k) = productions.at(k).substr(1);
    }
    /*----------------------------------------------------------------------*/
    yn_first.fill(false);
    yn_follow.fill(false);
    
    fout << "First" << endl;
    for (int i = 0; i < num_nonterminals; i++) {
        if (yn_first.at(i) == false) {
            find_first(i);
        }
        fout << left << setfill(' ') << setw(20) << nonterminals.at(i);
        fout << ": " << first_set.at(i) << endl;
    }
    fout << endl;
    fout << endl;
    fout << endl;
    fout << "Follow" << endl;
    follow_set.at(0).append("$ ");     //$ at start symbol
    for (int i = 0; i < num_nonterminals; i++) {
        if (yn_follow.at(i) == false) {
            find_follow(i);
        }
        fout << left << setfill(' ') << setw(20) << nonterminals.at(i);
        fout << ": " << follow_set.at(i) << endl;
    }
    fin.close();
    fout.close();
    return 0;
}


void find_follow(int index){
    vector<size_t> foundProductionIndex;
    vector<size_t> firstMatchIndex; //用來找next symbol
    size_t proIndex;
    
    string s0 = nonterminals.at(index);
    string fString = s0.insert(0," ");
    string s1 = fString;
    size_t sLength = s1.length();
    string eString = s1.insert(sLength," ");
    
    for (proIndex = 0; proIndex < productions.size(); proIndex++) {
        
        string tempProduction = productions.at(proIndex);
        tempProduction = tempProduction.insert(0," ");
        
        if (tempProduction.length() > nonterminals.at(index).length()) {
            size_t lastStringIndex = tempProduction.length() - nonterminals.at(index).length();
            if (tempProduction.find(fString, lastStringIndex-1) != string::npos) {
                foundProductionIndex.push_back(proIndex);
                firstMatchIndex.push_back(tempProduction.find(fString, lastStringIndex-1));
            }
            if (tempProduction.find(eString) != string::npos) {
                foundProductionIndex.push_back(proIndex);
                firstMatchIndex.push_back(tempProduction.find(eString));
            }
        }
    }
    
    size_t preLeftSideIndex = 99, leftSideIndex = 99;
    
    for (size_t i = 0; i < foundProductionIndex.size(); i++) {
        if (foundProductionIndex.size() == 0) {
            //break;
        }
        size_t nextBegin, nextEnd, nextLen, whichProduction;
        size_t nextIndex;
        string next;
        nextBegin = firstMatchIndex.at(i) + nonterminals.at(index).length();
        whichProduction = foundProductionIndex.at(i);
        
        /*Find left side nonterminal index*/
        preLeftSideIndex = leftSideIndex;
        size_t preleft, thisleft = 0;
        for (leftSideIndex = 0; leftSideIndex < num_productions.size() ; leftSideIndex++) {
            preleft = thisleft;
            thisleft += num_productions.at(leftSideIndex);
            if(whichProduction < thisleft && whichProduction >= preleft){
                break;
            }
        }
        
        //Next at the end
        if (nextBegin == productions.at(whichProduction).length()) {
            if (leftSideIndex != index){
                if (index == 9 && leftSideIndex == 10) {
                    continue;
                }else if(index == 15 && leftSideIndex == 16){
                    continue;
                }else if(index == 18 && leftSideIndex == 19){
                    continue;
                }else if(index == 18 && leftSideIndex == 20){
                    continue;
                }else if(index == 18 && leftSideIndex == 21){
                    continue;
                }else if(index == 23 && leftSideIndex == 24){
                    continue;
                }else if (preLeftSideIndex == leftSideIndex) {
                    break;
                }else if (yn_follow.at(leftSideIndex) == false) {
                    find_follow(leftSideIndex);
                }
                if(index == 5 && leftSideIndex == 4){
                    string s1 = follow_set.at(leftSideIndex);
                    s1 = s1.substr(24);
                    follow_set.at(index).append(s1);
                    continue;
                }
                follow_set.at(index).append(follow_set.at(leftSideIndex));
            }
        }else{
            
            nextEnd = productions.at(whichProduction).find(" ", nextBegin+1);
            nextLen = nextEnd - (nextBegin+1);
            next = productions.at(whichProduction).substr(nextBegin+1, nextLen);
            if (ispunct(next.front()) || islower(next.front())){
                if (follow_set.at(index).find(next) == string::npos) {
                    follow_set.at(index).append(next);
                    follow_set.at(index).append(" ");
                }
            }
            if (isupper(next.front())) {
                //由next找到nonterminal的index
                for (nextIndex = 0; nextIndex < nonterminals.size(); nextIndex++) {
                    if (nonterminals.at(nextIndex).compare(next) == 0) {
                        break;
                    }
                }
                //check first set of left side whether having ε?
                //把left side的first set加進欲找nonterminal的follow set
                if(first_set.at(nextIndex).find("ε") != string::npos){
                    size_t epsilonIndex = first_set.at(nextIndex).find("ε");
                    string remainString = first_set.at(nextIndex).substr(0, epsilonIndex);
                    follow_set.at(index).append(remainString);
                    if (yn_follow.at(leftSideIndex) == false) {
                        find_follow(leftSideIndex);
                    }
                    if ((follow_set.at(index).find(follow_set.at(leftSideIndex))) == string::npos) {
                        follow_set.at(index).append(follow_set.at(leftSideIndex));
                    }
                }else{
                    follow_set.at(index).append(first_set.at(nextIndex));
                }
            }
        }
    }
    yn_follow.at(index) = true;
}

void find_first(int index){
    int initial = 0;
    // production at num_productions[0]+...+num_productions[i-1]
    //找出欲找nonterminal的production初使位置
    for (int k = 0; k < index ; k++) {
        initial += num_productions.at(k);
    }
    //cout << nonterminals.at(index) << ":" << initial << endl;
    int endpoint = initial + num_productions.at(index);
    for (int j = initial; j < endpoint; j++) { //對每一個productions
        //切出第一個單詞
        size_t blank = productions.at(j).find_first_of(" ");
        string sub_production = productions.at(j).substr(0,blank);
        if (ispunct(sub_production.front()) || islower(sub_production.front())){
            if (sub_production.find("epsilon") != string::npos) {
                first_set.at(index).append("ε ");
            }else{
                first_set.at(index).append(sub_production);
                first_set.at(index).append(" ");
            }
        }
        if (isupper(sub_production.front())) {
            int index_2;
            //找index
            for (index_2 = 0; index_2 < num_nonterminals; index_2++) {
                if (nonterminals.at(index_2) == sub_production) {
                    break;
                }
            }
            if (yn_first.at(index_2) == false) {
                find_first(index_2);
            }
            first_set.at(index).append(first_set.at(index_2));
            first_set.at(index).append(" ");
        }
    }
    yn_first.at(index) = true;
}

