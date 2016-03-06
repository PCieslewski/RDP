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

/*
This is the main function for the entire project. Simply,
it gets the command line arguments, such as -ast. Then it
creates a parser object on the path passed in and calls 
getAst on it to generate the AST. Then it prints the AST
if the -ast flag was set.
*/

int main (int argc, char* argv[]){
	
	string path = string(argv[argc-1]);
	bool print = false;
	
	if(!ifstream(path.c_str())){
		cout << "File does not exist!" << endl;
		exit(EXIT_FAILURE);
	}
	
	for(int i = 1; i < argc-1; i++){
		string arg = argv[i];
		if(!arg.compare("-ast")){
			print = true;	
		}
	}
	
	Parser p;
	
	TreeNode* ast = p.getAst(path.c_str());
	
	if(print){
		cout << ast->toString() << endl;
	}
  
}
