#ifndef FLATTENER_H
#define FLATTENER_H

#include "TreeNode.h"
#include "ControlUnit.h"
#include <queue>
#include <string>
#include <stdlib.h>
#include <algorithm>

class StructureList{
	
	public:
		vector<ControlStructure*> list;
	
		static bool compare(const ControlStructure* cs1, const ControlStructure* cs2){
		   return (cs1->structureNum) < (cs2->structureNum);
		}

		void addStructure(ControlStructure*);
		string toString();
	
};

class Flattener{
	
	
	public:
		StructureList* genStructureList(TreeNode* node);
	
	private:
		int currLambda;
		int structureNum;
		queue<TreeNode*> nodeQueue;

		ControlStructure* flatten(TreeNode* node, StructureList* sl);
		void flatten(TreeNode* node, ControlStructure* cs, StructureList* sl);
	
};

#endif