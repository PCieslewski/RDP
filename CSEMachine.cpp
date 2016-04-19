#include "CSEMachine.h"

CSEMachine :: CSEMachine(StructureList* sl){
	this->sl = sl;
	currEnv = 0;
	maxEnv = 0;
	init();
	done = false;
	cout << stateToString() << endl;
}

string CSEMachine :: stateToString(){
	
	list<ControlUnit*>::iterator it;
	ostringstream temp;
	
	temp << "[";
	for (it = controlStack.begin(); it != controlStack.end(); it++){
		if(it != controlStack.begin()){
			temp << ", ";
		}
		temp << CUHelper :: getString(*it);
	}
	temp << "]";
	
	temp << " --- ";
		
	temp << "[";
	for (it = exeStack.begin(); it != exeStack.end(); it++){
		if(it != exeStack.begin()){
			temp << ", ";
		}
		temp << CUHelper :: getString(*it);
	}
	temp << "]";
	
	temp << "     Env = " << currEnv;
	
	return temp.str();
	
}

void CSEMachine :: init(){

	Enviornment* e0 = new Enviornment();
	el.push_back(e0);
	controlStack.push_back(new EnvCU(0));
	exeStack.push_front(new EnvCU(0));
	
	controlStack.push_back(sl->list.at(0));
	
}

void CSEMachine :: run(){
	
	while(!done){
		tick();	
	}
	
}

void CSEMachine :: tick(){
	
	switch(controlStack.back()->type){
		case STRUCTURE:
			expandStructure();
			break;
		case INTEGER:
			moveInt();
			break;
		case LAMBDA:
			moveLambda();
			break;
		case GAMMA:
			exeGamma();
			break;
		case IDENTIFIER:
			lookupId();
			break;
		case ENVIORNMENT:
			returnFromEnv();
			break;
		//case BINOP:
			//exeBinop();
			//break;
		default:
			cout << "Unexpected ControlUnit type : " << controlStack.back()->type << endl;
			exit(EXIT_FAILURE);
	}
	
	cout << stateToString() << endl;
	
}

void CSEMachine :: expandStructure(){

	ControlStructure* cs = (ControlStructure*)controlStack.back();
	
	controlStack.pop_back();
	
	expandStructure(cs);
	
}

void CSEMachine :: expandStructure(ControlStructure* cs){

	vector<ControlUnit*>::iterator it;
	for (it = cs->units.begin(); it != cs->units.end(); it++){
		controlStack.push_back(*it);
	}
	
}

void CSEMachine :: moveInt(){

	IntegerCU* icu = (IntegerCU*)controlStack.back();
	
	controlStack.pop_back();
	exeStack.push_front(icu);
	
}

void CSEMachine :: moveLambda(){

	LambdaCU* lcu = (LambdaCU*)controlStack.back();
	lcu->currEnv = currEnv;
	
	controlStack.pop_back();
	exeStack.push_front(lcu);
	
}

void CSEMachine :: exeGamma(){
	
	ControlUnit* cu = exeStack.front();
	
	switch(cu->type){
		case LAMBDA:
			exeGammaOnLambda();
			break;
		case FUNCTION:
			exeGammaOnFunction();
			break;
		default:
			cout << "Unexpected ControlUnit for gamma execution : " << controlStack.back()->type << endl;
			exit(EXIT_FAILURE);
	}
	
}

void CSEMachine :: exeGammaOnLambda(){
	
	GammaCU* gcu = (GammaCU*)controlStack.back();
	LambdaCU* lcu = (LambdaCU*)exeStack.front();
	controlStack.pop_back();
	exeStack.pop_front();
	
	Enviornment* newEnv = new Enviornment(el.at(currEnv));
	el.push_back(newEnv);
	
	maxEnv++;
	currEnv = maxEnv;
	
	bindVariables(lcu, newEnv);
	
	controlStack.push_back(new EnvCU(currEnv));
	exeStack.push_front(new EnvCU(currEnv));
	
	expandStructure(sl->list.at(lcu->lambdaNum));
	
}

void CSEMachine :: bindVariables(LambdaCU* lcu, Enviornment* newEnv){
	
	if(lcu->bindingVars.size()==1){
		string varStr = lcu->bindingVars.at(0);
		newEnv->addBinding(varStr, exeStack.front());
		exeStack.pop_front();
	}
	else{
		cout << "DO MULTI BINDING LAMDBA!!! AHHHHHHH." << endl;
		exit(EXIT_FAILURE);
	}
	
}

void CSEMachine :: exeGammaOnFunction(){
	
	GammaCU* gcu = (GammaCU*)controlStack.back();
	FunctionCU* fcu = (FunctionCU*)exeStack.front();
	controlStack.pop_back();
	exeStack.pop_front();
	
	if(fcu->nameIs("Print")){
		callPrint();
	}
	else{
		cout << "Unknown function : " << fcu->name << endl;
		exit(EXIT_FAILURE);	
	}
	
}

void CSEMachine :: callPrint(){
	
	ControlUnit* cu = exeStack.front();
	exeStack.pop_front();
	
	output << CUHelper :: getString(cu);
	
}

void CSEMachine :: lookupId(){

	IdCU* icu = (IdCU*)controlStack.back();
	controlStack.pop_back();
	
	if(icu->nameIs("Print")){
		exeStack.push_front(new FunctionCU("Print"));	
	}
	else if(icu->nameIs("Stem")){
		exeStack.push_front(new FunctionCU("Stem"));	
	}
	else if(icu->nameIs("Stern")){
		exeStack.push_front(new FunctionCU("Stern"));	
	}
	else{
		exeStack.push_front(el.at(currEnv)->getBinding(icu->name));
	}
}

void CSEMachine :: returnFromEnv(){
	
	EnvCU* ecu1 = (EnvCU*)controlStack.back();
	if(ecu1->envNumber == 0){
		done = true;
	}
	else{
		Enviornment* env = el.at(currEnv);
		currEnv = distance(el.begin(),find(el.begin(), el.end(), env->returningEnv));
	}
	
	controlStack.pop_back();
	
	if(exeStack.front()->type == ENVIORNMENT){
		exeStack.pop_front();	
	}
	else{
		ControlUnit* cu = exeStack.front();
		exeStack.pop_front();
		exeStack.pop_front();
		exeStack.push_front(cu);
	}
	
	
	
}

void CSEMachine :: exeBinop(){
	
	BinopCU* bcu = (BinopCU*)controlStack.back();
	controlStack.pop_back();
	
	if(bcu->opIs("+")){
		
	}
	else if(bcu->opIs("-")){
		
	}
	else if(bcu->opIs("**")){
		
	}
	else if(bcu->opIs("aug")){
		
	}
	else if(bcu->opIs("or")){
		
	}
	else if(bcu->opIs("&")){
		
	}
	else if(bcu->opIs("gr")){
		
	}
	else if(bcu->opIs("ge")){
		
	}
	else if(bcu->opIs("ls")){
		
	}
	else if(bcu->opIs("le")){
		
	}
	else if(bcu->opIs("eq")){
		
	}
	
}



