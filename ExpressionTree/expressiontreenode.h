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
	virtual void print(std::ostream& os) const = 0;
	friend std::ostream& operator<<(std::ostream& out, const TreeNode& tn);
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
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Variable& tn);
private:
	std::string variableName;
};

class Add: public TreeNode
{
public:
	Add(TreeNode* left, TreeNode* right);
	~Add() override {delete rightChild;}
	double evaluate(){return leftChild->evaluate() + rightChild->evaluate();}
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Add& tn);
};

class Subtract: public TreeNode
{
public:
	Subtract(TreeNode* left, TreeNode* right);
	~Subtract() override {delete rightChild;}
	double evaluate(){return leftChild->evaluate() - rightChild->evaluate();}
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Subtract& tn);
};

class Multiply: public TreeNode
{
public:
	Multiply(TreeNode* left, TreeNode* right);
	~Multiply() override {delete rightChild;}
	double evaluate(){return leftChild->evaluate() * rightChild->evaluate();}
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Multiply& tn);
};

class Divide: public TreeNode
{
public:
	Divide(TreeNode* left, TreeNode* right);
	~Divide() override {delete rightChild;}
	double evaluate();
	void print(std::ostream& os) const override;
	friend std::ostream& operator<<(std::ostream &out, const Divide& tn);
};

#endif // EXPRESSIONTREENODE_H
