#include "Token.h"

Token :: Token(){
	type = "";
	value = "";
}

Token :: Token(string type, string value){
	this->type = type;
	this->value = value;
}

string Token :: toString(){
	string str = "Token - Type: " + type + " - Value: " + value;
	return str;
}

bool Token :: valueIs(string value){
	/*string s1 = this->value;
	string s2 = value;
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	return !(s1.compare(s2));*/
	return !(this->value.compare(value));
}

bool Token :: typeIs(string type){
	/*string s1 = this->type;
	string s2 = type;
	transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	return !(s1.compare(s2));*/
	return !(this->type.compare(type));
}