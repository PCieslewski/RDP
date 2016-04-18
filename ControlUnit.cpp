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