#ifndef FLATTENER_H
#define FLATTENER_H

#inlude <ControlUnit.h>
#include <queue>

class Flattener{
	
	int currLambda;
	int structureNum;
	queue<TreeNode*> nodeQueue;

	vector<ControlStucture*>* getControlStructures(TreeNode* node);
	ControlStructure* flatten(TreeNode* node);
	
};

#endif