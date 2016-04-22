#ifndef CONTROLUNIT_H
#define CONTROLUNIT_H

using namespace std;
#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>
#include <math.h>

enum UnitType {IDENTIFIER, ENVIORNMENT, LAMBDA,
			   GAMMA, BINOP, UNOP, BETA, TAU, Y,
			   STRUCTURE, INTEGER, STRING, BOOLEAN,
			   TUPLE, DUMMY, FUNCTION, ETA};

class ControlUnit;
class IdCU;
class FunctionCU;
class EnvCU;
class LambdaCU;
class GammaCU;
class BinopCU;
class UnopCU;
class BetaCU;
class TauCU;
class YCU;
class IntegerCU;
class StringCU;
class BooleanCU;
class TupleCU;
class DummyCU;
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
	
		bool nameIs(string name){
			return !(this->name.compare(name));
		}
	
		IdCU* copy(){
			return new IdCU(this->name);	
		}
	
};

class FunctionCU: public ControlUnit {
	
	public:
		string name;
		string dataStr;
	
		FunctionCU(string name): ControlUnit(FUNCTION){
			this->name = name;
		}
	
		string toString(){
			return "Func:"+name;
		}
	
		bool nameIs(string name){
			return !(this->name.compare(name));
		}
	
		FunctionCU* copy(){
			FunctionCU* fcu = new FunctionCU(this->name);
			fcu->dataStr = this->dataStr;
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
	
		EnvCU* copy(){
			return new EnvCU(this->envNumber);	
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
			
			/*
			ostringstream temp;
			temp << "Lambda.";
			temp << lambdaNum;
			
			for(vector<string>::iterator it = bindingVars.begin(); it != bindingVars.end(); it++) {
				temp << "." << *it;
			}
			
			return temp.str();
			*/
			
			ostringstream temp;
			temp << "[lambda closure: ";
			
			for(vector<string>::iterator it = bindingVars.begin(); it != bindingVars.end(); it++) {
				temp << *it << ": ";
			}
			
			temp << lambdaNum << "]";
			
			return temp.str();
		}
	
		LambdaCU* copy(){
			LambdaCU* lam = new LambdaCU(this->lambdaNum);
			lam->currEnv = this->currEnv;
			lam->bindingVars = this->bindingVars;
			return lam;
		}
	
};

class GammaCU: public ControlUnit {
	
	public:
	
		GammaCU(): ControlUnit(GAMMA){}
	
		string toString(){
			return "Gamma";
		}
	
		GammaCU* copy(){
			return new GammaCU();	
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
	
		bool opIs(string op){
			return !(this->op.compare(op));
		}
	
		BinopCU* copy(){
			return new BinopCU(this->op);	
		}
	
};

class UnopCU: public ControlUnit {
	
	public:
		string op;
	
		UnopCU(string op): ControlUnit(UNOP){
			this->op = op;
		}
	
		string toString(){
			return op;
		}
	
		bool opIs(string op){
			return !(this->op.compare(op));
		}
	
		UnopCU* copy(){
			return new UnopCU(this->op);	
		}
	
};

class BetaCU: public ControlUnit {
	
	public:
	
		BetaCU(): ControlUnit(BETA){}
	
		string toString(){
			return "Beta";
		}
	
		BetaCU* copy(){
			return new BetaCU();	
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
	
		TauCU* copy(){
			return new TauCU(this->num);	
		}
	
};

class YCU: public ControlUnit {
	
	public:
		YCU(): ControlUnit(Y){}
	
		string toString(){
			return "Y";
		}
	
		YCU* copy(){
			return new YCU();	
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
			//temp << "Int.";
			temp << num;
			return temp.str();
		}
	
		IntegerCU* copy(){
			return new IntegerCU(this->num);	
		}
	
};

class StringCU: public ControlUnit {
	
	public:
		string value;
	
		StringCU(string value): ControlUnit(STRING){
			this->value = value;
		}
	
		string toString(){
			//return "Str." + value;
			//return "'" + value + "'";
			return value;
		}
	
		bool valueIs(string value){
			return !(this->value.compare(value));
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
	
		string toString();
	
		void insert(ControlUnit* cu){
			
			if(cu->type == ENVIORNMENT){
				cout << "Cannot add enviornment to tuple." << endl;
				exit(EXIT_FAILURE);
			}
			
			list.push_back(cu);	
		}
	
};

class DummyCU: public ControlUnit {
	
	public:
	
		DummyCU(): ControlUnit(DUMMY){}
	
		string toString(){
			return "Dummy";
		}
	
};

class EtaCU: public ControlUnit {
	
	public:
	
		LambdaCU* recLambda;
	
		EtaCU(LambdaCU* recLambda): ControlUnit(ETA){
			this->recLambda = recLambda;
		}
	
		string toString(){
			return "Eta";
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
				case(FUNCTION):
					return ((FunctionCU*)cu)->toString();
				case(ETA):
					return ((EtaCU*)cu)->toString();
				default:
					return "Unknown Type.";
			}
		}
	
