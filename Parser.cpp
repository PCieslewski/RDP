#include "Parser.h"

TreeNode* Parser :: getAst(string path){
	
	lex.open(path);
	nextToken = lex.getNextToken();
	cout << nextToken->toString() << endl;
	E();
	lex.close();
	
	cout << "Size of treeStack: " << treeStack.size() << endl;
	
	TreeNode* ast = treeStack.top();
	treeStack.pop();
	return ast;
	
}

void Parser :: readToken(string value){
	if(nextToken->valueIs(value)){
		delete nextToken;
		if(lex.hasNextToken){
			nextToken = lex.getNextToken();
			cout << nextToken->toString() << endl;
		}
		else{
			cout << "Parser ran out of tokens." << endl;
			exit(EXIT_FAILURE);
		}
	}
	else{
		cout << "Parsing error. Expecting: " << value << " Received: " << nextToken->value << endl;
		exit(EXIT_FAILURE);
	}
}

void Parser :: readTokenByType(string type){
	
	if(nextToken->typeIs(type)){
		delete nextToken;
		if(lex.hasNextToken){
			nextToken = lex.getNextToken();
			cout << nextToken->toString() << endl;
		}
		else{
			cout << "No more tokens for parser." << endl;
			exit(EXIT_FAILURE);
		}
	}
	else{
		cout << "Parsing error. Expecting: " << type << " Recieved: " << nextToken->type << endl;
		exit(EXIT_FAILURE);
	}
}
	   
	   
void Parser :: buildTree(string value, int numChildren) {
	TreeNode* tn = new TreeNode(value);
	for(int i = 0; i<numChildren; i++){
		tn->addChild(treeStack.top());
		treeStack.pop();
	}
	treeStack.push(tn);
}

void Parser :: E(){
	if(nextToken->valueIs("let")){
		readToken("let");
		D();
		readToken("in");
		E();
		buildTree("let",2);
	}
	else if(nextToken->valueIs("fn")){
		readToken("fn");
		int n = 0;
		do{
			Vb();
			n++;
		}
		while(nextToken->valueIs("(") | nextToken->typeIs("Identifier")); //I dont like this.
		readToken(".");
		E();
		buildTree("lambda", n+1);
	}
	else{
		Ew();
	}
}

void Parser :: Ew(){
	T();
	if(nextToken->valueIs("where")){
		readToken("where");
		Dr();
		buildTree("where", 2);
	}
}

void Parser :: T(){
	Ta();
	if(nextToken->valueIs(",")){
		int n = 0;
		while(nextToken->valueIs(",")){
			readToken(",");
			Ta();
			n++;
		}
		buildTree("tau", n+1);
	}
}

void Parser :: Ta(){
	Tc();
	while(nextToken->valueIs("aug")){
		readToken("aug");
		Tc();
		buildTree("aug",2);
	}
}

void Parser :: Tc(){
	B();
	if(nextToken->valueIs("->")){
		readToken("->");
		Tc();
		readToken("|");
		Tc();
		buildTree("->",3);
	}
}

void Parser :: B(){
	Bt();
	while(nextToken->valueIs("or")){
		readToken("or");
		Bt();
		buildTree("or", 2);
	}
}

void Parser :: Bt(){
	Bs();
	while(nextToken->valueIs("&")){
		readToken("&");
		Bs();
		buildTree("&",2);
	}
}

void Parser :: Bs(){
	if(nextToken->valueIs("not")){
		readToken("not");
		Bp();
		buildTree("not",1);
	}
	else{
		Bp();	
	}
}

void Parser :: Bp(){
	A();
	if(nextToken->valueIs("gr")){
		readToken("gr");
		A();
		buildTree("gr",2);
	}
	else if(nextToken->valueIs(">")){
		readToken(">");
		A();
		buildTree("gr",2);
	}
	else if(nextToken->valueIs("ge")){
		readToken("ge");
		A();
		buildTree("ge",2);
	}
	else if(nextToken->valueIs(">=")){
		readToken(">=");
		A();
		buildTree("ge",2);
	}
	else if(nextToken->valueIs("ls")){
		readToken("ls");
		A();
		buildTree("ls",2);
	}
	else if(nextToken->valueIs("<")){
		readToken("<");
		A();
		buildTree("ls",2);
	}
	else if(nextToken->valueIs("le")){
		readToken("le");
		A();
		buildTree("le",2);
	}
	else if(nextToken->valueIs("<=")){
		readToken("<=");
		A();
		buildTree("le",2);
	}
	else if(nextToken->valueIs("eq")){
		readToken("eq");
		A();
		buildTree("eq",2);
	}
	else if(nextToken->valueIs("ne")){
		readToken("ne");
		A();
		buildTree("ne",2);
	}
}

