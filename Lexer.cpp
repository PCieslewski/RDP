#include "Lexer.h"

Lexer :: Lexer(){
	hasNext = false;
	hasNextToken = false;
}

void Lexer :: open(string path){
	ifs.open(path.c_str());
	hasNext = !(ifs.peek() == EOF);
	hasNextToken = true;
}

void Lexer :: close(){
	hasNext = false;
	hasNextToken = false;
	ifs.close();	
}

char Lexer :: getNextChar(){
	char temp;
	ifs.get(temp);
	hasNext = !(ifs.peek() == EOF);
	return temp;
}

void Lexer :: test(){
	cout << "Test" << endl;	
}

//Main function that returns the next token of the input file.
Token* Lexer :: getNextToken(){
	char a, b;
	//bool t = true;
	while(hasNext){
		
		//Check if there is a // which indicates a comment.
		if(upcomingComment()){
			readComment();
		}
		
		//Check if the character is alphabetical.
		else if(upcomingIdentifier()){
			return getIdentifier();
		}
		
		//Check if the character is numberic
		else if(upcomingInteger()){
			return getInteger();
		}
		
		//Check if the next character is a punction.
		else if(upcomingPunction()){
			return getPunction();
		}
		
		//Check if the character is an operator
		else if(upcomingOperator()){
			return getOperator();
		}
		
		//Check if the next character begins a string
		else if(upcomingString()){
			return getString();
		}
		
		//Throw out the character
		else{
			getNextChar();
		}
		
	}
	
	hasNextToken = false;
	return new Token("EOF", "EOF");
	
}

Token* Lexer :: getIdentifier(){
	string type = "Identifier";
	string value = "";
	
	while(hasNext){
		char a = getNextChar();
		if(isalpha(a) | isdigit(a) | (a=='_')){
			value = value + a;
		}
		else{
			putBackChar(a);
			break;
		}
	}
	
	if(
	(!(value.compare("let"))) |
	(!(value.compare("in"))) |
	(!(value.compare("within"))) |
	(!(value.compare("or"))) |
	(!(value.compare("and"))) |
	(!(value.compare("fn"))) |
	(!(value.compare("aug"))) |
	(!(value.compare("rec"))) |
	(!(value.compare("nil"))) |
	(!(value.compare("where")))
	){
		type = "Keyword";
	}
	else{
		value = "<ID:" + value + ">";	
	}
	
	return new Token(type, value);
}

void Lexer :: readComment(){
	char a;
	while(hasNext){
		a = getNextChar();
		if(a == '\n'){
			break;	
		}
	}
}

Token* Lexer :: getInteger(){
	string type = "Integer";
	string value = "";
	
	while(hasNext){
		char a = getNextChar();
		if(isdigit(a)){
			value = value + a;
		}
		else{
			putBackChar(a);
			break;
		}
	}
	value = "<INT:" + value + ">";
	return new Token(type, value);
}

Token* Lexer :: getOperator(){
	string type = "Operator";
	string value = "";
	
	while(hasNext){
		
		if(upcomingComment()) break;
		
		char a = getNextChar();
		if(isOp(a)){
			value = value + a;
		}
		else{
			putBackChar(a);
			break;
		}
	}
	return new Token(type, value);
}

Token* Lexer :: getString(){
	string type = "String";
	string value = "";
	value = value + getNextChar();
	
	while(hasNext){
		char a = getNextChar();
		value = value + a;
		
		if(a == '\\'){
			char b = getNextChar();
			if(b == '\''){
				value = value + b;	
			}
			else{
				putBackChar(b);	
			}
		}
		
		if(a == '\''){
			value = "<STR:" + value + ">";
			return new Token(type, value);
		}
	}
	
	cout << "Error: Non-terminating string encountered." << endl;
	exit(EXIT_FAILURE);
}

Token* Lexer :: getPunction(){
	char a = getNextChar();
	switch(a){
		case '(':
			return new Token("Punction", "(");
			break;
		case ')':
			return new Token("Punction", ")");
			break;
		case ';':
			return new Token("Punction", ";");
			break;
		case ',':
			return new Token("Punction", ",");
			break;
		default:
			cout << "Error occured in getPunction." << endl;
			exit(EXIT_FAILURE);
			break;
	}
}

bool Lexer :: isOp(char a){
	
	char operators[26] = {'+', '-', '*', '<', '>', '&', '.',
					      '@', '/', ':', '=', '~', '|', '$',
					   	  '!', '#', '%', '^', '_', '[', ']',
					      '{', '}', '"', '`', '?'};
	
	for(int i=0; i<26; i++){
		if(operators[i] == a){
			return true;	
		}
	}
	return false;
	
}

bool Lexer :: upcomingIdentifier(){
	if(hasNext){
		char a = ifs.peek();
		if(isalpha(a)) return true;
	}
	return false;
}

bool Lexer :: upcomingInteger(){
	if(hasNext){
		char a = ifs.peek();
		if(isdigit(a)) return true;
	}
	return false;
}

bool Lexer :: upcomingOperator(){
	if(hasNext){
		char a = ifs.peek();
		if(isOp(a)) return true;
	}
	return false;
}

bool Lexer :: upcomingComment(){
	char a, b;
	if(hasNext){
		a = getNextChar();
		if((a == '/') && hasNext){	
			b = ifs.peek();
			putBackChar(a);
			if(b == '/') {
				return true;
			}
		}
		else{
			putBackChar(a);
		}
	}
	return false;		
}

bool Lexer :: upcomingString(){
	char a = ifs.peek();
	if(a == '\''){
		return true;	
	}
	return false;
}

bool Lexer :: upcomingPunction(){
	char a = ifs.peek();
	char punctions[4] = {'(', ')', ';', ','};
	for(int i=0; i<4; i++){
		if(punctions[i] == a){
			return true;
		}
	}
	return false;
}

void Lexer :: putBackChar(char a){
	ifs.putback(a);
	hasNext = true;
}

//Broken.
bool Lexer :: upcoming(string str){
	
	bool up = false;
	int currentPosition = ifs.tellg();
	
	char raw[str.length()+1];
	ifs.get(raw, str.length()+1);
	string temp(raw);
	
	if(temp.compare(str) == 0){
		up = true;
	}
	else {
		up = false;
	}
	ifs.seekg(currentPosition, std::ios_base::beg);
	
	return up;
}





