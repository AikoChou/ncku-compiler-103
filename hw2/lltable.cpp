//
//  lltable.cpp
//  
//
//  Created by chou  on 2015/5/7.
//
//
#include "lltable.h"

int main(){
    /* Open the grammar file to read */
    fin.open("grammar.txt");
    if (fin.fail()) {
        cout << "Input file opening failed." << endl;
        exit(1);
    }
    /* Open the output file to write */
    fout.open("LLtable.txt");
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
    for (size_t row = 0; row < nonterminals.size(); row++) {
        for (size_t col = 0; col < terminals.size(); col++) {
            lltable[row][col] = -1;
        }
    }

    size_t proIndex;
    for (proIndex = 0; proIndex < productions.size(); proIndex++) {
        char front = productions.at(proIndex).front();
        int leftIndex = leftToPro.at(proIndex);
        int rightFirst = rightToPro.at(proIndex);

        if (productions.at(proIndex).find("epsilon") != string::npos) {
            //epsilon
            for (int i = 0; i < followSize.at(leftIndex); i++) {
                int eachFollow = followSet[leftIndex][i];
                lltable[leftIndex][eachFollow] = 99;
            }
        }else if(ispunct(front) || islower(front)){
            //terminal
            lltable[leftIndex][rightFirst] = proIndex;
        }else if(isupper(front)){
            //nonterminal
            for (int i = 0; i < firstSize.at(rightFirst); i++) {
                int eachFirst = firstSet[rightFirst][i];
                if (eachFirst == 99) {
                    for (int j = 0; j < followSize.at(leftIndex); j++) {
                        int eachFollow = followSet[leftIndex][j];
                        lltable[leftIndex][eachFollow] = proIndex;
                    }
                }
                lltable[leftIndex][eachFirst] = proIndex;

            }
        
        }else
            cout << "cannot define production! :(" << endl;
    }
    lltable[2][29] = -1;
    
    string startSymbol = "S";
    string startProduction = "Program $";
    fout << startSymbol << endl;
    for (int s = 0; s < firstSize.at(0)-1; s++) {
        fout << left << setfill(' ') << setw(20) << startSymbol;
        fout << left << setfill(' ') << setw(20) << terminals.at(firstSet[0][s]);
        fout << left << setfill(' ') << setw(20) << startProduction << endl;
    }

    for (size_t row = 0; row < nonterminals.size(); row++) {
        for (size_t col = 0; col < terminals.size(); col++) {
             int proIndex2 = lltable[row][col];
            if (proIndex2 == -1) {
             continue;
            }else if(proIndex2 == 99){
                fout << left << setfill(' ') << setw(20) << nonterminals.at(row);
                fout << left << setfill(' ') << setw(20) << terminals.at(col);
                fout << left << setfill(' ') << setw(20) << "ε" << endl;
            }else{
                fout << left << setfill(' ') << setw(20) << nonterminals.at(row);
                fout << left << setfill(' ') << setw(20) << terminals.at(col);
                fout << left << setfill(' ') << setw(20) << productions.at(proIndex2) << endl;
             
            }
            
        }
    }

    for (size_t row = 0; row < nonterminals.size(); row++) {
        for (size_t col = 0; col < terminals.size(); col++) {
            cout << lltable[row][col] << " ";
        }
        cout << endl;
    }
    
    fin.close();
    fout.close();
    return 0;
}


