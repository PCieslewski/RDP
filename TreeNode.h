#ifndef TREENODE_H
#define TREENODE_H

#include <iostream>
#include <vector>
using namespace std;

class TreeNode {
	
	public:
	
		TreeNode(string value);
		TreeNode(string value, string type, string raw);
	
		string type;
		string value;
		string raw;
		vector<TreeNode*> children;
		
		void addChild(TreeNode* newChild);
		string toString();
		string toString(int level);
	
		bool valueIs(string value);
		bool typeIs(string value);
		bool rawIs(string value);
	
};

#endif