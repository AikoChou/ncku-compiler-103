int a ; 
int main ( ) {
	int b ;
	int c  ;
	a  =  0 ;
	b =  1 ;
	c  =  a + b ;
	return 0 ;
}

maintain a token list

lltable(layer, nonterminal, token) = productions
for(this productions's each node){
    node is terminal: 是否等於token => same => next token
    node is nonterminal: 查表(layer++, nonterminal, token)
}

    int layer = 0;