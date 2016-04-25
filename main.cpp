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
#include "Enviornment.h"
#include "CSEMachine.h"
#include <vector>
#include <utility>
#include <string>
#include <algorithm>

/*
This is the main function for the entire project. Simply,
it gets the command line arguments, such as -ast. Then it
creates the required objects and executes the program.

The following are all accepted flags:
-l     - Shows the file that was input
-ast   - Shows the AST generated
-st    - Shows the standardized tree
-cs    - Shows the control structures after flattening
-ex    - Shows the execution of the CSE machine
-noout - Does not show the final output.

*/

int main (int argc, char* argv[]){
	
	string path = string(argv[argc-1]);
	bool printAst = false;
	bool printfile = false;
	bool printSt = false;
	bool printCs = false;
	bool printExe = false;
	bool printOutput = true;
	
	if(!ifstream(path.c_str())){
		cout << "File does not exist!" << endl;
		exit(EXIT_FAILURE);
	}
	
	for(int i = 1; i < argc-1; i++){
		string arg = argv[i];
		if(!arg.compare("-ast")){
			printAst = true;	
		}
		else if(!arg.compare("-l")){
			printfile = true;	
		}
		else if(!arg.compare("-st")){
			printSt = true;	
		}
		else if(!arg.compare("-cs")){
			printCs = true;	
		}
		else if(!arg.compare("-ex")){
			printExe = true;	
		}
		else if(!arg.compare("-noout")){
			printOutput = false;	
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
	
	if(printAst){
		cout << ast->toString() << endl;
	}
	
	TreeNode* st = Standardizer :: standardize(ast);
	
	if(printSt){
		cout << st->toString() << endl;	
	}
	
	Flattener flat;
	StructureList* sl = flat.genStructureList(st);
	
	if(printCs){
		cout << sl->toString() << endl;
	}
	
	CSEMachine* cse = new CSEMachine(sl, printExe);
	cse->run();
	
	if(printOutput){
		cout << cse->output.str() << endl;
	}
  
}