		static bool ls(ControlUnit* cu1, ControlUnit* cu2){
			if( (cu1->type == INTEGER) && (cu1->type == INTEGER) ){
				return ((IntegerCU*)cu1)->num < ((IntegerCU*)cu2)->num;
			}
			else if( (cu1->type == STRING) && (cu1->type == STRING) ){
				return ((StringCU*)cu1)->value < ((StringCU*)cu2)->value;
			}
			else{
				cout << "Unexpected Comparison Types" << endl;
				exit(EXIT_FAILURE);
			}
		}
	
		static bool eq(ControlUnit* cu1, ControlUnit* cu2){
			return (!ls(cu1,cu2)) && (!ls(cu2,cu1));	
		}

		static bool ge(ControlUnit* cu1, ControlUnit* cu2){
			return !ls(cu1,cu2);	
		}
	
		static bool le(ControlUnit* cu1, ControlUnit* cu2){
			return ls(cu1,cu2) || eq(cu1,cu2);	
		}
	
		static bool gr(ControlUnit* cu1, ControlUnit* cu2){
			return !le(cu1,cu2);
		}
	
		static bool ne(ControlUnit* cu1, ControlUnit* cu2){
			return !eq(cu1,cu2);
		}
	
		static int add(ControlUnit* cu1, ControlUnit* cu2){
			if( (cu1->type == INTEGER) && (cu1->type == INTEGER) ){
				return ((IntegerCU*)cu1)->num + ((IntegerCU*)cu2)->num;
			}
			else{
				cout << "Unexpected Addition Types" << endl;
				exit(EXIT_FAILURE);
			}
		}
		
		static int subtract(ControlUnit* cu1, ControlUnit* cu2){
			if( (cu1->type == INTEGER) && (cu1->type == INTEGER) ){
				return ((IntegerCU*)cu1)->num - ((IntegerCU*)cu2)->num;
			}
			else{
				cout << "Unexpected Subtraction Types" << endl;
				exit(EXIT_FAILURE);
			}
		}
	
		static int multiply(ControlUnit* cu1, ControlUnit* cu2){
			if( (cu1->type == INTEGER) && (cu1->type == INTEGER) ){
				return ((IntegerCU*)cu1)->num * ((IntegerCU*)cu2)->num;
			}
			else{
				cout << "Unexpected Multiplication Types" << endl;
				exit(EXIT_FAILURE);
			}
		}
	
		static int divide(ControlUnit* cu1, ControlUnit* cu2){
			if( (cu1->type == INTEGER) && (cu1->type == INTEGER) ){
				return ((IntegerCU*)cu1)->num / ((IntegerCU*)cu2)->num;
			}
			else{
				cout << "Unexpected Division Types" << endl;
				exit(EXIT_FAILURE);
			}
		}
	
		static int power(ControlUnit* cu1, ControlUnit* cu2){
			if( (cu1->type == INTEGER) && (cu1->type == INTEGER) ){
				return pow(((IntegerCU*)cu1)->num,((IntegerCU*)cu2)->num);
			}
			else{
				cout << "Unexpected Power Types" << endl;
				exit(EXIT_FAILURE);
			}
		}
	
		static bool logicalAnd(ControlUnit* cu1, ControlUnit* cu2){
			if( (cu1->type == BOOLEAN) && (cu1->type == BOOLEAN) ){
				return ((BooleanCU*)cu1)->value && ((BooleanCU*)cu2)->value;
			}
			else{
				cout << "Unexpected Logical And Types" << endl;
				exit(EXIT_FAILURE);
			}
		}
	
		static bool logicalOr(ControlUnit* cu1, ControlUnit* cu2){
			if( (cu1->type == BOOLEAN) && (cu1->type == BOOLEAN) ){
				return ((BooleanCU*)cu1)->value || ((BooleanCU*)cu2)->value;
			}
			else{
				cout << "Unexpected Logical Or Types" << endl;
				exit(EXIT_FAILURE);
			}
		}
	
		static ControlUnit* aug(ControlUnit* cu1, ControlUnit* cu2){
			if( (cu1->type == TUPLE) ){
				((TupleCU*)cu1)->insert(cu2);
				return cu1;
			}
			else{
				cout << "Augment to non tuple." << endl;
				exit(EXIT_FAILURE);
			}
		}
	
		static bool logicalNot(ControlUnit* cu){
			if( (cu->type == BOOLEAN) ){
				return !(((BooleanCU*)cu)->value);
			}
			else{
				cout << "Unexpected Logical Not type" << endl;
				exit(EXIT_FAILURE);
			}
		}
	
		static int neg(ControlUnit* cu){
			if( (cu->type == INTEGER) ){
				return -(((IntegerCU*)cu)->num);
			}
			else{
				cout << "Unexpected neg type" << endl;
				exit(EXIT_FAILURE);
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