#include <iostream>
#include <fstream>
using namespace std;

#include "TreeNode.h"
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

int main (int argc, char* argv[]){
	
	/*string t = "MyType";
	string val = "MyVal";
	string s1 = t;
	string s2 = val;
	std::transform(s1.begin(), s1.end(), s1.begin(), ::tolower);
	std::transform(s2.begin(), s2.end(), s2.begin(), ::tolower);
	
	cout << s1 << endl;
	cout << s2 << endl;
	cout << t << endl;
	cout << val << endl;*/
	
	
	/*TreeNode t0("0");
	TreeNode t1("1");
	TreeNode t2("2");
	TreeNode t3("3");
	TreeNode t4("4");
	TreeNode t5("5");
	TreeNode t6("5");
	
	t0.addChild(&t1);
	t0.addChild(&t2);
	t2.addChild(&t3);
	t2.addChild(&t4);
	t3.addChild(&t5);
	t3.addChild(&t6);
	
	cout << t0.toString() << endl;
	cout << endl;
	cout << t2.toString() << endl;*/
	
	string path = string(argv[1]);
	string line;
	
	Lexer lex;
	
	/*lex.open(path.c_str());
	
	while(lex.hasNextToken){
		cout << lex.getNextToken()->toString() << endl;
	}*/
	
	Parser p;
	
	TreeNode* ast = p.getAst(path.c_str());
	
	cout << ast->toString() << endl;
  
}
