#include "Standardizer.h"

TreeNode* Standardizer :: standardize(TreeNode* node){
	
	TreeNode* head = node;

	for(vector<TreeNode*>::iterator it = node->children.begin(); it != node->children.end(); it++){
		*it = standardize(*it);
	}
	
	if(node->valueIs("let")){
		head = standardizeLet(node);	
	}
	else if(node->valueIs("within")){
		head = standardizeWithin(node);
	}
	else if(node->valueIs("function_form")){
		head = standardizeFcnForm(node);
	}
	else if(node->valueIs("lambda")){
		head = standardizeLambda(node);
	}
	else if(node->valueIs("and")){
		head = standardizeAnd(node);
	}
	else if(node->valueIs("where")){
		head = standardizeWhere(node);
	}
	else if(node->valueIs("rec")){
		head = standardizeRec(node);
	}
	else if(node->valueIs("@")){
		head = standardizeAtSign(node);
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

TreeNode* Standardizer :: standardizeWithin(TreeNode* node){

	if((node->children.at(0)->valueIs("=") && node->children.at(1)->valueIs("=")) != true){
		cout << "Cannot standardize 'within'. Both children are not '='";
		exit(EXIT_FAILURE);
	}
	
	TreeNode* equals = new TreeNode("=");
	TreeNode* gamma = new TreeNode("gamma");
	TreeNode* lambda = new TreeNode("lambda");
	TreeNode* X1 = node->children.at(0)->children.at(0);
	TreeNode* E1 = node->children.at(0)->children.at(1);
	TreeNode* X2 = node->children.at(1)->children.at(0);
	TreeNode* E2 = node->children.at(1)->children.at(1);
	
	lambda->addChild(E2);
	lambda->addChild(X1);
	gamma->addChild(E1);
	gamma->addChild(lambda);
	equals->addChild(gamma);
	equals->addChild(X2);
	
	delete node->children.at(0);
	delete node->children.at(1);
	delete node;
	
	return equals;
	
}

TreeNode* Standardizer :: standardizeFcnForm(TreeNode* node){
	
	int numArgs = node->children.size()-2;
	TreeNode* equals = new TreeNode("=");
	TreeNode* lambda[numArgs];
	TreeNode* P = node->children.at(0);
	TreeNode* E = node->children.at(numArgs+1);
	
	lambda[numArgs-1] = new TreeNode("lambda");
	lambda[numArgs-1]->addChild(E);
	lambda[numArgs-1]->addChild(node->children.at(numArgs));
	
	for(int i = numArgs-2; i >= 0; i--){
	
		lambda[i] = new TreeNode("lambda");
		lambda[i]->addChild(lambda[i+1]);
		lambda[i]->addChild(node->children.at(i+1));
		
	}
	
	equals->addChild(lambda[0]);
	equals->addChild(P);
	
	delete node;
	
	return equals;
	
}

TreeNode* Standardizer :: standardizeLambda(TreeNode* node){
	
	//Unchecked
	
	if(node->children.size() == 2){
		return node;	
	}
	
	int numArgs = node->children.size() - 1;
	TreeNode* E = node->children.at(numArgs);
	TreeNode* lambda[numArgs];
	
	lambda[numArgs-1] = new TreeNode("lambda");
	lambda[numArgs-1]->addChild(E);
	lambda[numArgs-1]->addChild(node->children.at(numArgs-1));

	for(int i = numArgs-2; i >= 0; i--){
		
		lambda[i] = new TreeNode("lambda");
		lambda[i]->addChild(lambda[i+1]);
		lambda[i]->addChild(node->children.at(i));
		
	}
	
	delete node;
	
	return lambda[0];
	
}

TreeNode* Standardizer :: standardizeAnd(TreeNode* node){
	
	//Unchecked
		
	if(node->children.size() < 2){
		return node;	
	}
	
	TreeNode* equals = new TreeNode("=");
	TreeNode* comma = new TreeNode(",");
	TreeNode* tau = new TreeNode("tau");
	
	for(int i = node->children.size() - 1; i >= 0; i--){
		
		comma->addChild(node->children.at(i)->children.at(0));
		tau->addChild(node->children.at(i)->children.at(1));
		delete node->children.at(i);
		
	}
	
	equals->addChild(tau);
	equals->addChild(comma);
	
	delete node;
	
	return equals;
	
}

TreeNode* Standardizer :: standardizeWhere(TreeNode* node){
	
	//Unchecked

	TreeNode* gamma = new TreeNode("gamma");
	TreeNode* lambda = new TreeNode("lambda");
	
	TreeNode* P = node->children.at(0);
	TreeNode* X = node->children.at(1)->children.at(0);
	TreeNode* E = node->children.at(1)->children.at(1);
	
	lambda->addChild(P);
	lambda->addChild(X);
	gamma->addChild(E);
	gamma->addChild(lambda);
	
	delete node->children.at(1);
	delete node;
	
	return gamma;
	
}

TreeNode* Standardizer :: standardizeRec(TreeNode* node){

	//Unchecked
	
	TreeNode* equals = new TreeNode("=");
	TreeNode* gamma = new TreeNode("gamma");
	TreeNode* lambda = new TreeNode("lambda");
	TreeNode* ystar = new TreeNode("<Y*>", "Y", "Y");
	
	TreeNode* X = node->children.at(0)->children.at(0);
	TreeNode* E = node->children.at(0)->children.at(1);
	
	lambda->addChild(E);
	lambda->addChild(X);
	gamma->addChild(lambda);
	gamma->addChild(ystar);
	equals->addChild(gamma);
	equals->addChild(X);
	
	delete node->children.at(0);
	delete node;
	
	return equals;
	
}

TreeNode* Standardizer :: standardizeAtSign(TreeNode* node){
	
	//Unchecked
	
	TreeNode* gamma1 = new TreeNode("gamma");
	TreeNode* gamma2 = new TreeNode("gamma");
	
	TreeNode* E1 = node->children.at(0);
	TreeNode* N = node->children.at(1);
	TreeNode* E2 = node->children.at(2);
	
	gamma2->addChild(E1);
	gamma2->addChild(N);
	gamma1->addChild(E2);
	gamma1->addChild(gamma2);
	
	delete node;
	
	return gamma1;
	
}

