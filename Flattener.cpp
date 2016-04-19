#include "Flattener.h"

void StructureList :: addStructure(ControlStructure* cs){
	this->list.push_back(cs);
}

string StructureList :: toString(){
	
	ostringstream temp;
	for(vector<ControlStructure*>::iterator it = list.begin(); it != list.end(); it++) {
		temp << (*it)->toString() << " : " << (*it)->toStringExpanded();
		if(it+1 != list.end()){
			temp << endl;
		}
	}
	return temp.str();
	
}

StructureList* Flattener :: genStructureList(TreeNode* node){
	
	//currLambda = 1;
	structureNum = 0;
	StructureList* sl = new StructureList();
	
	ControlStructure* cs0 = new ControlStructure(structureNum);
	structureNum++;
	nodeQueue.push(node);
	structureQueue.push(cs0);

	while(!nodeQueue.empty()){
		flatten(nodeQueue.front(), structureQueue.front(), sl);
		sl->addStructure(structureQueue.front());
		nodeQueue.pop();
		structureQueue.pop();
	}
	
	//sort(sl->list.begin(), sl->list.end(), sl->compare);
	
	return sl;
	
}

/*ControlStructure* Flattener :: flatten(TreeNode* node, StructureList* sl){
	
	ControlStructure* cs = new ControlStructure(structureNum);
	structureNum++;
	
	flatten(node, cs, sl);
	
	return cs;
	
}*/

void Flattener :: flatten(TreeNode* node, ControlStructure* cs, StructureList* sl){
	
	if(node->typeIs("Identifier")){
		cs->pushBack(new IdCU(node->raw));
	}
	else if(node->typeIs("lambda")){
		
		TreeNode* left = node->children.at(0);
		TreeNode* right = node->children.at(1);
		LambdaCU* lam = new LambdaCU(structureNum);
		ControlStructure* nextCs = new ControlStructure(structureNum);
		structureNum++;
		
		if(left->typeIs(",")){
			for(vector<TreeNode*>::iterator it = left->children.begin(); it != left->children.end(); it++) {
				lam->addBindingVar((*it)->raw);
			}
		}
		else{
			lam->addBindingVar(left->raw);	
		}
		
		cs->pushBack(lam);
		
		nodeQueue.push(node->children.at(1));
		structureQueue.push(nextCs);
		
		return;
		
	}
	else if(node->typeIs("gamma")){
		cs->pushBack(new GammaCU());
	}
	else if(node->typeIs("Binop")){
		cs->pushBack(new BinopCU(node->raw));
	}
	else if(node->typeIs("Unop")){
		cs->pushBack(new UnopCU(node->raw));
	}
	else if(node->typeIs("tau")){
		cs->pushBack(new TauCU(node->children.size()));
	}
	else if(node->typeIs("Y")){
		cs->pushBack(new YCU());
	}
	else if(node->typeIs("Integer")){
		cs->pushBack(new IntegerCU(atoi(node->raw.c_str())));
	}
	else if(node->typeIs("String")){
		cs->pushBack(new StringCU(node->raw));
	}
	else if(node->typeIs("nil")){
		cs->pushBack(new TupleCU());
	}
	else if(node->typeIs("dummy")){
		cs->pushBack(new DummyCU());
	}
	else if(node->typeIs("Boolean")){
		
		if(node->rawIs("true")){
			cs->pushBack(new BooleanCU(true));
		}
		else{
			cs->pushBack(new BooleanCU(false));
		}
		
	}
	else if(node->typeIs("->")){
		
		ControlStructure* thenStructure = new ControlStructure(structureNum);
		nodeQueue.push(node->children.at(1));
		structureQueue.push(thenStructure);
		structureNum++;
		cs->pushBack(thenStructure);
		
		ControlStructure* elseStructure = new ControlStructure(structureNum);
		nodeQueue.push(node->children.at(2));
		structureQueue.push(elseStructure);
		structureNum++;
		cs->pushBack(elseStructure);
		
		cs->pushBack(new BetaCU());
		
		flatten(node->children.at(0), cs, sl);
		
		return;
	}
	else{
		cout << "Unexpected node type : " << node->type << endl;	
	}
	
	// ----
	
	for(vector<TreeNode*>::iterator it = node->children.begin(); it != node->children.end(); it++) {
		flatten(*it, cs, sl);
	}
	
}
