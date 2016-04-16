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
		static TreeNode* standardizeWithin(TreeNode* node);
		static TreeNode* standardizeFcnForm(TreeNode* node);
		static TreeNode* standardizeLambda(TreeNode* node);
		static TreeNode* standardizeAnd(TreeNode* node);
		static TreeNode* standardizeWhere(TreeNode* node);
		static TreeNode* standardizeRec(TreeNode* node);
		static TreeNode* standardizeAtSign(TreeNode* node);
		
};

#endif