#ifndef EXPRESSIONTREENODE_H
#define EXPRESSIONTREENODE_H

#include <map>
#include <string>
#include <stdio.h>



class TreeNode
{
public:
	virtual ~TreeNode(){}
	virtual double evaluate() = 0;
	// placeholder for operator<<()
	// placeholder for derivative()
	static std::map<std::string, double> lookUpTable;

protected:
	TreeNode* leftChild = nullptr;
	TreeNode* rightChild = nullptr;
};

class Constant: public TreeNode
{
public:
	Constant(double val){value = val;}
	double evaluate() override {return value;}
private:
	double value;
};

class Variable: public TreeNode
{
public:
	Variable(std::string str);
	double evaluate() override;
private:
	std::string variableName;
};

class Add: public TreeNode
{
public:
	Add(TreeNode* left, TreeNode* right);
	double evaluate(){return leftChild->evaluate() + rightChild->evaluate();}
};

class Subtract: public TreeNode
{
public:
	Subtract(TreeNode* left, TreeNode* right);
	double evaluate(){return leftChild->evaluate() - rightChild->evaluate();}
};

class Multiply: public TreeNode
{
public:
	Multiply(TreeNode* left, TreeNode* right);
	double evaluate(){return leftChild->evaluate() * rightChild->evaluate();}
};

class Divide: public TreeNode
{
public:
	Divide(TreeNode* left, TreeNode* right);
	double evaluate();
};

#endif // EXPRESSIONTREENODE_H
