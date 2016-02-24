#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <iterator>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include "Token.h"
using namespace std;

class Lexer {
	
	public:
	
		Lexer();
	
		void open(string path);
		void close();
		bool hasNext;
	
		void test();
		Token* getNextToken();
	
	private:
	
		ifstream ifs;
		bool isOp(char a);
	
		char getNextChar();
		void putBackChar(char a);
	
		Token* getInteger();
		Token* getIdentifier();
		Token* getOperator();
		Token* getString();
		void readComment();
	
		bool upcomingComment();
		bool upcomingIdentifier();
		bool upcomingOperator();
		bool upcomingInteger();
		bool upcomingString();
		
};

#endif
