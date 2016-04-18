#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <stack>
#include "Token.h"
#include "Lexer.h"
#include "TreeNode.h"
using namespace std;

class Parser {
	
	public:
	
		TreeNode* getAst(string path);
	
		Lexer lex;
		stack<TreeNode*> treeStack;
		Token* nextToken;
		
	private:
	
		void readToken(string value);
		void readTokenByType(string type);
		
		void buildTree(string value, int numChildren);
		void buildTree(string value, int numChildren, string type, string raw);
	
		void E();
		void Ew();
		void T();
		void Ta();
		void Tc();
		void B();
		void Bt();
		void Bs();
		void Bp();
		void A();
		void At();
		void Af();
		void Ap();
		void R();
		void Rn();
		void D();
		void Da();
		void Dr();
		void Db();
		void Vb();
		void Vl();

};

#endif