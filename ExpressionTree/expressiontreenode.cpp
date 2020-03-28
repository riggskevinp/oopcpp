#include "expressiontreenode.h"
#include <iostream>

std::map<std::string, double> TreeNode::lookUpTable = {};

Add::Add(TreeNode *left, TreeNode *right)
{
	leftChild = left;
	rightChild = right;
}

Variable::Variable(std::string str):
	variableName(str)
{
	lookUpTable.try_emplace(str, 1.0);
}

double Variable::evaluate()
{
	auto res = lookUpTable.find(variableName);
	return res->second;
}

Divide::Divide(TreeNode *left, TreeNode *right)
{
	leftChild = left;
	rightChild = right;
}

double Divide::evaluate()
{
	if(rightChild->evaluate() == 0){
		std::cerr << "Tried to divide by zero" << std::endl;
		return 1;
	} else{
		return leftChild->evaluate() / rightChild->evaluate();
	}
	// or should I use the option below?
	/*
	try {
		return leftChild->evaluate() / rightChild->evaluate();
	} catch (std::runtime_error& e) {
		std::cerr << "Exception occurred" << std::endl << e.what() << std::endl;
	}
	*/
}

Multiply::Multiply(TreeNode *left, TreeNode *right)
{
	leftChild = left;
	rightChild = right;
}

Subtract::Subtract(TreeNode *left, TreeNode *right)
{
	leftChild = left;
	rightChild = right;
}
