#include <iostream>
#include <fstream>
using namespace std;

#include "TreeNode.h"
#include "Token.h"
#include "Lexer.h"
#include "Parser.h"
#include "Standardizer.h"
#include "Flattener.h"
#include "ControlUnit.h"
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
	bool printfile = false;
	bool printSt = false;
	
	if(!ifstream(path.c_str())){
		cout << "File does not exist!" << endl;
		exit(EXIT_FAILURE);
	}
	
	for(int i = 1; i < argc-1; i++){
		string arg = argv[i];
		if(!arg.compare("-ast")){
			print = true;	
		}
		else if(!arg.compare("-l")){
			printfile = true;	
		}
		else if(!arg.compare("-st")){
			printSt = true;	
		}
	}
	
	if(printfile){
		string line;
		ifstream myfile (path.c_str());
		if (myfile.is_open()){
			while ( getline (myfile,line) ){
				cout << line << '\n';
			}
		myfile.close();
  		}
	}
	
	Parser p;
	
	TreeNode* ast = p.getAst(path.c_str());
	
	if(print){
		cout << ast->toString() << endl;
	}
	
	TreeNode* st = Standardizer :: standardize(ast);
	
	if(printSt){
		cout << st->toString() << endl;	
	}
	
	Flattener flat;
	
	StructureList* sl = flat.genStructureList(st);
	
	cout << sl->toString() << endl;
  
}
