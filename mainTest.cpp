#include <iostream>
#include <fstream>
using namespace std;

#include "Flattener.h"
#include "ControlUnit.h"

int main(){

	LambdaCU* u1 = new LambdaCU(1);
	GammaCU* u2 = new GammaCU();
	EnvCU* u3 = new EnvCU(0);
	IdCU* u4 = new IdCU("Test");
	BinopCU* u5 = new BinopCU("+");
	UnopCU* u6 = new UnopCU("neg");
	BetaCU* u7 = new BetaCU();
	TauCU* u8 = new TauCU(5);
	YCU* u9 = new YCU();
	
	ControlStructure* cs1 = new ControlStructure(1);
	cs1->pushBack(u1);
	cs1->pushBack(u2);
	cs1->pushBack(u3);
	cs1->pushBack(u4);
	cs1->pushBack(u5);
	cs1->pushBack(u6);
	cs1->pushBack(u7);
	cs1->pushBack(u8);
	cs1->pushBack(u9);
	
	//cout << cs1->toString() << endl;
	//cout << cs1->toStringExpanded() << endl;
	
	ControlStructure* cs2 = new ControlStructure(2);
	cs2->pushFront(u1);
	cs2->pushFront(u2);
	cs2->pushFront(u3);
	cs2->pushFront(u4);
	cs2->pushFront(u5);
	cs2->pushFront(u6);
	cs2->pushFront(u7);
	cs2->pushFront(u8);
	cs2->pushFront(u9);
	cs2->pushFront(cs1);
	
	//cout << cs2->toString() << endl;
	//cout << cs2->toStringExpanded() << endl;
	
	StructureList* sl = new StructureList();
	sl->addStructure(cs1);
	sl->addStructure(cs2);
	
	cout << sl->toString() << endl;
	
}