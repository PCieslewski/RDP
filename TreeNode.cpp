#include "TreeNode.h"

TreeNode :: TreeNode(){
	value = "";
}

TreeNode :: TreeNode(string value){
	this->value = value;
}

void TreeNode :: addChild(TreeNode* newChild){
	//children.push_back(newChild);
	children.insert(children.begin(), newChild);
}

string TreeNode :: toString(){
	string temp = "";
	temp = temp + value;
	
	for(int i = 0; i < children.size(); i++){
		temp = temp + children.at(i)->toString(1);
	}
	
	if(children.size() == 0){
		temp = temp + "\n";
	}
	
	return temp;
}

string TreeNode :: toString(int level){
	
	string temp = "";
	
	for(int i=0; i<level; i++){
		temp = temp + '.';	
	}
	temp = "\n" + temp + value;

	for(int i = 0; i < children.size(); i++){
		temp = temp + children.at(i)->toString(level + 1);
	}
	
	return temp;
	
}