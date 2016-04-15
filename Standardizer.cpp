#include "Standardizer.h"

TreeNode* Standardizer :: standardize(TreeNode* node){
	
	TreeNode* head = node;

	for(vector<TreeNode*>::iterator it = node->children.begin(); it != node->children.end(); it++){
		*it = standardize(*it);
	}
	
	if(node->valueIs("let")){
		head = standardizeLet(node);	
	}
	
	return head;
	
}

TreeNode* Standardizer :: standardizeLet(TreeNode* node){
	
	if(!node->children.at(0)->valueIs("=")){
		cout << "Cannot standardize 'let'. Left child is : ";
		cout << node->children.at(0)->value << endl;
		exit(EXIT_FAILURE);
	}
	
	TreeNode* gamma = new TreeNode("gamma");
	TreeNode* lambda = new TreeNode("lambda");
	TreeNode* X = node->children.at(0)->children.at(0);
	TreeNode* E = node->children.at(0)->children.at(1);
	TreeNode* P = node->children.at(1);
	
	lambda->addChild(P);
	lambda->addChild(X);
	gamma->addChild(E);
	gamma->addChild(lambda);

	delete node->children.at(0);
	delete node;
	
	return gamma;
	
}