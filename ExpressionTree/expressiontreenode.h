#ifndef EXPRESSIONTREENODE_H
#define EXPRESSIONTREENODE_H

#include <map>
#include <string>
#include <stdio.h>
#include <iostream>
#include <memory>


class TreeNode
{
public:
	virtual ~TreeNode(){}
	virtual double evaluate() = 0;
	virtual TreeNode* derivative(std::string var) = 0;
	virtual void print(std::ostream& os) const = 0;
	friend std::ostream& operator<<(std::ostream& out, const TreeNode& tn);
	// placeholder for derivative()
	static std::map<std::string, double> lookUpTable;

protected:
	std::shared_ptr<TreeNode> leftChild = nullptr;
	std::shared_ptr<TreeNode> rightChild = nullptr;
};

class Constant: public TreeNode
{
public:
	Constant(double val){value = val;}
	double evaluate() override {return value;}
	Constant* derivative(std::string var)override {return new Constant(0.0);}
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Constant& tn);
private:
	double value;
};

class Variable: public TreeNode
{
public:
	Variable(std::string str);
	double evaluate() override;
	Constant* derivative(std::string var)override;
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Variable& tn);
private:
	std::string variableName;
};

class Add: public TreeNode
{
public:
	Add(TreeNode* left, TreeNode* right);
	double evaluate()override{return leftChild->evaluate() + rightChild->evaluate();}
	Add* derivative(std::string var)override{return new Add(this->leftChild->derivative(var), this->rightChild->derivative(var));}
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Add& tn);
};

class Subtract: public TreeNode
{
public:
	Subtract(TreeNode* left, TreeNode* right);
	double evaluate() override {return leftChild->evaluate() - rightChild->evaluate();}
	Subtract* derivative(std::string var)override{return new Subtract(this->leftChild->derivative(var), this->rightChild->derivative(var));}
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Subtract& tn);
};

class Multiply: public TreeNode
{
public:
	Multiply(TreeNode* left, TreeNode* right);
	double evaluate() override {return leftChild->evaluate() * rightChild->evaluate();}
	Add* derivative(std::string var)override;
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Multiply& tn);
};

class Divide: public TreeNode
{
public:
	Divide(TreeNode* left, TreeNode* right);
	double evaluate() override;
	Divide* derivative(std::string var)override;
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Divide& tn);
};

#endif // EXPRESSIONTREENODE_H
