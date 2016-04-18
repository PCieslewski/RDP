#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

using namespace std;
#include <string>
#include <vector>
#include <sstream>

enum UnitType {IDENTIFIER, ENVIORNMENT, LAMBDA,
			   GAMMA, BINOP, UNOP, BETA, TAU, Y,
			   STRUCTURE, INTEGER, STRING, BOOLEAN,
			   TUPLE, DUMMY};

class CUHelper;
class ControlStructure;

class ControlUnit {
	
	public:
		UnitType type;
	
		ControlUnit(UnitType type){
			this->type = type;		
		}
	
		virtual string toString(){
			ostringstream temp;
			temp << "Base:";
			temp << (int)type;
			return temp.str();
		}
	
};

class IdCU: public ControlUnit {
	
	public:
		string name;
	
		IdCU(string name): ControlUnit(IDENTIFIER){
			this->name = name;
		}
	
		string toString(){
			return "Id:"+name;
		}
	
};

class EnvCU: public ControlUnit {
	
	public:
		int envNumber;
	
		EnvCU(int envNumber): ControlUnit(ENVIORNMENT){
			this->envNumber = envNumber;
		}
	
		string toString(){
			ostringstream temp;
			temp << "e.";
			temp << envNumber;
			return temp.str();
		}
	
};

class LambdaCU: public ControlUnit {

	public:
		vector<string> bindingVars;
		int lambdaNum;
		int currEnv;

		LambdaCU(int lambdaNum): ControlUnit(LAMBDA){
			this->lambdaNum = lambdaNum;
			this->currEnv = -1;
		}
	
		void addBindingVar(string bindingVar){
			bindingVars.push_back(bindingVar);
		}
	
		string toString(){
			ostringstream temp;
			temp << "Lambda.";
			temp << lambdaNum;
			
			for(vector<string>::iterator it = bindingVars.begin(); it != bindingVars.end(); it++) {
				temp << "." << *it;
			}
			
			return temp.str();
		}
	
};

class GammaCU: public ControlUnit {
	
	public:
	
		GammaCU(): ControlUnit(GAMMA){}
	
		string toString(){
			return "Gamma";
		}
	
};

class BinopCU: public ControlUnit {
	
	public:
		string op;
	
		BinopCU(string op): ControlUnit(BINOP){
			this->op = op;
		}
	
		string toString(){
			return op;
		}
	
};

class UnopCU: public ControlUnit {
	
	public:
		string op;
	
		UnopCU(string op): ControlUnit(BINOP){
			this->op = op;
		}
	
		string toString(){
			return op;
		}
	
};

class BetaCU: public ControlUnit {
	
	public:
	
		BetaCU(): ControlUnit(BETA){}
	
		string toString(){
			return "Beta";
		}
	
};

class TauCU: public ControlUnit {
	
	public:
		int num;
	
		TauCU(int num): ControlUnit(TAU){
			this->num = num;
		}
	
		string toString(){
			ostringstream temp;
			temp << "Tau.";
			temp << num;
			return temp.str();
		}
	
};

class YCU: public ControlUnit {
	
	public:
		YCU(): ControlUnit(Y){}
	
		string toString(){
			return "Y";
		}
	
};

class IntegerCU: public ControlUnit {
	
	public:
		int num;
	
		IntegerCU(int num): ControlUnit(INTEGER){
			this->num = num;
		}
	
		string toString(){
			ostringstream temp;
			temp << "Int.";
			temp << num;
			return temp.str();
		}
	
};

class StringCU: public ControlUnit {
	
	public:
		string value;
	
		StringCU(string value): ControlUnit(STRING){
			this->value = value;
		}
	
		string toString(){
			return "Str." + value;
		}
	
};

class BooleanCU: public ControlUnit {
	
	public:
		bool value;
	
		BooleanCU(bool value): ControlUnit(BOOLEAN){
			this->value = value;
		}
	
		string toString(){
			if(value==true){
				return "true";		
			}
			else{
				return "false";
			}
		}
	
};

class TupleCU: public ControlUnit {
	
	public:
		vector<ControlUnit*> list; 
	
		TupleCU(): ControlUnit(TUPLE){}
	
		string toString(){
			if(list.empty()){
				return "nil";	
			}
			else{
				ostringstream temp;
				temp << "(";
				for(vector<ControlUnit*>::iterator it = list.begin(); it != list.end(); it++) {
					temp << (*it)->toString();
					if(it+1 != list.end()){
						temp << ", ";
					}
				}
				temp << ")";
				return temp.str();
			}
		}
	
};

class DummyCU: public ControlUnit {
	
	public:
	
		DummyCU(): ControlUnit(DUMMY){}
	
		string toString(){
			return "Dummy";
		}
	
};

class ControlStructure: public ControlUnit {

	public:
		int structureNum;
		vector<ControlUnit*> units;
	
		ControlStructure(int structureNum): ControlUnit(STRUCTURE){
			this->structureNum = structureNum;
		}
		
		void pushFront(ControlUnit* cu){
			units.insert(units.begin(), cu);
		}
	
		void pushBack(ControlUnit* cu){
			units.push_back(cu);
		}
	
		string toString(){
			ostringstream temp;
			temp << "CS.";
			temp << structureNum;
			return temp.str();	
		}
	
		string toStringExpanded();
	
};

class CUHelper {
	
	public:
		static string getString(ControlUnit* cu){
			switch(cu->type){
				case(IDENTIFIER):
					return ((IdCU*)cu)->toString();
				case(ENVIORNMENT):
					return ((EnvCU*)cu)->toString();
				case(LAMBDA):
					return ((LambdaCU*)cu)->toString();
				case(GAMMA):
					return ((GammaCU*)cu)->toString();
				case(BINOP):
					return ((BinopCU*)cu)->toString();
				case(UNOP):
					return ((UnopCU*)cu)->toString();
				case(BETA):
					return ((BetaCU*)cu)->toString();
				case(TAU):
					return ((TauCU*)cu)->toString();
				case(Y):
					return ((YCU*)cu)->toString();
				case(STRUCTURE):
					return ((ControlStructure*)cu)->toString();
				case(INTEGER):
					return ((IntegerCU*)cu)->toString();
				case(STRING):
					return ((StringCU*)cu)->toString();
				case(BOOLEAN):
					return ((BooleanCU*)cu)->toString();
				case(TUPLE):
					return ((TupleCU*)cu)->toString();
				case(DUMMY):
					return ((DummyCU*)cu)->toString();
				default:
					return "Unknown Type.";
			}
		}
	
};

/*string ControlStructure :: toStringExpanded(){
	ostringstream temp;
	temp << "{";
	for(vector<ControlUnit*>::iterator it = units.begin(); it != units.end(); it++) {
		temp << CUHelper :: getString(*it);
		if(it+1 != units.end()){
			temp << ", ";
		}
	}
	temp << "}";
	return temp.str();
}*/


#endif