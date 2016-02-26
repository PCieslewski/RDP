#ifndef LEXER_H
#define LEXER_H

#include <iostream>
#include <iterator>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>
#include "Token.h"
#include <ios>
using namespace std;

class Lexer {
	
	public:
	
		Lexer();
	
		void open(string path);
		void close();
		bool hasNextToken;
	
		void test();
		Token* getNextToken();
	
	private:
	
		ifstream ifs;
		bool isOp(char a);
		bool hasNext;
	
		char getNextChar();
		void putBackChar(char a);
	
		Token* getInteger();
		Token* getIdentifier();
		Token* getOperator();
		Token* getString();
		Token* getPunction();
		void readComment();
	
		bool upcomingComment();
		bool upcomingIdentifier();
		bool upcomingOperator();
		bool upcomingInteger();
		bool upcomingString();
		bool upcomingPunction();
	
		//Broken
		bool upcoming(string str);
		
};

#endif
