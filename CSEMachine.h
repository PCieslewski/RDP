#ifndef CSEMACHINE_H
#define CSEMACHINE_H

#include <vector>
#include <list>
#include "ControlUnit.h"
#include <stdlib.h>
#include <iostream>
#include <stddef.h>
#include "Enviornment.h"
#include "Flattener.h"

using namespace std;

class CSEMachine {
	
	private:
		list<ControlUnit*> controlStack;
		list<ControlUnit*> exeStack;
		vector<Enviornment*> el;
		StructureList* sl;
		int currEnv;
		int maxEnv;
	
		void init();
		void expandStructure();
		void expandStructure(ControlStructure* cs);
		void moveInt();
		void moveLambda();
		void exeGamma();
		void exeGammaOnLambda();
		void bindVariables(LambdaCU* lcu, Enviornment* newEnv);
		void exeGammaOnFunction();
		void callPrint();
		void lookupId();
		void returnFromEnv();
		void exeBinop();
		void exeUnop();
		void exeTau();
		void moveY();
		void exeGammaOnY();
		void exeGammaOnEta();
		void exeBeta();
		void moveString();
		void moveBoolean();
		void callStem();
		void callStern();
		void callConcP1();
		void callConcP2();
		void exeGammaOnTuple();
		void callOrder();
		void callItoS();
		void callIstuple();
		void callIsfunction();
		void callIsdummy();
		void callIsstring();
		void callIsinteger();
		void callIstruthvalue();
		void move();
	
	public:
		CSEMachine(StructureList* sl, bool printExe);
		string stateToString();
		void run();
		void tick();
		ostringstream output;
		bool done;
		bool printExe;
	
};


#endif