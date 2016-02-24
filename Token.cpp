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