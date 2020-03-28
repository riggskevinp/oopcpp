#ifndef EXPRESSIONTREENODE_H
#define EXPRESSIONTREENODE_H

#include <map>
#include <string>
#include <stdio.h>
#include <memory>


class TreeNode
{
public:
	virtual ~TreeNode(){}
	virtual double evaluate() = 0;
	// placeholder for operator<<()
	// placeholder for derivative()
	static std::map<std::string, double> lookUpTable;

protected:
	std::shared_ptr<TreeNode> leftChild = nullptr;
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
	~Add(){delete rightChild;}
	double evaluate(){return leftChild->evaluate() + rightChild->evaluate();}
};

class Subtract: public TreeNode
{
public:
	Subtract(TreeNode* left, TreeNode* right);
	~Subtract(){delete rightChild;}
	double evaluate(){return leftChild->evaluate() - rightChild->evaluate();}
};

class Multiply: public TreeNode
{
public:
	Multiply(TreeNode* left, TreeNode* right);
	~Multiply(){delete rightChild;}
	double evaluate(){return leftChild->evaluate() * rightChild->evaluate();}
};

class Divide: public TreeNode
{
public:
	Divide(TreeNode* left, TreeNode* right);
	~Divide(){delete rightChild;}
	double evaluate();
};

#endif // EXPRESSIONTREENODE_H
