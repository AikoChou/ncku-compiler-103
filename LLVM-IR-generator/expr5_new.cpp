#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include <cstdio>
#include <cctype>
#include <vector>
#include <map>
#include <deque>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
using namespace std;
ifstream fin;
ofstream fout;
string node;
deque<string> tStream;
deque<int> opStream;
deque<string> assigntStream;
int reg = 1; //%1 is main defaule
int assign_flag = 0;
int array_left_flag = 0;
string assignt;
int arraycheck = 0;
deque<int> labelStream;
int label_if;
int if_else_flag = 0;
deque<string> exprStream;
string temp_expr;
int label_while;
int label_loop;
int while_flag = 0;
int returnk=0;
string typeStr[] = {"i32","double"};
vector<string> typeName(typeStr, typeStr+sizeof(typeStr)/sizeof(string));
string typePtrStr[] = {"i32*","double*"};
vector<string> typePtr(typePtrStr, typePtrStr+sizeof(typePtrStr)/sizeof(string));
string typeLen[] = {", align 4", ", align 8"};
vector<string> typeAlign(typeLen, typeLen+sizeof(typeLen)/sizeof(int));
string iopStr[] = {"add nsw","sub nsw","mul nsw","sdiv","icmp eq","icmp ne","icmp slt","icmp sle","icmp sgt", "icmp sge","and","or"};
vector<string> iop(iopStr, iopStr+sizeof(iopStr)/sizeof(string));
string fopStr[] = {"fadd","fsub","fmul","fdiv","fcmp oeq","fcmp une","fcmp olt","fcmp ole","fcmp ogt", "fcmp oge"};
vector<string> fop(fopStr,fopStr+sizeof(fopStr)/sizeof(string));
string OpStr[] = {"+","-","*","/","==","!=","<","<=",">",">=","&&","||","-","!"};
vector<string> Op(OpStr,OpStr+sizeof(OpStr)/sizeof(string));
string symbolStr[] = {"@x","@main","%a","%b","%c","%d","%e","%f","%g","@func","%test"};
vector<string> symbol(symbolStr, symbolStr+sizeof(symbolStr)/sizeof(string));
map<string,int> symbolScope;
map<string,int> symbolType;
map<string,int> isArray;
map<string,int> isFunction;
////////////////////////////////////////////////////////////////
int Program(char Program_[10][100]);
int DeclList(char DeclList_[10][100]);
int DeclListpron(char DeclListpron_[10][100]);
int Decl(char Decl_[10][100]);
int VarDecl(char VarDecl_[10][100]);
int VarDeclpron(char VarDeclpron_[10][100]);
int FunDecl(char FunDecl_[10][100]);
int ParamDeclList(char ParamDeclList_[10][100]);
int ParamDeclListTail(char ParamDeclListTail_[10][100]);
int ParamDeclListTailpron(char ParamDeclListTailpron_[10][100]);
int ParamDecl(char ParamDecl_[10][100]);
int ParamDeclpron(char ParamDeclpron_[10][100]);
int Type(char Type_[10][100]);
//int StmtListpron(char StmtListpron_[10][100]); ////////->int StmtListA();
FILE* tree=fopen("tree.txt","r");
char Tree[10][100];
char stringkkk[100];  //int to string
int FtableI(char id[100],int nowscopel);
int Type(char Type_[10][100]);
////////////////////////////////////////////////////////////////
int Expr();
int ExprIdTail();
int ExprA();
int ExprList();
int ExprListTail();
int ExprListTailA();
int ExprArrayTail();
int Stmt();
int Block();
int VarDeclList();
int StmtList();
int StmtListA();
int Print();
void assignLL();
void UniExprLL();
void BinExprLL();
void If_Else_LL();
void While_LL();
int num_calcu(string t1,string t2);
int oneNum_oneReg_type_check(string t1, string t2);
int type_check(string t1,string t2);
int numType(string numStr);
int regORnum(string t);
string intToString(int a);
string ftoi(string f);
string itof(string i);
void construct_data();
////////////////////////////////////////////////////////////////
int nowscope=1;
struct symboltable
{
    int scope;
    char Symbol[100];
    char Type[10];
    int array;
    int  funct;
    int para;
    char Rname[15];
};
struct symboltable SymbolTable[50];
int STindex=0;
int scoperecord[50];
int scoperecordindex=0;
FILE* code=fopen("code.ll","w");
char functname[100];
char functtype[20];
int getcount=1;
////////////////////////////////////////////////////////////////
int main(){
    construct_data();
    fin.open("treeC.txt");
    fout.open("llvm_code.txt");
    fout<<"target datalayout = \"e-m:e-p:32:32-f64:32:64-f80:32-n8:16:32-S128\""<<endl;
    fout<<"target triple = \"i386-pc-linux-gnu\""<<endl;
    fout<<endl;
    fout<<"@.str = private unnamed_addr constant [3 x i8] c\"%d\\00\", align 1"<<endl;
    fout<<"@.str1 = private unnamed_addr constant [3 x i8] c\"%f\\00\", align 1"<<endl;
    fout<<endl;
    char k[10][100];
    fin >> node;
/*
    while (node != "$") {
        fin >> node;
        if (node == "Stmt") {
            Stmt();
        }
    }
*/
    while (node != "$") {
        fin >> node;
        if (node == "Program") {
            Program(k);
        }
    }
    fout<<endl;
    fout<<"declare i32 @printf(i8*, ...) #1"<<endl;
    fout<<"attributes #0 = { nounwind  \" less-precise-fpmad\" =\" false\"  \" no-frame-pointer-elim\" =\" true\"  \" no-frame-pointer-elim-non-leaf\"  \" no-infs-fp-math\" =\" false\" \"no-nans-fp-math\" = \" false\" \"stack-protector-buffer-size\"=\" 8\" \" unsafe-fp-math\"= \"false\" \" use-soft-float\"=\"false\" }\nattributes #1 = { \"less-precise-fpmad\"=\"false\" \"no-frame-pointer-elim\"=\"true\" \"no-frame-pointer-elim-non-leaf\" \"no-infs-fp-math\"=\"false\" \"no-nans-fp-math\"=\"false\" \"stack-protector-buffer-size\"=\" 8\" \"unsafe-fp-math\"=\"false\" \"use-soft-float\"=\"false\" }\n!llvm.ident = !{!0}\n!0 = metadata !{metadata !\"Ubuntu clang version 3.5.0-4ubuntu2 (tags/RELEASE_350/final) (based on LLVM 3.5.0)\"}\n";
    fin.close();
    fout.close();
    return 0;
}
void UniExprLL(){
    ;
}
void assignLL(){
    char c[20];
    string result;
    assignt = assigntStream.front();
    int assigntType = symbolType[assignt];
    string t = tStream.front();
    if (isalpha(t[1])||(arraycheck&&(!array_left_flag))) { //a=b
        fout<<" %"<<reg<<" = load "<<typePtr[symbolType[t]]<<" "<<t<<typeAlign[symbolType[t]]<<endl;
        symbolType.insert(pair<string,int>("%"+intToString(reg),symbolType[t]));
        t = "%"+intToString(reg);
        reg++;
        }
    if (symbolType[t] != assigntType) { //type correct, modify t or update t
        if (regORnum(t)) { //reg
            switch (assigntType) {
                case 0: {//int
                    if (if_else_flag||while_flag) {
                        temp_expr =" %"+intToString(reg)+" = fptosi double "+t+" to i32";
                        exprStream.push_back(temp_expr);
                    }else{
                        fout<<" %"<<reg<<" = fptosi double "<<t<<" to i32"<<endl;
                    }
                    cout<<"warning(scope "<<nowscope<<") : "<<assignt.substr(1)<<" int, temp double"<<endl;
                    break;  }
                case 1: {//double
                    if (if_else_flag||while_flag) {
                        temp_expr =" %"+intToString(reg)+" = sitofp i32 "+t+" to double";
                        exprStream.push_back(temp_expr);
                    }else{
                        fout<<" %"<<reg<<" = sitofp i32 "<<t<<" to double"<<endl;
                    }
                    cout<<"warning(scope "<<nowscope<<") : "<<assignt.substr(1)<<" double, temp int"<<endl;
                    break;  }
                default:
                    break;
            }
            tStream.pop_front();
            result = "%"+intToString(reg);
            tStream.push_back(result);
            symbolType.insert(pair<string,int>(result,assigntType));
            reg++;
            t = tStream.front();
        }else{ //num
            switch (assigntType) {
                case 0: //t: double to int
                {
                    sprintf(c,"%f",atof(t.c_str()));
                    string f(c);
                    cout<<"warning(scope "<<nowscope<<") : "<<assignt.substr(1)<<" int, "<<t<<" double"<<endl;
                    t = ftoi(t);
                    break;
                }
                case 1: //t: int to double
                {
                    cout<<"warning(scope "<<nowscope<<") : "<<assignt.substr(1)<<" double, "<<t<<" int"<<endl;
                    t = itof(t);
                    break;
                }
                default:
                    break;
            }
        }
    }
    if (if_else_flag||while_flag) {
        temp_expr=" store "+typeName[assigntType]+" "+t+", "+typePtr[assigntType]+" "+assignt+typeAlign[assigntType];
        exprStream.push_back(temp_expr);
    }else{
        fout<<" store "<<typeName[assigntType]<<" "<<t<<", "<<typePtr[assigntType]<<" "<<assignt<<typeAlign[assigntType]<<endl;
    }
    tStream.pop_front();//pop t
    assigntStream.pop_front();
}
//tStream: 5 a b 6
//opStream: + +
void BinExprLL(){
    string t1, t2, result;
    int op_index, intORdouble; //0: int, 1:double
    while (!opStream.empty()){
        t1 = tStream.front();
        tStream.pop_front();
        t2 = tStream.front();
        tStream.pop_front();
//fout << "t1: " << t1<< endl;
//fout << "t2: " << t2<< endl;
//fout << "op: " << opStream.front()<<endl;
        if ((regORnum(t1)==0)&&(regORnum(t2)==0)) { //num num
            //delete op in opStream, break out this while loop
            num_calcu(t1, t2);
            opStream.pop_front();
            break;
        }else if(regORnum(t1)^regORnum(t2)){ //num reg or reg num
            intORdouble = oneNum_oneReg_type_check(t1,t2);
        }else{ //reg reg
            intORdouble =  type_check(t1,t2);
        }
        //new t1, t2 in tStream, op still in opStream
        t1 = tStream.front();
        tStream.pop_front();
        t2 = tStream.front();
        tStream.pop_front();
        op_index = opStream.front();
        if (intORdouble) { //double
            if (if_else_flag||while_flag) {
                temp_expr =" %"+intToString(reg)+" = "+fop[op_index]+" double "+t1+", "+t2;
                exprStream.push_back(temp_expr);
            }else{
                if ((op_index==11)||(op_index==12)) {
                    fout<<" %"<<reg<<" = fcmp une double "<<t1<<", 0.000000e+00"<<endl; reg++;
                    fout<<" %"<<reg<<" = fcmp une double "<<t2<<", 0.000000e+00"<<endl; reg++;
                    fout<<" %"<<reg<<" = zext i1 %"<<reg-2<<" to i32"<<endl; reg++;
                    fout<<" %"<<reg<<" = zext i1 %"<<reg-2<<" to i32"<<endl; reg++;
                    fout<<" %"<<reg<<" = "<<iop[op_index]<<" %"<<reg-2<<", %"<<reg-1<<endl; reg++;
                    fout<<" %"<<reg<<" = trunc i32 %"<<reg-1<<" to i1"<<endl;
                }else{
                    fout<<" %"<<reg<<" = "<< fop[op_index] <<" double "<<t1<<", "<<t2<<endl;
                }
            }
        }else{  //int
            if (if_else_flag||while_flag) {
                temp_expr =" %"+intToString(reg)+" = "+iop[op_index]+" i32 "+t1+", "+t2;
                exprStream.push_back(temp_expr);
            }else{
                if ((op_index==11)||(op_index==12)) { //&& ||
                    fout<<" %"<<reg<<" = icmp ne i32 "<<t1<<", 0"<<endl; reg++;
                    fout<<" %"<<reg<<" = icmp ne i32 "<<t2<<", 0"<<endl; reg++;
                    fout<<" %"<<reg<<" = zext i1 %"<<reg-2<<" to i32"<<endl; reg++;
                    fout<<" %"<<reg<<" = zext i1 %"<<reg-2<<" to i32"<<endl; reg++;
                    fout<<" %"<<reg<<" = "<<iop[op_index]<<" %"<<reg-2<<", %"<<reg-1<<endl; reg++;
                    fout<<" %"<<reg<<" = trunc i32 %"<<reg-1<<" to i1"<<endl;
                }else{
                    fout<<" %"<<reg<<" = "<< iop[op_index] <<" i32 "<<t1<<", "<<t2<<endl;
                }
            }
        }
        
        result = "%"+intToString(reg);
//cout<<"result: "<<result<<endl;
        tStream.push_front(result);
        symbolType.insert(pair<string,int>(result,intORdouble));
        reg++;
        opStream.pop_front();
        
        if(assign_flag>0) {
            assignLL();
            assign_flag--;
        }
    }
}
void If_Else_LL(){
    int label_else,label_jp;
    label_else=labelStream.front();
    labelStream.pop_front();
    label_jp=labelStream.front();
    labelStream.pop_front();
    fout<<" br i1 %"<<label_if-1<<", label %"<<label_if<<", label %"<<label_else<<endl;
    fout<<endl;
    
    fout<<"; <label>:"<<label_if<<endl; //10
    while (exprStream.front() != ":)") {
        fout<<exprStream.front()<<endl;
        exprStream.pop_front();
    }
    exprStream.pop_front();
    fout<<" br label %"<<label_jp<<endl;
    fout<<endl;
    fout<<"; <label>:"<<label_else<<endl; //13
    while (exprStream.front() != ":)") {
        fout<<exprStream.front()<<endl;
        exprStream.pop_front();
    }
    exprStream.pop_front();
    fout<<" br label %"<<label_jp<<endl;
    fout<<endl;
    fout<<"; <label>:"<<label_jp<<endl;
}
void While_LL(){
    int label_jp;
    label_jp=labelStream.front();
    labelStream.pop_front();
    fout<<" br i1 %"<<label_loop-1<<", label %"<<label_loop<<", label %"<<label_jp<<endl;
    fout<<endl;
    
    fout<<"; <label>:"<<label_loop<<endl; //20
    while (exprStream.front() != ":)") {
        fout<<exprStream.front()<<endl;
        exprStream.pop_front();
    }
    exprStream.pop_front();
    fout<<" br label %"<<label_while<<endl;
    fout<<endl;
    fout<<"; <label>:"<<label_jp<<endl;
}
string returnvalue;
int Stmt(){
    fin >> node;
    if(node == ";"){
        ;
    }else if (node == "Expr") { // Expr ;
        Expr();
        if(!opStream.empty()){
            BinExprLL();
        }
        if(assign_flag>0) {
            assignLL();
            assign_flag--;
        }
        arraycheck = 0;
        array_left_flag = 0;
        fin >> node; //;
    }else if (node == "return"){
        fin >> node; //Expr
        Expr();
        if(!opStream.empty()){
            BinExprLL();
        }
        if(assign_flag>0) {
            assignLL();
            assign_flag--;
        }
        if(!tStream.empty()){
            string t = tStream.front();
            if (isalpha(t[1])) { //a=b
                fout<<" %"<<reg<<" = load "<<typePtr[symbolType[t]]<<" "<<t<<typeAlign[symbolType[t]]<<endl;
                symbolType.insert(pair<string,int>("%"+intToString(reg),symbolType[t]));
                t = "%"+intToString(reg);
                reg++;
            }
            fout<<" ret "<<typeName[symbolType[t]]<<" "<<t<<endl;
            returnvalue=tStream.front();
            tStream.pop_front();
        }
        fin >> node; //;
//        cout<<"ret "<<(symbolType[tStream.back()]?" double ":" i32 ");
//        cout<< tStream.back()<<endl;
//        returnvalue=tStream.back();
//        tStream.pop_back();
    }else if(node == "if"){ //If-else
        fin >> node; //(
        fin >> node; //Expr
        Expr();
        BinExprLL();
        label_if = reg; //10
        reg++;
//fout<<"pop tStream: "<<tStream.front()<<endl;
        tStream.pop_front();
        if_else_flag = 1;
        fin >> node; //)
        fin >> node; //Stmt
        Stmt();
        fin >> node; //else
        fin >> node;
        Stmt();
        If_Else_LL();
        if_else_flag = 0;
    }else if(node == "while"){ //while
        fin >> node; //(
        label_while = reg;
        fout<<" br label %"<<reg<<endl; //17
        fout<<endl;
        fout<<"; <label>:"<<reg<<endl; //17
        reg++;
        
        fin >> node; //Expr
        Expr();
        BinExprLL();
        
        label_loop = reg; //20
        reg++;
//fout<<"pop tStream: "<<tStream.front()<<endl;
        tStream.pop_front();
        while_flag = 1;
        fin >> node; //)
        fin >> node; //Stmt
        Stmt();
        
        While_LL();
        
        while_flag = 0;
    }else if(node == "Block"){
        Block();
    }else if(node == "print"){ //print id ;
        Print();
        fin >> node; //;
    }
    return 0;
}
int Print(){
    fin >> node;//id
    fin >> node;//a
    char copy[20];
    string node_in;
    strcpy(copy,node.c_str());
    node_in=SymbolTable[FtableI(copy,nowscope)].Rname;
    
    if (if_else_flag||while_flag) {
        temp_expr=" %"+intToString(reg)+" = load "+typePtr[symbolType[node_in]]+" "+node_in+typeAlign[symbolType[node_in]];
        exprStream.push_back(temp_expr);
        reg++;
        if(symbolType[node_in]==0){
            temp_expr=" %"+intToString(reg)+" = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %"+intToString(reg-1)+")";
            exprStream.push_back(temp_expr); reg++;
        }else{
            temp_expr=" %"+intToString(reg)+" = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str1, i32 0, i32 0), double %"+intToString(reg-1)+")";
            exprStream.push_back(temp_expr); reg++;
        }
    }else{
        fout<<" %"<<reg<<" = load "<<typePtr[symbolType[node_in]]<<" "<<node_in<<typeAlign[symbolType[node_in]]<<endl;
        reg+=1;
        if(symbolType[node_in]==0){
            fout<<" %"<<reg<<" = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str, i32 0, i32 0), i32 %"<<reg-1<<")"<<endl;
            reg++;
        }else{
            fout<<" %"<<reg<<" = call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([3 x i8]* @.str1, i32 0, i32 0), double %"<<reg-1<<")"<<endl;
            reg++;
        }
    }
}
int Block(){
    int i, j, find = 0;
    //printf("Block\n");
    fin >> node; //{
    strcpy(Tree[1],node.c_str());
    nowscope*=10;
    for(i=0;i<9;i++)
    {
        find=0;
        nowscope+=1;
        for(j=0;j<=scoperecordindex;j++)
        {
            if(scoperecord[j]==nowscope)
            {
                find=1;
                break;
            }
        }
        if(find==0)
        {    find=0;
            scoperecord[scoperecordindex]=nowscope;
            scoperecordindex+=1;
            break;
        }
    }
    //printf("nowscope%d",nowscope);
    
    for(j=0;j<=scoperecordindex;j++)
    {
        //printf("scoperecord[%d]=%d\n",j,scoperecord[j]);
    }
    //printf("{");
    fin >> node; //VarDeclList
    strcpy(Tree[1],node.c_str());
    //printf("~~~~~~~~~\n");
    VarDeclList();
    fin >> node; //StmtList
    strcpy(Tree[1],node.c_str());
    
    StmtList();
    if (if_else_flag||while_flag) {
        labelStream.push_back(reg);
//        fout<<"===============label: "<<reg<<endl;
        reg++;
        exprStream.push_back(":)");
    }
    fin >> node; //}
    strcpy(Tree[1],node.c_str());
    //printf("}");
    nowscope/=10;
    return 0;
}
int VarDeclList(){
    char VarDeclList_[10][100];
    //printf("VarDeclList\n");
    fin >> node; //epsilon
    strcpy(Tree[1],node.c_str());
    {
        if(strcmp(Tree[1],"VarDecl")==0)
        {
            VarDecl( VarDeclList_);
            fin >> node; //VarDeclList
            strcpy(Tree[1],node.c_str());
            { //cout << "*****Tree[1] =" <<Tree[1] << endl;
                if(strcmp(Tree[1],"VarDeclList")==0)VarDeclList();
            }
        }
        if(strcmp(Tree[1],"epsilon")==0){//printf("epsilon\n");return 1;}
        }
    return 0;
    }
}
int StmtList(){
    //printf("StmtList\n");
    fin >> node; //Stmt
    Stmt();
    fin >> node; //StmtList'
    StmtListA();
    return 0;
}
int StmtListA(){
    //printf("StmtListpron\n");
    fin >> node; //epsilon
    if(node == "epsilon"){ //epsilon -> return
        return 0;
    }else if (node == "StmtList") {
        StmtList();
    }
    return 0;
}
int Expr(){
    fin >> node;
    if (node == "UnaryOp") { // UnaryOp Expr
        fin >> node; //!
        for (int i = 0; i < Op.size(); i++){
            if (node == Op[i])
                opStream.push_back(i);
            break;
        }
        fin >> node;
        Expr();
        UniExprLL();
    }else if(node == "num"){ // num Expr'
        fin >> node; //0
        int type_in;
        type_in = numType(node);
        if (type_in) { //is double
            char c[20];
            sprintf(c,"%.6e",atof(node.c_str()));
            string str(c);
            tStream.push_back(str);
            symbolType.insert(pair<string,int>(str,type_in));
        }else{
            tStream.push_back(node);
            symbolType.insert(pair<string,int>(node,type_in));
        }
        fin >> node;
        ExprA();
    }else if(node == "("){ // ( Expr ) Expr' ->(a+b)+c
        fin >> node;
        Expr();
    }else if(node == "id"){ // id ExprIdTail
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        fin >> node; //a
        string node_in;
        node_in = node;
        //cout <<"node_in:"<<node_in<<endl;
        char copy[20];
        strcpy(copy,node_in.c_str());
        node_in.assign(SymbolTable[FtableI(copy,nowscope)].Rname);
        tStream.push_back(node_in); //%a 還要考慮可能是全域變數
//    fout<<node_in;
//fout<<"id: "<<node_in<<endl;
        fin >> node;
        ExprIdTail();
    }
    return 0;
}
int ExprIdTail(){
    fin >> node;
    if (node == "Expr'") {
//fout<<"EXPRA";
        ExprA();
        return 0;
    }else if(node == "("){ // ( ExprList ) Expr' -> call function
        string functcall=tStream.back();
        char copy[20];
        functcall=functcall.substr(1);
        strcpy(copy,functcall.c_str());
        //cout<<copy<<endl;
        //cout<<FtableI(copy, nowscope)<<endl;
        //cout<<" %"<<reg<<" = call"<< (((strcmp(SymbolTable[FtableI(copy,nowscope)].Type,"int")==0))? " i32 ":" double ");
        
        //cout<<SymbolTable[FtableI(copy, nowscope)].Rname;
        //cout<<"()"<<endl;
        fout<<" %"<<reg<<" = call"<<  (((strcmp(SymbolTable[FtableI(copy,nowscope)].Type,"int")==0))?" i32 ":" double ");
        fout<<SymbolTable[FtableI(copy, nowscope)].Rname;
        fout<<"()"<<endl;
        reg+=1;
    tStream.pop_back();
        fin >> node;
        ExprList();
        fin >> node;
        fin >> node;
        ExprA();
        return 0;
    }else if(node == "["){ // [ Expr ] ExprArrayTail ->array calcu or assign
        string idid;
        idid=tStream.back(); //e
        tStream.pop_back();
        fin >> node; //Expr
        
        arraycheck=1;
        
        Expr();
        string result;
        string intdouble= symbolType[idid]?"double":"i32 ";
        int inpair=symbolType[idid]?1:0;
        char copy[20];
        string idid1=idid.substr(1);
        strcpy(copy,idid1.c_str());
        fout <<" %"<<reg<<"= getelementptr inbounds "<<"[";
        fout<< SymbolTable[FtableI(copy, nowscope)].array;
        fout<<  " x "<< intdouble <<"]* "<<idid<<","<<    intdouble<<"0,"<< intdouble <<tStream.back()<< endl;
        tStream.pop_back();
        result = "%"+intToString(reg);
        tStream.push_back(result);
        symbolType.insert(pair<string,int>(result, inpair));
        reg+=1;
        fin >> node; //]
        fin >> node; //ExprArrayTail
        ExprArrayTail();
        return 0;
    }else if(node == "="){ // = Expr ->assign
        //assign_flag = 1;
        assign_flag++;
        string t;
        t = tStream.back();  //assignt = a
        tStream.pop_back(); //empty
        assigntStream.push_back(t);
        fin >> node; //Expr
        Expr();
    }
}
int ExprA(){
    fin >> node;
    if(node == "epsilon"){ //epsilon -> return
        return 0;
    }else if (node == "BinOp") { // BinOp Expr: BinOp + t
        fin >> node;
        for (int i = 0; i < Op.size(); i++){
            if (node == Op[i]){
                opStream.push_back(i);
                break;
            }
        }
        fin >> node;
        Expr();
        return 0;
    }
}
int ExprArrayTail(){
    fin >> node;
    if (node == "Expr'") { // Expr' //array 運算
        ExprA();
        return 0;
    }else if(node == "="){ //= Expr
        array_left_flag = 1;
        assign_flag++;
        string t;
        t = tStream.back();  //assignt = a //array  賦值
        tStream.pop_back(); //empty
        assigntStream.push_back(t);
        
        fin >> node; //Expr
        Expr();
        return 0;
    }
}
int ExprList(){
    fin >> node;
    if(node == "epsilon"){ //epsilon -> return
        ;
    }else if(node == "ExprListTail") { // ExprListTail
        ExprListTail();
    }
    return 0;
}
int ExprListTail(){
    fin >> node;
    Expr();
    fin >> node;
    ExprListTailA();
    return 0;
}
int ExprListTailA(){
    fin >> node;
    if(node == "epsilon"){ //epsilon -> return
        ;
    }else if (node == ",") { // , ExprListTail
        fin >> node;
        ExprListTail();
    }
    return 0;
}
int num_calcu(string t1,string t2){//num num
    int n1_type, n2_type, op_index;
    string calcu_result;
    op_index = opStream.front();
    n1_type = numType(t1); //0:int,1:double
    n2_type = numType(t2);
    if ((n1_type==0)&&(n2_type==1)) {
        cout<<"warning(scope "<<nowscope<<") : "<<t1<<" int, "<<t2<<" double"<<endl;
    }
    if ((n1_type==1)&&(n2_type==0)) {
        cout<<"warning(scope "<<nowscope<<") : "<<t1<<" double, "<<t2<<" int"<<endl;
    }
    if (!(n1_type|n2_type)||((n1_type^n2_type)&&(!symbolType[assignt]))) { //int int
        int n1, n2, n_result;
        n1 = atoi(t1.c_str());
        n2 = atoi(t2.c_str());
        switch (op_index) {
            case 0: //+
                n_result = n1+n2;
                break;
            case 1: //-
                n_result = n1-n2;
                break;
            case 2: //*
                n_result = n1*n2;
                break;
            case 3: ///
                n_result = n1/n2;
                break;
            case 4: //==
                n_result = (n1 == n2); //1:equal, 0:not equal
                break;
            case 5: //!=
                n_result = (n1 != n2);
                break;
            case 6: //<
                n_result = (n1<n2);
                break;
            case 7: //<=
                n_result = (n1<=n2);
                break;
            case 8: //>
                n_result = (n1>n2);
                break;
            case 9: //>=
                n_result = (n1>=n2);
                break;
            case 10: //&&
                n_result = (n1&&n2);
                break;
            case 11: //||
                n_result = (n1||n2);
                break;
            default:
                break;
        }
        calcu_result = intToString(n_result);
        tStream.push_front(calcu_result);
        symbolType.insert(pair<string,int>(calcu_result,0));
        return 0;
    }else{
        double d1, d2, d_result;
        d1 = atof(t1.c_str());
        d2 = atof(t2.c_str());
        switch (op_index) {
            case 0: //+
                d_result = d1+d2;
                break;
            case 1: //-
                d_result = d1-d2;
                break;
            case 2: //*
                d_result = d1*d2;
                break;
            case 3: ///
                d_result = d1/d2;
                break;
            case 4: //==
                d_result = (d1 == d2); //1:equal, 0:not equal
                break;
            case 5: //!=
                d_result = (d1 != d2);
                break;
            case 6: //<
                d_result = (d1<d2);
                break;
            case 7: //<=
                d_result = (d1<=d2);
                break;
            case 8: //>
                d_result = (d1>d2);
                break;
            case 9: //>=
                d_result = (d1>=d2);
                break;
            case 10: //&&
                d_result = (d1&&d2);
                break;
            case 11: //||
                d_result = (d1||d2);
                break;
            default:
                break;
        }
        char d[20];
        sprintf(d,"%.6e",d_result);
        string str(d);
        calcu_result = str;
        tStream.push_front(calcu_result);
        symbolType.insert(pair<string,int>(calcu_result,1));
    }
    return 1;
}
int oneNum_oneReg_type_check(string t1, string t2){
    string result;
    char d[20];
    if (!(symbolType[t1]|symbolType[t2])) { //both int
        if (regORnum(t1)) { //t1 is reg, load t1
            tStream.push_front(t2);
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = load i32* "+t1+", align 4";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load i32* "<<t1<<", align 4"<<endl;
            }
            result = "%"+intToString(reg);
            tStream.push_front(result);
            symbolType.insert(pair<string,int>(result,0));
            reg++;
        }else{//t2 is reg, load t2
            if(if_else_flag||while_flag){
                temp_expr=" %"+intToString(reg)+" = load i32* "+t2+", align 4";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load i32* "<<t2<<", align 4"<<endl;
            }
            result = "%"+intToString(reg);
            tStream.push_front(result);
            symbolType.insert(pair<string,int>(result,0));
            reg++;
            tStream.push_front(t1);
        }
        return 0;
    }else{//one of them is double
        if (regORnum(t1)) { //t1 is reg, t2 is num
            if (!symbolType[t1]) { //t1 is int, load it, sitofp
                cout<<"warning(scope "<<nowscope<<") : temp int, "<<t2<<" double"<<endl;
                if (if_else_flag||while_flag) {
                    temp_expr=" %"+intToString(reg)+" = load i32* "+t1+", align 4";
                    exprStream.push_back(temp_expr);
                }else{
                    fout<<" %"<<reg<<" = load i32* "<<t1<<", align 4"<<endl;
                }
                reg++;
                if (if_else_flag||while_flag) {
                    temp_expr=" %"+intToString(reg)+" = sitofp i32 %"+intToString(reg-1)+" to double";
                    exprStream.push_back(temp_expr);
                }else{
                    fout<<" %"<<reg<<" = sitofp i32 %"<<reg-1<<" to double"<<endl;
                }
            }else{//t1 is double
                if (!numType(t2)) {
                    cout<<"warning(scope "<<nowscope<<") : temp double, "<<t2<<" int"<<endl;
                }
                if (if_else_flag||while_flag) {
                    temp_expr=" %"+intToString(reg)+" = load double* "+t1+", align 8";
                    exprStream.push_back(temp_expr);
                }else{
                    fout<<" %"<<reg<<" = load double* "<<t1<<", align 8"<<endl;
                }
            }
            result = "%"+intToString(reg);
            tStream.push_back(result);
            symbolType.insert(pair<string,int>(result,1));
            reg++;
            //t2 to 6e string
            sprintf(d,"%.6e",atof(t2.c_str()));
            string str(d);
            tStream.push_back(str);
            symbolType.insert(pair<string,int>(str,1));
        }else{ //t2 is reg
            //t1 to 6e string
            sprintf(d,"%.6e",atof(t1.c_str()));
            string str(d);
            tStream.push_back(str);
            symbolType.insert(pair<string,int>(str,1));
            if (!symbolType[t2]) {//t2 is int, load it, sitofp
                cout<<"warning(scope "<<nowscope<<") : "<<t1<<" double, temp int"<<endl;
                if (if_else_flag||while_flag) {
                    temp_expr=" %"+intToString(reg)+" = load i32* "+t2+", align 4";
                    exprStream.push_back(temp_expr);
                }else{
                    fout<<" %"<<reg<<" = load i32* "<<t2<<", align 4"<<endl;
                }
                reg++;
                if (if_else_flag||while_flag) {
                    temp_expr=" %"+intToString(reg)+" = sitofp i32 %"+intToString(reg-1)+" to double";
                    exprStream.push_back(temp_expr);
                }else{
                    fout<<" %"<<reg<<" = sitofp i32 %"<<reg-1<<" to double"<<endl;
                }
            }else{//t2 is double
                if (!numType(t1)) {
                    cout<<"warning(scope "<<nowscope<<") : "<<t1<<" int, temp double"<<endl;
                }
                if (if_else_flag||while_flag) {
                    temp_expr=" %"+intToString(reg)+" = load double* "+t2+", align 8";
                    exprStream.push_back(temp_expr);
                }else{
                    fout<<" %"<<reg<<" = load double* "<<t2<<", align 8"<<endl;
                }
            }
            result = "%"+intToString(reg);
            tStream.push_back(result);
            symbolType.insert(pair<string,int>(result,1));
            reg++;
        }
    }
    return 1;
}
int type_check(string t1,string t2)
{
    string result;
    if(symbolType[t1]&&(symbolType[t2]!=1)) //t1=1, t2=0
    {
        cout<<"warning(scope "<<nowscope<<") : "<<t1.substr(1)<<" double, "<<t2.substr(1)<<" int"<<endl;
        if (!isdigit(t2[1])) { //t2 need load
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = load "+typePtr[symbolType[t2]]+" "+t2+typeAlign[symbolType[t2]];
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load "<<typePtr[symbolType[t2]]<<" "<<t2<<typeAlign[symbolType[t2]]<<endl;
            }
            reg+=1;
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = sitofp i32 %"+intToString(reg-1)+" to double ";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = sitofp i32 %"<<(reg-1)<<" to double "<<endl;
            }
            result = "%"+intToString(reg);
//            if (!priority_flag) {
                tStream.push_front(result);
//            }else{
//                tStream[priority_i+1] = result;
//            }
            symbolType.insert(pair<string,int>(result,1));
            reg+=1;
        }else{ //t2 don't need load
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = sitofp i32 "+t2+" to double ";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = sitofp i32 "<<t2<<" to double "<<endl;
            }
            result = "%"+intToString(reg);
