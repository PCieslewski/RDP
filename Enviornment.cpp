#include "Enviornment.h"

Enviornment :: Enviornment(){
	returningEnv = NULL;
}

Enviornment :: Enviornment(Enviornment* returningEnv){
	this->returningEnv = returningEnv;
}

void Enviornment :: addBinding(string str, ControlUnit* cu){
	bindings.push_back(BoundPair(str,cu));
}

ControlUnit* Enviornment :: getBinding(string str){
	
	vector<BoundPair>::iterator it;
	for(it = bindings.begin(); it != bindings.end(); it++) {
		if((*it).strIs(str)){
			//exp
			return CUHelper :: copy((*it).cu);
			
			//return (*it).cu;
		}
	}
	
	if(returningEnv != NULL){
		return returningEnv->getBinding(str);	
	}
	else{
		cout << "No variable appears to bound to input: " << str << endl;
		exit(EXIT_FAILURE);
	}
	
}

string Enviornment :: toString(){
	
	ostringstream temp;
	
	if(returningEnv == NULL){
		return "End";	
	}
	
	vector<BoundPair>::iterator it;
	for(it = bindings.begin(); it != bindings.end(); it++) {
		temp << (*it).str << "=" << CUHelper :: getString((*it).cu) << " ";
	}
	
	temp << returningEnv->toString();	
	
	return temp.str();
	
}
	