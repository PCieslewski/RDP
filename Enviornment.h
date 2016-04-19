#ifndef ENVIORNMENT_H
#define ENVIORNMENT_H

#include <vector>
#include "ControlUnit.h"
#include <stdlib.h>
#include <iostream>
#include <stddef.h>

using namespace std;

class BoundPair {

	public:
		string str;
		ControlUnit* cu;

		BoundPair(string str, ControlUnit* cu){
			this->str = str;
			this->cu = cu;
		}

		bool strIs(string str){
			return !(this->str.compare(str));
		}
	
};

class Enviornment {

	private:
		vector<BoundPair> bindings;
	
	public:
		Enviornment();
		Enviornment(Enviornment* returningEnv);
		void addBinding(string str, ControlUnit* cu);
		ControlUnit* getBinding(string str);
		Enviornment* returningEnv;
		string toString();
	
};


#endif