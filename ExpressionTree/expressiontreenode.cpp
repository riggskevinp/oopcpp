#include "expressiontreenode.h"
#include <iostream>

std::map<std::string, double> TreeNode::lookUpTable = {};

Add::Add(TreeNode* left, TreeNode* right)
{
	leftChild.reset(left);
	rightChild = right;
}

void Add::print(std::ostream &os) const
{
	os << "(" << *this->leftChild << "+" << *this->rightChild << ")";
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

void Variable::print(std::ostream &os) const
{
	os << "(" << this->variableName << ")";
}

Divide::Divide(TreeNode *left, TreeNode *right)
{
	leftChild.reset(left);
	rightChild = right;
}

double Divide::evaluate()
{
	if(0.0 == rightChild->evaluate()){
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

void Divide::print(std::ostream &os) const
{
	os << "(" << *this->leftChild << "/" << *this->rightChild << ")";
}

Multiply::Multiply(TreeNode *left, TreeNode *right)
{
	leftChild.reset(left);
	rightChild = right;
}

void Multiply::print(std::ostream &os) const
{
	os << "(" << *this->leftChild << "*" << *this->rightChild << ")";
}

Subtract::Subtract(TreeNode *left, TreeNode *right)
{
	leftChild.reset(left);
	rightChild = right;
}

void Subtract::print(std::ostream &os) const
{
	os << "(" << *this->leftChild << "-" << *this->rightChild << ")";
}

void Constant::print(std::ostream &os) const
{
	os << "(" << this->value << ")";
}

std::ostream& operator<<(std::ostream &out, const TreeNode& tn) {
	tn.print(out);
	return out;
}
std::ostream& operator<<(std::ostream &out, const Add& tn) {
	tn.print(out);
	return out;
}
std::ostream& operator<<(std::ostream &out, const Subtract& tn) {
	tn.print(out);
	return out;
}
std::ostream& operator<<(std::ostream &out, const Multiply& tn) {
	tn.print(out);
	return out;
}
std::ostream& operator<<(std::ostream &out, const Divide& tn) {
	tn.print(out);
	return out;
}
std::ostream& operator<<(std::ostream &out, const Constant& tn) {
	tn.print(out);
	return out;
}
std::ostream& operator<<(std::ostream &out, const Variable& tn) {
	tn.print(out);
	return out;
}
