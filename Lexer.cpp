#include "Lexer.h"

//Constructor for the lexer object.
Lexer :: Lexer(){
	hasNext = false;
	hasNextToken = false;
}

//Opens a file for the lexer.
void Lexer :: open(string path){
	ifs.open(path.c_str());
	hasNext = !(ifs.peek() == EOF);
	hasNextToken = true;
}

//Closes a file for the lexer.
void Lexer :: close(){
	hasNext = false;
	hasNextToken = false;
	ifs.close();	
}

//Gets the next character in the file.
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

//Function that reads and returns an identifier.
//Note: Also if the identifier is a KEYWORD, such as in the list below
//it will return a keyword token instead.
Token* Lexer :: getIdentifier(){
	string type = "Identifier";
	string value = "";
	string raw = "";
	
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
	
	raw = value;
	
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
	(!(value.compare("eq"))) |
	(!(value.compare("not"))) |
	(!(value.compare("gr"))) |
	(!(value.compare("ge"))) |
	(!(value.compare("ne"))) |
	(!(value.compare("ls"))) |
	(!(value.compare("le"))) |
	(!(value.compare("dummy"))) |
	(!(value.compare("true"))) |
	(!(value.compare("false"))) |
	(!(value.compare("where")))
	){
		type = "Keyword";
	}
	else{
		value = "<ID:" + value + ">";	
	}
	
	return new Token(type, value, raw);
}

//Function that reads and deletes a comment.
void Lexer :: readComment(){
	char a;
	while(hasNext){
		a = getNextChar();
		if(a == '\n'){
			break;	
		}
	}
}

//Function that reads and returns an integer.
Token* Lexer :: getInteger(){
	string type = "Integer";
	string value = "";
	string raw = "";
	
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
	
	raw = value;
	value = "<INT:" + value + ">";
	return new Token(type, value, raw);
}

//Function that reads and returns an operator.
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

//Function that reads and returns a string.
Token* Lexer :: getString(){
	string type = "String";
	string value = "";
	string raw = "";
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
			raw = value;
			value = "<STR:" + value + ">";
			return new Token(type, value, raw);
		}
	}
	
	cout << "Error: Non-terminating string encountered." << endl;
	exit(EXIT_FAILURE);
}

//Function that reads and returns a punction.
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

//Function that checks to see if a character is an operator.
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

//Function that checks to see if an identifier is next in the file.
bool Lexer :: upcomingIdentifier(){
	if(hasNext){
		char a = ifs.peek();
		if(isalpha(a)) return true;
	}
	return false;
}

//Function that checks to see if an identifier is next in the file.
bool Lexer :: upcomingInteger(){
	if(hasNext){
		char a = ifs.peek();
		if(isdigit(a)) return true;
	}
	return false;
}

//Function that checks to see if an operator is next in the file.
bool Lexer :: upcomingOperator(){
	if(hasNext){
		char a = ifs.peek();
		if(isOp(a)) return true;
	}
	return false;
}

////Function that checks to see if a comment is next in the file.
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

//Function that checks to see if a string is next in the file.
bool Lexer :: upcomingString(){
	char a = ifs.peek();
	if(a == '\''){
		return true;	
	}
	return false;
}

//Function that checks to see if a punction is next in the file.
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

//Function that returns a character to the input stream to be retrieved later.
void Lexer :: putBackChar(char a){
	ifs.putback(a);
	hasNext = true;
}




