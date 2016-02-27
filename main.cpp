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
