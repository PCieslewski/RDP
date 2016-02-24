#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
using namespace std;

class Token {
	
	public:
	
		string type;
		string value;
	
		Token();
		Token(string type, string value);
		string toString();
	
};

#endif