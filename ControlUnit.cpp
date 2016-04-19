#include "ControlUnit.h"

string ControlStructure :: toStringExpanded(){
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
}

string TupleCU :: toString(){
	if(list.empty()){
		return "nil";	
	}
	else{
		ostringstream temp;
		temp << "(";
		for(vector<ControlUnit*>::iterator it = list.begin(); it != list.end(); it++) {
			//temp << (*it)->toString();
			temp << CUHelper :: getString(*it);
			if(it+1 != list.end()){
				temp << ", ";
			}
		}
		temp << ")";
		return temp.str();
	}
}