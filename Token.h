#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <algorithm>
using namespace std;

class Token {
	
	public:
	
		string type;
		string value;
	
		Token();
		Token(string type, string value);
		string toString();
	
		bool valueIs(string value);
		bool typeIs(string type);
	
};

#endif