#include "ControlUnit.h"

ControlUnit :: ControlUnit(UnitType type){
	this->type = type;
}

IdCU :: IdCU(string name) : ControlUnit(IDENTIFIER){
	this->name = name;
}

EnvCU :: EnvCU(int envNumber) : ControlUnit(ENVIORNMENT){
	this->envNumber = envNumber;
}