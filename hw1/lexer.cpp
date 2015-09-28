/* lexer.cpp - a lexical analyzer for c */

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
using namespace std;



/* Global declarations */

/* Variables */
ifstream fin;
ofstream fout;
string keywordTable[] =
{"int","char","float","double","main","return","if","else","while","break","for","print"};
vector<string> keywords(keywordTable, keywordTable+12);
string op1("=!+-*/<>&|");
string op2("=>&|");
string special("{}();,[]");
string lexeme;
char nextChar;
char peekChar;
int lineNum = 1;
int charClass;
int peekClass;

/* Function declarations */
void getChar();
void getPeek();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define OTHERS 99
#define UNDERLINE 3
#define BLANK 4
#define NEWLINE 5
#define TAB 6


int main(){
    /* Open the input source file to read */
    fin.open("gift.c");
    if (fin.fail()) {
        cout << "Input file opening failed." << endl;
        exit(1);
    }
    /* Open the output file to write */
    fout.open("token.txt");
    if (fout.fail()) {
        cout << "Output file opening failed." << endl;
        exit(1);
    }
    
    fout << "Line " << lineNum++ << ":" << endl;
    getChar();
    while (! fin.eof()) {
        /* Use the class of the next character to determine the state */
        switch (charClass) {
                /* get rid of blank and tab */
            case BLANK:
                break;
            case TAB:
                break;
                /* print a new line if encountering newline */
            case NEWLINE:
                fout << "Line " << lineNum++ << ":" << endl;
                lexeme.clear();
                break;
                /* begin with _ would be a identifier */
            case UNDERLINE:
                lexeme += nextChar;
                getPeek();
                /* add charater to lexeme until the next charater
                 is not letter or digit or underline*/
                while ((isalnum(peekChar))||(peekChar == '_')) {
                    getChar();
                    lexeme += nextChar;
                    getPeek();
                }
                fout << "\t<Identifier>\t:\t" << lexeme << endl;
                lexeme.clear();
                break;
                /* begin with a letter, keyoword or id are possible */
            case LETTER:
                lexeme += nextChar;
                getPeek();
                /* add charater to lexeme until the next charater
                 is not letter or digit or underline*/
                while ((isalnum(peekChar))||peekChar == '_') {
                    getChar();
                    lexeme += nextChar;
                    getPeek();
                }
                /* look up keyword table */
                for (unsigned i=0; i<keywords.size(); i++) {
                    if (keywords.at(i) == lexeme) { //is keyword
                        fout << "\t<Keyword>\t:\t" << lexeme << endl;
                        lexeme.clear();
                        break;
                    }
                }
                /* do not print the id if keyword has been output and lexeme is empty */
                if (lexeme.empty()) {
                    break;
                }
                fout << "\t<Identifier>\t:\t" << lexeme << endl;
                lexeme.clear();
                break;
                /* begin with a digit, number or error are possible */
            case DIGIT:
                lexeme += nextChar;
                getPeek();
                while ((peekClass == DIGIT)||peekChar == '.') {
                    getChar();
                    lexeme += nextChar;
                    getPeek();
                }
                if (peekClass == LETTER) {
                    do {
                        getChar();
                        lexeme += nextChar;
                        getPeek();
                    } while (isalnum(peekChar));
                    fout << "\t<Error>\t\t:\t" << lexeme << endl;
                    lexeme.clear();
                    break;
                }
                fout << "\t<Number>\t:\t" << lexeme << endl;
                lexeme.clear();
                break;
                /* begin with other character, operator or special or char are possible */
            case OTHERS:
                lexeme += nextChar;
                if ((op1.find(nextChar)) != string::npos) { //in op1
                    getPeek();
                    if (peekChar == '/') { //is comment
                        lexeme.clear();
                        do {
                            getChar();
                        } while (nextChar != '\n');
                        fout << "Line " << lineNum++ << ":" << endl;
                        break;
                    }else if((op2.find(peekChar)) != string::npos) { //in op2
                        getChar();
                        lexeme += nextChar;
                        fout << "\t<Operator>\t:\t" << lexeme << endl;
                        lexeme.clear();
                    }else{
                        fout << "\t<Operator>\t:\t" << lexeme << endl;
                        lexeme.clear();
                    }
                }
                if (special.find(nextChar) != string::npos) { //in special
                    fout << "\t<Special>\t:\t" << lexeme << endl;
                    lexeme.clear();
                }
                if (nextChar == 39) { //char
                    do {
                        getChar();
                        lexeme += nextChar;
                        getPeek();
                    } while (peekChar != 39);
                    fout << "\t<Char>\t\t:\t" << lexeme << "'" << endl;
                    lexeme.clear();
                    getChar();
                }
                break;
            default:
                break;
        }
        getChar();
    }
    
    fin.close();
    fout.close();
    return 0;
}
/*****************************************************/
/* getChar - a function to get the next character of
 input and determine its character class */

void getChar(){
    fin.get(nextChar); //begin char of file
    if (isalpha(nextChar)) {
        charClass = LETTER;
    } else if(isdigit(nextChar)){
        charClass = DIGIT;
    } else if(nextChar == '_'){
        charClass = UNDERLINE;
    } else if(nextChar == ' '){
        charClass = BLANK;
    } else if(nextChar == '\n'){
        charClass = NEWLINE;
    } else if(nextChar == '\t'){
        charClass = TAB;
    } else
        charClass = OTHERS;
}
/*****************************************************/
/* getPeek - a function to peek the next of the next
 character of input but does not use up
 as well as determine its character class */

void getPeek(){
    peekChar = fin.peek();
    if (isalpha(peekChar)) {
        peekClass = LETTER;
    } else if(isdigit(peekChar)){
        peekClass = DIGIT;
    } else if(peekChar == '_'){
        peekClass = UNDERLINE;
    } else if(peekChar == ' '){
        peekClass = BLANK;
    } else if(peekChar == '\n'){
        peekClass = NEWLINE;
    } else if(peekChar == '\t'){
        peekClass = TAB;
    } else
        peekClass = OTHERS;
}