//            if (!priority_flag) {
                tStream.push_front(result);
//            }else{
//                tStream[priority_i+1] = result;
//            }
            symbolType.insert(pair<string,int>(result,1));
            reg+=1;
        }
        if (!isdigit(t1[1])) { //t1 need load
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = load double* "+t1+", align 8";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load double* "<<t1<<", align 8"<<endl;
            }
            result = "%"+intToString(reg);
//            if (!priority_flag) {
                tStream.push_front(result);
//            }else{
//                tStream[priority_i] = result;
//            }
            symbolType.insert(pair<string,int>(result,1));
            reg+=1;
        }else{//t1 don't need load
//            if (!priority_flag) {
                tStream.push_front(t1);
//            }else{
//                tStream[priority_i] = t1;
//            }
        }
        
        return 1;
    }
    if(symbolType[t2]&&(symbolType[t1]!=1)) //t1=0,t2=1
    {
        cout<<"warning(scope "<<nowscope<<") : "<<t1.substr(1)<<" int, "<<t2.substr(1)<<" double"<<endl;
        if (!isdigit(t2[1])) { //need load
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = load double* "+t2+", align 8";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load double* "<<t2<<", align 8"<<endl;
            }
            result = "%"+intToString(reg);
            tStream.push_front(result);
            symbolType.insert(pair<string,int>(result,1));
            reg+=1;
        }else{
            tStream.push_front(t2);
        }
        
        if (!isdigit(t1[1])) { //need load
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = load i32* "+t1+", align 4";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load i32* "<<t1<<", align 4"<<endl;
            }
            reg+=1;
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = sitofp i32 %"+intToString(reg-1)+" to double ";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = sitofp i32 %"<<(reg-1)<<" to double "<<endl;
            }
            result = "%"+intToString(reg);
            tStream.push_front(result);
            symbolType.insert(pair<string,int>(result,1));
            reg+=1;
        }else{
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = sitofp i32 "+t1+" to double ";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = sitofp i32 "<<t1<<" to double "<<endl;
            }
            result = "%"+intToString(reg);
            tStream.push_front(result);
            symbolType.insert(pair<string,int>(result,1));
            reg+=1;
        }
        
        
        
        return 1;
        
    }
    if(symbolType[t2]&&(symbolType[t1]))
    {
        if (isdigit(t2[1])) {//%num don't need load
            tStream.push_front(t2);
        }else{
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = load double* "+t2+", align 8";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load double* "<<t2<<", align 8"<<endl;
            }
            result = "%"+intToString(reg); //***c++11***
            tStream.push_front(result);
            symbolType.insert(pair<string,int>(result,1));
            reg+=1;
        }
        
        if (isdigit(t1[1])) {//%num don't need load
            tStream.push_front(t1);
        }else{
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = load double* "+t1+", align 8";
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load double* "<<t1<<", align 8"<<endl;;
            }
            result = "%"+intToString(reg);
            tStream.push_front(result);
            symbolType.insert(pair<string,int>(result,1));
            reg+=1;
        }
        return 1;
    }
    if(symbolType[t2]!=1&&(symbolType[t1])!=1) //int int
    {
        if (isdigit(t2[1])) {//%num don't need load
//            if (!priority_flag) {
                tStream.push_front(t2);
//            }else{
//                tStream[priority_i+1]=t2;
//            }
        }else{
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = load "+typePtr[symbolType[t2]]+" "+t2+typeAlign[symbolType[t2]];
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load "<<typePtr[symbolType[t2]]<<" "<<t2<<typeAlign[symbolType[t2]]<<endl;
            }
            result = "%"+intToString(reg);
//            if (!priority_flag) {
                tStream.push_front(result);
//            }else{
//                tStream[priority_i+1] = result;
//            }
            symbolType.insert(pair<string,int>(result,0));
            reg+=1;
        }
        if (isdigit(t1[1])) {
//            if (!priority_flag) {
                tStream.push_front(t1);
//            }else{
//                tStream[priority_i] = t1;
//            }
        }else{
            if (if_else_flag||while_flag) {
                temp_expr=" %"+intToString(reg)+" = load "+typePtr[symbolType[t1]]+" "+t1+typeAlign[symbolType[t1]];
                exprStream.push_back(temp_expr);
            }else{
                fout<<" %"<<reg<<" = load "<<typePtr[symbolType[t1]]<<" "<<t1<<typeAlign[symbolType[t1]]<<endl;
            }
            result = "%"+intToString(reg);
//            if (!priority_flag) {
                tStream.push_front(result);
//            }else{
//                tStream[priority_i] = result;
//            }
            symbolType.insert(pair<string,int>(result,0));
            reg+=1;
        }
        return 0;
    }
    return 0;
}
int numType(string numStr){
    if (numStr.find(".") == string::npos) {
        return 0;
    }else{
        return 1;
    }
}
int regORnum(string t){ //0: num, 1:reg
    if (isdigit(t[0])) {
        return 0;
    }else{
        return 1;
    }
}
string intToString(int a){
    char  c[10];
    sprintf(c,"%d",a);
    string str(c);
    return str;
}
string ftoi(string f){
    int dot = f.find(".");
    return f.substr(0,dot);
}
string itof(string i){
    //3.3->3.300000e+00
    char c[20];
    sprintf(c,"%.6e",atof(i.c_str()));
    string str(c);
    return str;
}
void construct_data(){ //symbol table
    /*
    symbolType["@x"]=0;
    symbolType["@main"]=0;
    symbolType["%a"]=0;
    symbolType["%b"]=0;
    symbolType["%c"]=1;
    symbolType["%d"]=1;
    symbolType["%e"]=0;
    symbolType["%f"]=0;
    symbolType["%g"]=0;
    symbolType["@func"]=0;
    symbolType["%test"]=0;
    
    isArray["@x"]=0;
    isArray["@main"]=0;
    isArray["%a"]=0;
    isArray["%b"]=0;
    isArray["%c"]=0;
    isArray["%d"]=0;
    isArray["%e"]=1;
    isArray["%f"]=1;
    isArray["%g"]=0;
    isArray["@func"]=0;
    isArray["%test"]=0;
    
    isFunction["@x"]=0;
    isFunction["@main"]=1;
    isFunction["%a"]=0;
    isFunction["%b"]=0;
    isFunction["%c"]=0;
    isFunction["%d"]=0;
    isFunction["%e"]=1;
    isFunction["%f"]=1;
    isFunction["%g"]=0;
    isFunction["@func"]=1;
    isFunction["%test"]=0;
     */
}
int Program(char Program_[10][100])
{
    //printf("Program\n");
    
    fin >> node;
    strcpy(Tree[1],node.c_str());
    if(strcmp(Tree[1],"DeclList")==0)
    {
        DeclList(Program_);
        
    }
    FILE *table;
    int i;
    table=fopen("table.txt","w");
    printf("scope  symbol     type     array     funct     para\n");
    fprintf(table,"scope  symbol     type     array     funct     para\n");
    
    for(i=0;i<50;i++)
    {
        if(strcmp(SymbolTable[i].Symbol,"")==0)break;
        printf("%3d     %5s     %7s     %3d     %3d         %d     %s\n",SymbolTable[i].scope,SymbolTable[i].Symbol,SymbolTable[i].Type,SymbolTable[i].array,SymbolTable[i].funct,SymbolTable[i].para,SymbolTable[i].Rname);
        fprintf(table,"%3d     %5s     %7s     %3d     %3d         %d     %s\n",SymbolTable[i].scope,SymbolTable[i].Symbol,SymbolTable[i].Type,SymbolTable[i].array,SymbolTable[i].funct,SymbolTable[i].para,SymbolTable[i].Rname);
    }
    int p;
    return 0;
}
int DeclList(char DeclList_[10][100])
{
    //printf("DeclList\n");
    fin >> node;
    strcpy(Tree[1],node.c_str());
    {
        if(strcmp(Tree[1],"DeclList'")==0)
        {
            DeclListpron(DeclList_);
            fin >> node;
            strcpy(Tree[1],node.c_str());
            {
                if(strcmp(Tree[1],"DeclList")==0)DeclList(DeclList_);
            }
        }
        if(strcmp(Tree[1],"epsilon")==0)
        {   ;
        }
    }
    return 0;
}
int DeclListpron(char DeclListpron_[10][100])
{
    //printf("DeclListpron\n");
    
    fin >> node;
    strcpy(Tree[1],node.c_str());
    {
        if(strcmp(Tree[1],"Type")==0)
        {
            Type(DeclListpron_);
            fin >> node;
            strcpy(Tree[1],node.c_str());
            {
                if(strcmp(Tree[1],"id")==0)
                {
                    //printf("id\n");
                    fin >> node;
                    strcpy(Tree[1],node.c_str());
                    strcpy(DeclListpron_[1],Tree[1]);
                    strcpy(functname,Tree[1]);
                    //printf("%s\n",Tree[1]);
                }
                fin >> node;
                strcpy(Tree[1],node.c_str());
                {
                    if(strcmp(Tree[1],"Decl")==0)
                    {
                        Decl(DeclListpron_);;
                        
                        
                    }
                }
            }
        }
    }
    return 0;
}
char fun_ret_type[20];
int Decl(char Decl_[10][100])
{
    strcpy(Decl_[3],"Decl");//stamp
    //printf("Decl\n");
    fin >> node;
    strcpy(Tree[1],node.c_str());
    {
        if(strcmp(Tree[1],"VarDecl'")==0)
        {
            VarDeclpron(Decl_);
        }
        if(strcmp(Tree[1],"FunDecl")==0)
        {
            ////////////////////////////////////////////////////函式宣告
            //symbolType["@x"]=0; 0int  1double
            // isArray["@x"]=0;  1
            // isFunction["@x"]=0;
            //string copychar;
            //copychar.assign();
            //symbolType["SymbolTable[STindex].Symbol"]=(strcmp(SymbolTable[STindex].Type,"double")==1);
            SymbolTable[STindex].array=0;
            SymbolTable[STindex].funct=1;
            SymbolTable[STindex].scope=1;
            strcpy(SymbolTable[STindex].Symbol,functname);
            strcpy(SymbolTable[STindex].Type,functtype);
            strcpy(fun_ret_type,functtype);
            
            SymbolTable[STindex].para=0;
            
            strcpy(SymbolTable[STindex].Rname,"@");
            strcat(SymbolTable[STindex].Rname,Decl_[1]);
            string copychar;
            copychar.assign(SymbolTable[STindex].Rname);
            symbolType[copychar]=(strcmp(SymbolTable[STindex].Type,"double")==0);
            isArray[copychar]=0;
            isFunction[copychar]=1;
            //printf("%sXDDDDDDDDDD\n",SymbolTable[STindex].Rname);
            fprintf(code,"define %s %s() #0 {\n",(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32"),SymbolTable[STindex].Rname);
            fout<<"define "<<(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32")<<SymbolTable[STindex].Rname<<" () #0 {"<<endl;
            if(strcmp(SymbolTable[STindex].Symbol,"main")==0)
            {
        reg=2;
                fout<<" %1 = alloca i32, align 4"<<endl;
                fout<<" store i32 0, i32* %1"<<endl;
                fprintf(code,"  %1 = alloca i32, align 4\n");
                fprintf(code," store i32 0, i32* %1\n");
            }
            STindex+=1;
            ////////////////////////////////////////////////////
            FunDecl(Decl_);
        }
    }
    return 0;
}
int VarDecl(char VarDecl_[10][100])
{
    //printf(" VarDecl\n");
    fin >> node;
    strcpy(Tree[1],node.c_str());
    {
        if(strcmp(Tree[1],"Type")==0)
        {
            Type(VarDecl_);
            fin >> node; //id
            strcpy(Tree[1],node.c_str());
            {
                if(strcmp(Tree[1],"id")==0)
                {
                    fin >> node; //d
                    strcpy(Tree[1],node.c_str());
                    //printf("id\n");
                    strcpy(VarDecl_[1],Tree[1]);
                    //printf("%s\n",Tree[1]);
                }
                fin >> node;
                strcpy(Tree[1],node.c_str());
                {
                    if(strcmp(Tree[1],"VarDecl'")==0)
                    {
                        VarDeclpron(VarDecl_);;
                        /////////////////////////////////////////////////////////////////////////////////判定
                        //內部變數宣告
                        if(strcmp(VarDecl_[2],"0")==0)
                        {
                            ;
                            SymbolTable[STindex].array=0;
                            SymbolTable[STindex].funct=0;
                            SymbolTable[STindex].scope=nowscope;
                            strcpy(SymbolTable[STindex].Symbol,VarDecl_[1]);
                            strcpy(SymbolTable[STindex].Type,VarDecl_[0]);
                            SymbolTable[STindex].para=0;
                            
                            strcpy(SymbolTable[STindex].Rname,"%");
                            strcat(SymbolTable[STindex].Rname,VarDecl_[1]);
                            string copychar;
                            copychar.assign(SymbolTable[STindex].Rname);
                            symbolType[copychar]=(strcmp(SymbolTable[STindex].Type,"double")==0);
                            isArray[copychar]=0;
                            isFunction[copychar]=0;
                            fprintf(code,"%s = alloca %s , align %s\n",SymbolTable[STindex].Rname,(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32"),(strcmp(SymbolTable[STindex].Type,"int")?"8":"4"));
                            fout<<" "<<SymbolTable[STindex].Rname<<" = alloca "<<(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32")<<" , align "<<(strcmp(SymbolTable[STindex].Type,"int")?"8":"4")<<endl;
                            //%yyy = alloca i32, align 4
                            //printf("declare functinvar:%s %s  array=%d funct=%dscope=%d\n",SymbolTable[STindex].Type,SymbolTable[STindex].Symbol,SymbolTable[STindex].array,SymbolTable[STindex].funct,SymbolTable[STindex].scope);
                            STindex+=1;
                        }
                        ////內部陣列宣告
                        else
                        {
                            ;
                            //sprintf(,"",);
                            ;
                            SymbolTable[STindex].array=atoi(VarDecl_[2]);
                            SymbolTable[STindex].funct=0;
                            SymbolTable[STindex].scope=nowscope;
                            strcpy(SymbolTable[STindex].Symbol,VarDecl_[1]);
                            strcpy(SymbolTable[STindex].Type,VarDecl_[0]);
                            SymbolTable[STindex].para=0;
                            
                            strcpy(SymbolTable[STindex].Rname,"%");
                            strcat(SymbolTable[STindex].Rname,VarDecl_[1]);
                            string copychar;
                            copychar.assign(SymbolTable[STindex].Rname);
                            symbolType[copychar]=(strcmp(SymbolTable[STindex].Type,"double")==0);
                            isArray[copychar]=1;
                            isFunction[copychar]=0;
                            fprintf(code,"%s = alloca [%d x %s], align %s\n",SymbolTable[STindex].Rname,SymbolTable[STindex].array,(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32"),(strcmp(SymbolTable[STindex].Type,"int")?"8":"4"));
                            fout<<" "<<SymbolTable[STindex].Rname<<" = alloca [ "<<SymbolTable[STindex].array<<" x "<<(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32")<<"], align "<<(strcmp(SymbolTable[STindex].Type,"int")?"8":"4") <<endl;
                            //printf("declarefunctinarray:%s %s [%d]; array=%d funct=%dscope=%d\n",SymbolTable[STindex].Type,SymbolTable[STindex].Symbol,SymbolTable[STindex].array,SymbolTable[STindex].array,SymbolTable[STindex].funct,SymbolTable[STindex].scope);
                            STindex+=1;
                        }
                        /////////////////////////////////////////////////////////////////////////////////判定
                    }
                    //printf("a");
                }
                //printf("b");
            }
            //printf("c");
        }
    }
    //printf("d");
    //printf("tree1:%s\n",Tree[1]);
    return 0;
}
int VarDeclpron(char VarDeclpron_[10][100])
{
    //printf("VarDeclpron\n");
    // while(fscanf(tree,"%d%s",Tree[0],Tree[1])!=EOF)
    fin >> node;
    strcpy(Tree[1],node.c_str());
    {
        if(strcmp(Tree[1],";")==0)
        {
            if((strcmp(VarDeclpron_[3],"Decl")==0)&&(nowscope==1))
            {
                SymbolTable[STindex].array=0;
                //外部變數宣告
                SymbolTable[STindex].funct=0;
                SymbolTable[STindex].scope=1;
                strcpy(SymbolTable[STindex].Symbol,VarDeclpron_[1]);
                strcpy(SymbolTable[STindex].Type,VarDeclpron_[0]);
                SymbolTable[STindex].para=0;
                
                strcpy(SymbolTable[STindex].Rname,"@");
                strcat(SymbolTable[STindex].Rname,VarDeclpron_[1]);
                string copychar;
                copychar.assign(SymbolTable[STindex].Rname);
                symbolType[copychar]=(strcmp(SymbolTable[STindex].Type,"double")==0);
                isArray[copychar]=0;
                isFunction[copychar]=0;
                fprintf(code,"%s = common global %s %s, align %s\n",SymbolTable[STindex].Rname,(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32"),(strcmp(SymbolTable[STindex].Type,"int")?"0.000000e+00":"0"),(strcmp(SymbolTable[STindex].Type,"int")?"8":"4"));
                fout<<SymbolTable[STindex].Rname<<" = common global "<<(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32")<<" "<<(strcmp(SymbolTable[STindex].Type,"int")?"0.000000e+00":"0")<<", align "<<(strcmp(SymbolTable[STindex].Type,"int")?"8":"4")<<endl;
                fout<<endl;
                //printf("declare functoutvar:%s %s  ;array=%d funct=%dscope=%d\n",SymbolTable[STindex].Type,SymbolTable[STindex].Symbol,SymbolTable[STindex].array,SymbolTable[STindex].funct,SymbolTable[STindex].scope);
                
                STindex+=1;
                strcpy(VarDeclpron_[3],"\0");
                ;
                
            }
            strcpy(VarDeclpron_[2],"0");
            //printf(";\n");
        }
        if(strcmp(Tree[1],"[")==0)
        {
            //     while(fscanf(tree,"%d%s",Tree[0],Tree[1])!=EOF)
            fin >> node;
            strcpy(Tree[1],node.c_str());
            {
                if(strcmp(Tree[1],"num")==0)
                {
                    // fscanf(tree,"%d%s",Tree[0],Tree[1]);//18
                    fin >> node;
                    strcpy(Tree[1],node.c_str());
                    strcpy(VarDeclpron_[2],Tree[1]);
                    if((strcmp(VarDeclpron_[3],"Decl")==0)&&(nowscope==1))
                    {
                        //外部陣列宣告
                        
                        SymbolTable[STindex].array=atoi(VarDeclpron_[2]);
                        SymbolTable[STindex].funct=0;
                        SymbolTable[STindex].scope=1;
                        strcpy(SymbolTable[STindex].Symbol,VarDeclpron_[1]);
                        strcpy(SymbolTable[STindex].Type,VarDeclpron_[0]);
                        SymbolTable[STindex].para=0;
                        
                        strcpy(SymbolTable[STindex].Rname,"@");
                        strcat(SymbolTable[STindex].Rname,VarDeclpron_[1]);
                        string copychar;
                        copychar.assign(SymbolTable[STindex].Rname);
                        symbolType[copychar]=(strcmp(SymbolTable[STindex].Type,"double")==0);
                        isArray[copychar]=1;
                        isFunction[copychar]=0;
                        fout<<SymbolTable[STindex].Rname<<" = common global ["<<SymbolTable[STindex].array<<" x "<<(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32")<<"] zeroinitializer, align "<<(strcmp(SymbolTable[STindex].Type,"int")?"8":"4")<<endl;
                        fprintf(code,"%s = common global [%d x %s] zeroinitializer, align %s\n",SymbolTable[STindex].Rname,SymbolTable[STindex].array,(strcmp(SymbolTable[STindex].Type,"int")?"double":"i32"),(strcmp(SymbolTable[STindex].Type,"int")?"8":"4"));
                        //printf("declarearrayout:%s %s [%d]; array=%d funct=%dscope=%d\n",SymbolTable[STindex].Type,SymbolTable[STindex].Symbol,SymbolTable[STindex].array,SymbolTable[STindex].array,SymbolTable[STindex].funct,SymbolTable[STindex].scope);
                        
                        STindex+=1;
                        strcpy(VarDeclpron_[3],"\0");
                        ;
                        
                    }
                    fin >> node;
                    strcpy(Tree[1],node.c_str());
                    //                    fscanf(tree,"%d%s",Tree[0],Tree[1]);//]
                    //printf("tree1invardeclpron%s\n",Tree[1]);
                    // fscanf(tree,"%d%s",Tree[0],Tree[1]);
                    fin >> node;
                    strcpy(Tree[1],node.c_str());
                    //printf("QAQ%s\n",Tree[1]);
                    
                }
                //  break;
            }
            ;
        }
        
        
        //      break;
        
    }
    return 0;
}
int FunDecl(char FunDecl_[10][100])
{
    strcpy(FunDecl_[2],"65500");
    //printf("FunDecl\n");
    //    while(fscanf(tree,"%d%s",Tree[0],Tree[1])!=EOF)
    fin >> node;
    strcpy(Tree[1],node.c_str());
    {
        if(strcmp(Tree[1],"(")==0)
        {
            //      fscanf(tree,"%d%s",Tree[0],Tree[1]);
            fin >> node;
            strcpy(Tree[1],node.c_str());
            if(strcmp(Tree[1],"ParamDeclList")==0)
            {
                ParamDeclList(FunDecl_);
                ;////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////ParamDeclList
            }
            //       fscanf(tree,"%d%s",Tree[0],Tree[1]);
            fin >> node;
            strcpy(Tree[1],node.c_str());
            if(strcmp(Tree[1],")")==0){;}
            //        fscanf(tree,"%d%s",Tree[0],Tree[1]);
            fin >> node;
            strcpy(Tree[1],node.c_str());
            if(strcmp(Tree[1],"Block")==0)
            {
                //printf("block\n");
                Block();
                /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////Block
                //cout<<"ret "<<((strcmp(fun_ret_type,"double")==0)?" double ":" i32 ");////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
                //cout<< tStream.back()<<endl;
                //cout<< "XDXDXDXD"<<fun_ret_type<<endl;
//                fout<<" ret "<<((strcmp(fun_ret_type,"double")==0)?" double ":" i32 ");////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                fout<< tStream.back()<<endl;
                // tStream.pop_back();
                fout<<"}"<<endl;
                fout<<endl;
            }
            ;
        }
        
        
        //   break;
        
    }
    
    return 0;
}
int FtableI(char id[100],int nowscopel)
{
    // SymbolTable[i]
    //    int scope;
    //    char Symbol[100];
    //    char Type[10];
    //    int array;
    //    int  funct;
    //    int para;
    //    char Rname[15];
    int i;
    int find;
    int k;
    for(;nowscopel>0;){
        for(i=0;i<50;i++)
        {
            if(strcmp(SymbolTable[i].Symbol,"")==0){//printf("break");break;
            }
            if(strcmp(SymbolTable[i].Symbol,id)==0)
            {
                k=i;
                find+=1;
                if(nowscopel==SymbolTable[i].scope)return i;
            }
            
        }
        if(find==0)break;
        nowscopel=(nowscopel/10);
    }
    
    if(find==0)return 100;
}
int Type(char Type_[10][100])
{
    fin >> node; //double
    strcpy(Tree[1],node.c_str());
    //printf("Type\n");
    strcpy(Type_[0],Tree[1]);
    strcpy(functtype,Tree[1]);
    
    //printf("%s\n",Tree[1]);
    return 0;
}
int ParamDeclList(char ParamDeclList_[10][100])
{
    //printf("ParamDeclList\n");
    // while(fscanf(tree,"%d%s",Tree[0],Tree[1])!=EOF)
    fin >> node;
    strcpy(Tree[1],node.c_str());
    {
        
        //    printf("%s%s\n",Tree[0],Tree[1]);
        if(strcmp(Tree[1],"ParamDeclListTail")==0)
        {
            ParamDeclListTail( ParamDeclList_);
            
            //     break;
        }
        if(strcmp(Tree[1],"epsilon")==0){
            ;    //break;
        }
    }
    return 0;
}
int ParamDeclListTail(char ParamDeclListTail_[10][100])
{
    //printf("ParamDeclListTail\n");
    //   while(fscanf(tree,"%d%s",Tree[0],Tree[1])!=EOF)
    fin >> node;
    strcpy(Tree[1],node.c_str());
    {
        
        //    printf("%s%s\n",Tree[0],Tree[1]);
        if(strcmp(Tree[1],"ParamDecl")==0)
        {
            ParamDecl( ParamDeclListTail_);
            //    fscanf(tree,"%d%s",Tree[0],Tree[1]);
            fin >> node;
            strcpy(Tree[1],node.c_str());
            ParamDeclListTailpron( ParamDeclListTail_);
            //  break;
        }
        //if(strcmp(Tree[1],"epsilon")==0){break;}
    }
    return 0;
}
int ParamDeclListTailpron(char ParamDeclListTailpron_[10][100])
{
    //printf("ParamDeclListTailpron\n");
    //  fscanf(tree,"%d%s",Tree[0],Tree[1]);
    fin >> node;
    strcpy(Tree[1],node.c_str());
    if(strcmp(Tree[1],"epsilon")==0)
    {
        //printf("epsilon\n");
        return 0;
    }
    else
    {
        //printf(",");
        fin >> node;
        strcpy(Tree[1],node.c_str());
        //   fscanf(tree,"%d%s",Tree[0],Tree[1]);
        ParamDeclListTail(ParamDeclListTailpron_);
    }
    //Type( ParamDecl_);
    return 0;
}
int ParamDecl(char ParamDecl_[10][100])
{
    //printf("ParamDecl\n");
    //    fscanf(tree,"%d%s",Tree[0],Tree[1]);
    fin >> node;
    strcpy(Tree[1],node.c_str());
    Type( ParamDecl_);
    //fscanf(tree,"%d%s",Tree[0],Tree[1]);
    fin >> node;
    strcpy(Tree[1],node.c_str());    
    //printf("%s\n",Tree[1]);
    fin >> node;
    strcpy(Tree[1],node.c_str());
    //    fscanf(tree,"%d%s",Tree[0],Tree[1]);
    //printf("%s\n",Tree[1]);
    fin >> node;
    strcpy(Tree[1],node.c_str());
    //    fscanf(tree,"%d%s",Tree[0],Tree[1]);
    ParamDeclpron(ParamDecl_);
    return 0;
}
int ParamDeclpron(char ParamDeclpron_[10][100])
{
    
    //printf("ParamDeclpron\n");
    fin >> node;
    strcpy(Tree[1],node.c_str());
    // fscanf(tree,"%d%s",Tree[0],Tree[1]);
    ////printf("%sXDXDXD",Tree[1]);
    
    if(strcmp(Tree[1],"epsilon")==0)
    {
        //printf("epsilon\n");
        return 0;
    }
    //printf("[");
    fin >> node;
    strcpy(Tree[1],node.c_str());
    //   fscanf(tree,"%d%s",Tree[0],Tree[1]);
    //printf("]");
    return 0;
}