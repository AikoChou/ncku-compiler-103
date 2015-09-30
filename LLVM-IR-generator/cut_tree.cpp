#include <iostream>
#include <fstream>
#include <string>

using namespace std;

ifstream fin;
ofstream fout;

string node;

int main(){
    fin.open("tree.txt");
    fout.open("treeC.txt");
    
    while(1){
        fin >> node;
        if(fin.eof()) break;
        fin >> node;
        fout << node <<endl;
    }
    fin.close();
    fout.close();
    return 0;
}
