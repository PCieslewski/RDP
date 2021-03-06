#include "Parser.h"

//This function returns the a pointer to a tree node that is the
//root of the AST.
TreeNode* Parser :: getAst(string path){
	
	lex.open(path);
	nextToken = lex.getNextToken();
	//cout << nextToken->toString() << endl;
	E();
	lex.close();
	
	//cout << "Size of treeStack: " << treeStack.size() << endl;
	
	TreeNode* ast = treeStack.top();
	treeStack.pop();
	return ast;
	
}

//Confirms that a token is of the given value and deletes it.
void Parser :: readToken(string value){
	if(nextToken->valueIs(value)){
		delete nextToken;
		if(lex.hasNextToken){
			nextToken = lex.getNextToken();
			//cout << nextToken->toString() << endl;
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

//Confirms that a token is of a certain type and deletes it.
//For example, string or identifier.
void Parser :: readTokenByType(string type){
	
	if(nextToken->typeIs(type)){
		delete nextToken;
		if(lex.hasNextToken){
			nextToken = lex.getNextToken();
			//cout << nextToken->toString() << endl;
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
	   
//Pops num children off of the tree stack, creates a new treenode with
//the value, value.
void Parser :: buildTree(string value, int numChildren, string type, string raw) {
	TreeNode* tn = new TreeNode(value, type, raw);
	for(int i = 0; i<numChildren; i++){
		tn->addChild(treeStack.top());
		treeStack.pop();
	}
	treeStack.push(tn);
}

void Parser :: buildTree(string value, int numChildren) {
	TreeNode* tn = new TreeNode(value, value, value);
	for(int i = 0; i<numChildren; i++){
		tn->addChild(treeStack.top());
		treeStack.pop();
	}
	treeStack.push(tn);
}

/*
All of the following function are functions to used to process the non terminal
expressions of the grammar.
*/

void Parser :: E(){
	if(nextToken->valueIs("let")){
		readToken("let");
		D();
		readToken("in");
		E();
		buildTree("let", 2);
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
		buildTree("aug", 2, "Binop", "aug");
	}
}

void Parser :: Tc(){
	B();
	if(nextToken->valueIs("->")){
		readToken("->");
		Tc();
		readToken("|");
		Tc();
		buildTree("->", 3);
	}
}

void Parser :: B(){
	Bt();
	while(nextToken->valueIs("or")){
		readToken("or");
		Bt();
		buildTree("or", 2, "Binop", "or");
	}
}

void Parser :: Bt(){
	Bs();
	while(nextToken->valueIs("&")){
		readToken("&");
		Bs();
		buildTree("&", 2, "Binop", "&");
	}
}

void Parser :: Bs(){
	if(nextToken->valueIs("not")){
		readToken("not");
		Bp();
		buildTree("not", 1, "Unop", "not");
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
		buildTree("gr", 2, "Binop", "gr");
	}
	else if(nextToken->valueIs(">")){
		readToken(">");
		A();
		buildTree("gr", 2, "Binop", "gr");
	}
	else if(nextToken->valueIs("ge")){
		readToken("ge");
		A();
		buildTree("ge", 2, "Binop", "ge");
	}
	else if(nextToken->valueIs(">=")){
		readToken(">=");
		A();
		buildTree("ge", 2, "Binop", "ge");
	}
	else if(nextToken->valueIs("ls")){
		readToken("ls");
		A();
		buildTree("ls", 2, "Binop", "ls");
	}
	else if(nextToken->valueIs("<")){
		readToken("<");
		A();
		buildTree("ls", 2, "Binop", "ls");
	}
	else if(nextToken->valueIs("le")){
		readToken("le");
		A();
		buildTree("le", 2, "Binop", "le");
	}
	else if(nextToken->valueIs("<=")){
		readToken("<=");
		A();
		buildTree("le", 2, "Binop", "le");
	}
	else if(nextToken->valueIs("eq")){
		readToken("eq");
		A();
		buildTree("eq", 2, "Binop", "eq");
	}
	else if(nextToken->valueIs("ne")){
		readToken("ne");
		A();
		buildTree("ne", 2, "Binop", "ne");
	}
}

void Parser :: A(){
	
	if(nextToken->valueIs("+")){
		readToken("+");
		At();
	}
	else if(nextToken->valueIs("-")){
		readToken("-");
		At();
		buildTree("neg", 1, "Unop", "neg");
	}
	else{
		At();
	}
	
	while(nextToken->valueIs("+") | nextToken->valueIs("-")){
		if(nextToken->valueIs("+")){
			readToken("+");
			At();
			buildTree("+", 2, "Binop", "+");
		}
		else if(nextToken->valueIs("-")){
			readToken("-");
			At();
			buildTree("-", 2, "Binop", "-");
		}
	}
	
}

void Parser :: At(){
	Af();
	while(nextToken->valueIs("*") | nextToken->valueIs("/")){
		if(nextToken->valueIs("*")){
			readToken("*");
			Af();
			buildTree("*", 2, "Binop", "*");
		}
		else if(nextToken->valueIs("/")){
			readToken("/");
			Af();
			buildTree("/", 2, "Binop", "/");
		}
	}
}

void Parser :: Af(){
	Ap();
	if(nextToken->valueIs("**")){
		readToken("**");
		Af();
		buildTree("**", 2, "Binop", "**");
	}
}

void Parser :: Ap(){
	R();	
	while(nextToken->valueIs("@")){
		readToken("@");
		buildTree(nextToken->value, 0, "Identifier", nextToken->raw);
		readTokenByType("Identifier");
		R();
		buildTree("@", 3);
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
		buildTree("gamma", 2);
	}
	
}

void Parser :: Rn(){
	if(nextToken->typeIs("Identifier")){
		buildTree(nextToken->value,0,"Identifier",nextToken->raw);
		readTokenByType("Identifier");
	}
	else if(nextToken->typeIs("Integer")){
		buildTree(nextToken->value,0,"Integer",nextToken->raw);
		readTokenByType("Integer");
	}
	else if(nextToken->typeIs("String")){
		buildTree(nextToken->value, 0, "String", nextToken->raw);
		readTokenByType("String");
	}
	else if(nextToken->valueIs("true")){
		buildTree("<" + nextToken->value + ">", 0,"Boolean", "true");
		readToken("true");
	}
	else if(nextToken->valueIs("false")){
		buildTree("<" + nextToken->value + ">", 0, "Boolean", "false");
		readToken("false");
	}
	else if(nextToken->valueIs("nil")){
		//For some unknown reason, rpal puts a <> around nil...
		buildTree("<" + nextToken->value + ">", 0, "nil", "nil");
		readToken("nil");
	}
	else if(nextToken->valueIs("(")){
		readToken("(");
		E();
		readToken(")");
	}
	else if(nextToken->valueIs("dummy")){
		buildTree("<" + nextToken->value + ">", 0, "dummy", "dummy");
		readToken("dummy");
	}
}

void Parser :: D(){
	Da();
	if(nextToken->valueIs("within")){
		readToken("within");
		D();
		buildTree("within", 2);
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
		buildTree(nextToken->value, 0, "Identifier", nextToken->raw);
		readTokenByType("Identifier");
		
		if(nextToken->valueIs(",")){
			//This is the Vl() case;
			int n = 0;
			while(nextToken->valueIs(",")){
				readToken(",");
				buildTree(nextToken->value, 0, "Identifier", nextToken->raw);
				readTokenByType("Identifier");
				n++;
				//buildTree(",",2);
			}
			buildTree(",",n+1);
		}
		
		if(nextToken->valueIs("=")){
			readToken("=");
			E();
			buildTree("=", 2);
		}
		else{
			int n = 0;
			do{
				Vb();
				n++;
			}
			while(nextToken->valueIs("(") | nextToken->typeIs("Identifier"));
			readToken("=");
			E();
			buildTree("function_form",n+2);
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
		buildTree(nextToken->value, 0, "Identifier", nextToken->raw);
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
	buildTree(nextToken->value, 0, "Identifier", nextToken->raw);
	readTokenByType("Identifier");
	
	if(nextToken->valueIs(",")){
		int n = 0;
		while(nextToken->valueIs(",")){
			readToken(",");
			buildTree(nextToken->value, 0, "Identifier", nextToken->raw);
			readTokenByType("Identifier");
			n++;
			//buildTree(",",2);
		}
		buildTree(",",n+1);
	}
}