void Parser :: A(){
	
	if(nextToken->valueIs("+")){
		readToken("+");
		At();
	}
	else if(nextToken->valueIs("-")){
		readToken("-");
		buildTree("neg",1);
	}
	else{
		At();
	}
	
	while(nextToken->valueIs("+") | nextToken->valueIs("-")){
		if(nextToken->valueIs("+")){
			readToken("+");
			At();
			buildTree("+",2);
		}
		else if(nextToken->valueIs("-")){
			readToken("-");
			At();
			buildTree("-",2);
		}
	}
	
}

void Parser :: At(){
	Af();
	while(nextToken->valueIs("*") | nextToken->valueIs("/")){
		if(nextToken->valueIs("*")){
			readToken("*");
			Af();
			buildTree("*",2);
		}
		else if(nextToken->valueIs("/")){
			readToken("/");
			Af();
			buildTree("/",2);
		}
	}
}

void Parser :: Af(){
	Ap();
	if(nextToken->valueIs("**")){
		readToken("**");
		Af();
		buildTree("**",2);
	}
}

void Parser :: Ap(){
	R();	
	while(nextToken->valueIs("@")){
		readToken("@");
		buildTree(nextToken->value,0);
		readTokenByType("Identifier");
		R();
		buildTree("@",3);
	}
}

void Parser :: R(){
	Rn();
	
	while(nextToken->typeIs("Identifier") |
		  nextToken->typeIs("Integer") | 
		  nextToken->typeIs("String") |
		  nextToken->valueIs("true") |
		  nextToken->valueIs("false") |
		  nextToken->valueIs("nil") |
		  nextToken->valueIs("(") |
		  nextToken->valueIs("dummy")){
		
		Rn();	
		buildTree("gamma",2);
	}
	
}

void Parser :: Rn(){
	if(nextToken->typeIs("Identifier")){
		buildTree(nextToken->value,0);
		readTokenByType("Identifier");
	}
	else if(nextToken->typeIs("Integer")){
		buildTree(nextToken->value,0);
		readTokenByType("Integer");
	}
	else if(nextToken->typeIs("String")){
		buildTree(nextToken->value,0);
		readTokenByType("String");
	}
	else if(nextToken->valueIs("true")){
		buildTree(nextToken->value,0);
		readToken("true");
	}
	else if(nextToken->valueIs("false")){
		buildTree(nextToken->value,0);
		readToken("false");
	}
	else if(nextToken->valueIs("nil")){
		buildTree(nextToken->value,0);
		readToken("nil");
	}
	else if(nextToken->valueIs("(")){
		readToken("(");
		E();
		readToken(")");
	}
	else if(nextToken->valueIs("dummy")){
		buildTree(nextToken->value,0);
		readToken("dummy");
	}
}

void Parser :: D(){
	Da();
	if(nextToken->valueIs("within")){
		readToken("within");
		D();
		buildTree("within",2);
	}
}

void Parser :: Da(){
	Dr();
	if(nextToken->valueIs("and")){
		int n = 0;
		while(nextToken->valueIs("and")){
			readToken("and");
			Dr();
			n++;
		}
		buildTree("and", n+1);
	}
}

void Parser :: Dr(){
	if(nextToken->valueIs("rec")){
		readToken("rec");
		Db();
		buildTree("rec",1);
	}
	else{
		Db();	
	}
}

void Parser :: Db(){
	if(nextToken->typeIs("Identifier")){
		buildTree(nextToken->value,0);
		readTokenByType("Identifier");
		
		if(nextToken->valueIs(",")){
			//This is the Vl() case;
			while(nextToken->valueIs(",")){
				readToken(",");
				buildTree(nextToken->value,0);
				readTokenByType("Identifier");
				buildTree(",",2);
			}
		}
		
		if(nextToken->valueIs("=")){
			readToken("=");
			E();
			buildTree("=",2);
		}
		else{
			int n = 0;
			do{
				Vb();
				n++;
			}
			while(nextToken->valueIs("(") | nextToken->typeIs("Identifier"));
			buildTree("fcn_form",n+2);
		}
	}
	else{
		readToken("(");
		D();
		readToken(")");
	}
}

void Parser :: Vb(){
	if(nextToken->typeIs("Identifier")){
		buildTree(nextToken->value,0);
		readTokenByType("Identifier");
	}
	else{
		readToken("(");
		if(nextToken->valueIs(")")){
			readToken(")");
			buildTree("()",0);
		}
		else{
			Vl();
			readToken(")");
		}
	}
}

void Parser :: Vl(){
	buildTree(nextToken->value,0);
	readTokenByType("Identifier");
	while(nextToken->valueIs(",")){
		readToken(",");
		buildTree(nextToken->value,0);
		readTokenByType("Identifier");
		buildTree(",",2);
	}
}