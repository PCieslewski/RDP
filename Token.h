#ifndef TOKEN_H
#define TOKEN_H

#include <iostream>
#include <algorithm>
using namespace std;

class Token {
	
	public:
	
		string type;
		string value;
		string raw;
	
		Token();
		Token(string type, string value);
		Token(string type, string value, string raw);
		string toString();
	
		bool valueIs(string value);
		bool typeIs(string type);
	
};

#endif