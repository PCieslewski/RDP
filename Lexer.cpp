#include "Lexer.h"

Lexer :: Lexer(){
	hasNext = false;
}

void Lexer :: open(string path){
	ifs.open(path.c_str());
	hasNext = !(ifs.peek() == EOF);
}

void Lexer :: close(){
	hasNext = false;
	ifs.close();	
}

char Lexer :: getNextChar(){
	char temp;
	ifs.get(temp);
	//cout << temp << endl;
	hasNext = !(ifs.peek() == EOF);
	return temp;
}

void Lexer :: test(){
	cout << "Test" << endl;	
}

//Main function that returns the next token of the input file.
Token* Lexer :: getNextToken(){
	char a, b;
	bool t = true;
	while(hasNext){
		
		//ifs.get(a);
		//Get a character from the file.
		//if(ifs.eof()){
		//	return new Token("EOF", "");
		//}
		
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
			t = ifs.get(a);
		}
		
	}
	
	hasNext = false;
	return new Token("EOF", "");
	
}

Token* Lexer :: getIdentifier(){
	string type = "Identifier";
	string value = "";
	Token* token = new Token();
	char a;
	
	while(hasNext){
		a = getNextChar();
		if(isalpha(a)){
			value = value + a;
		}
		else{
			putBackChar(a);
			break;
		}
	}
	
	token->type = type;
	token->value = value;
	return token;
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
		if(a == '\''){
			return new Token(type, value);
		}
	}
	
	cout << "Error: Non-terminating string encountered." << endl;
	exit(EXIT_FAILURE);
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
		char a = getNextChar();
		putBackChar(a);
		if(isalpha(a)) return true;
	}
	return false;
}

bool Lexer :: upcomingInteger(){
	if(hasNext){
		char a = getNextChar();
		putBackChar(a);
		if(isdigit(a)) return true;
	}
	return false;
}

bool Lexer :: upcomingOperator(){
	if(hasNext){
		char a = getNextChar();
		putBackChar(a);
		if(isOp(a)) return true;
	}
	return false;
}

bool Lexer :: upcomingComment(){
	char a, b;
	if(hasNext){
		a = getNextChar();
		if((a == '/') && hasNext){	
			b = getNextChar();
			putBackChar(b);
			putBackChar(a);
			if(b == '/') return true;
		}
		putBackChar(a);
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

void Lexer :: putBackChar(char a){
	ifs.putback(a);
	hasNext = true;
}



