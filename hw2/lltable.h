//
//  lltable.h
//  
//
//  Created by chou  on 2015/5/7.
//
//

#ifndef ____lltable__
#define ____lltable__

#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <cstdlib>
#include <cctype>
#include <array>
#include <iomanip>
#include <map>
#include <stdio.h>
using namespace std;

#define NUM_PRODUCTIONS 67
#define NUM_NONTERMINALS 27
#define NUM_TERMINALS 35
#define MAX_FIRST_SET 17
#define MAX_FOLLOW_SET 19
#define EPSILON 99

/* Global declarations */

/* Variables */
ifstream fin;
ofstream fout;

int leftToProArray[] = {0,1,1,2,3,3,4,5,5,6,7,7,8,8,9,10,10,11,12,12,13,14,14,14,14,15,16,16,17,17,17,17,17,17,17,17,18,18,18,18,19,19,19,19,20,20,21,21,22,22,23,24,24,25,25,26,26,26,26,26,26,26,26,26,26,26,26};
vector<int> leftToPro (leftToProArray, leftToProArray + sizeof(leftToProArray) / sizeof(int) );

int rightToProArray[] = {1,2,99,14,5,6,14,12,18,16,4,99,9,99,11,13,99,14,18,99,20,0,1,2,3,17,15,99,12,18,6,7,8,10,13,11,25,4,16,5,21,16,18,25,21,25,26,99,23,99,18,13,99,14,15,22,14,23,24,26,27,28,29,30,31,32,33};

vector<int> rightToPro (rightToProArray, rightToProArray + sizeof(rightToProArray) / sizeof(int) );

int firstSizeArray[] = {5,5,4,3,4,2,1,5,5,4,2,4,2,1,4,12,13,12,5,16,14,13,6,5,2,2,12};

vector<int> firstSize (firstSizeArray, firstSizeArray + sizeof(firstSizeArray) / sizeof(int) );

int followSizeArray[] = {1,1,5,5,16,17,5,12,1,1,1,2,2,19,1,1,1,14,4,4,4,4,1,1,1,5,5};

vector<int> followSize (followSizeArray, followSizeArray + sizeof(followSizeArray) / sizeof(int) );

int firstSet[NUM_NONTERMINALS][MAX_FIRST_SET] =
{
    {0,1,2,3,99},{0,1,2,3,99},{0,1,2,3},{12,18,16},{0,1,2,3},{12,18},{16},{0,1,2,3,99},{0,1,2,3,99},{0,1,2,3},{13,99},{0,1,2,3},{18,99},{20},{0,1,2,3},{12,14,15,4,16,5,6,7,8,10,20,11},{12,14,15,4,16,5,6,7,8,10,20,11,99},{12,14,15,4,16,5,6,7,8,10,20,11},{14,15,4,16,5},{22,14,23,24,26,27,28,29,30,31,32,33,16,18,25,99},{22,14,23,24,26,27,28,29,30,31,32,33,25,99},{22,14,23,24,26,27,28,29,30,31,32,33,99},{14,15,4,16,5,99},{14,15,4,16,5},{13,99},{14,15},{22,14,23,24,26,27,28,29,30,31,32,33}
    
};
int followSet[NUM_NONTERMINALS][MAX_FOLLOW_SET] =
{
    {34},{34},{0,1,2,3,34},{0,1,2,3,34},{0,1,2,3,12,14,15,4,5,6,7,16,8,10,20,11},{0,1,2,3,12,14,15,4,5,6,7,16,8,10,20,11,34},{0,1,2,3,34},{12,14,15,4,5,6,7,16,8,10,20,11},{17},{17},{17},{13,17},{13,17},{0,1,2,3,12,14,15,4,5,6,7,16,8,10,20,11,21,9,34},{5},{21},{21},{12,14,15,4,5,6,7,16,8,10,20,11,21,9},{12,17,19,13},{12,17,19,13},{12,17,19,13},{12,17,19,13},{17},{17},{17},{14,15,4,16,5},{14,15,4,16,5}
};

int lltable[NUM_NONTERMINALS][NUM_TERMINALS];

int num_nonterminals = 0;
vector<string> nonterminals;
vector<string> productions;
vector<int> num_productions;
string terminalList[] = {"int","char","double","float","num","id","return","break","if","else","while","print",";",",","-","!","(",")","[","]","{","}","+","*","/","=","==","!=","<","<=",">",">=","&&","||","$"};
vector<string> terminals(terminalList, terminalList + sizeof(terminalList) / sizeof(string));

#endif /* defined(____lltable__) */
