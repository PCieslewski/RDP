#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
	
	public:
	
		TreeNode();
		TreeNode(string value);
	
		string value;
		vector<TreeNode*> children;
		
		void addChild(TreeNode* newChild);
		string toString();
		string toString(int level);
	
};

#endif