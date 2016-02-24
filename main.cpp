#include <iostream>
#include <fstream>
using namespace std;

#include "Token.h"
#include "Lexer.h"

int main (int argc, char* argv[]){
	
	string path = string(argv[1]);
	string line;
	
	Lexer lex;
	
	lex.open(path.c_str());
		
	while(lex.hasNext){
		cout << lex.getNextToken()->toString() << endl;
	}
	
	
	
	
	/*ifstream myfile;
	myfile.open(path.c_str());
	
	Token* test = new Token("INT", "10");
	cout << test->type << endl;
	
	char c;
	if (myfile.is_open()){
		while ( myfile.get(c) ){
			if(c == '\n'){
				cout << "NEWLINE" << endl;
			}
			else if(c == ' ') {
				cout << "SPACE" << endl;
			}
			else{
				cout << c << endl;
			}
		}
		myfile.close();
    }*/
  
}
