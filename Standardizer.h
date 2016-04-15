#ifndef STANDARDIZER_H
#define STANDARDIZER_H

#include <iostream>
#include <stack>
#include "TreeNode.h"

#include <iostream>
#include <fstream>
#include <ctype.h>
#include <stdlib.h>

using namespace std;

class Standardizer {
	
	public:
	
		static TreeNode* standardize(TreeNode* node);
		
	private:
	
		static TreeNode* standardizeLet(TreeNode* node);
		//void standardizeWithin(TreeNode* node);
		//void standardizeFcnForm(TreeNode* node);
		//void standardizeLambda(TreeNode* node);
		//void standardizeAnd(TreeNode* node);
		//void standardizeWhere(TreeNode* node);
		//void standardizeRec(TreeNode* node);
		//void standardizeAtSign(TreeNode* node);
		
};

#endif