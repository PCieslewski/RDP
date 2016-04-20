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
creates a parser object on the path passed in and calls 
getAst on it to generate the AST. Then it prints the AST
if the -ast flag was set.
*/

void replaceAll(std::string& str, const std::string& from, const std::string& to);

int main (int argc, char* argv[]){
	
	string path = string(argv[argc-1]);
	bool print = false;
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
			print = true;	
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
	
	if(print){
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
	
	if(printOutput){
		CSEMachine* cse = new CSEMachine(sl, printExe);
		cse->run();
		
		string out = cse->output.str();
		replaceAll(out, "\\n", "\n");
		replaceAll(out, "\\t", "\t");
		cout << out << endl;
	}
  
}

void replaceAll(std::string& str, const std::string& from, const std::string& to) {
	if(from.empty())
		return;
	size_t start_pos = 0;
	while((start_pos = str.find(from, start_pos)) != std::string::npos) {
		str.replace(start_pos, from.length(), to);
		start_pos += to.length();
	}
}
