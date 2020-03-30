#ifndef TST_EXPRESSIONTREE_H
#define TST_EXPRESSIONTREE_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <iostream>
#include <stdexcept>
#include <memory>

#include "expressiontreenode.h"

using namespace testing;

TEST(newgt, newgtc)
{
	EXPECT_EQ(1, 1);
	ASSERT_THAT(0, Eq(0));
}

TEST(expressionTree, constantChecks){
	std::shared_ptr<Constant> c(new Constant(3.3));
	EXPECT_EQ(3.3, c->evaluate());
}

TEST(expressionTree, variableChecks){
	Variable* v = new Variable("X");
	TreeNode::lookUpTable.insert_or_assign("X", 2.2);
	EXPECT_EQ(2.2, v->evaluate());
}

TEST(expressionTree, addChecks){
	std::shared_ptr<Add> a(new Add(new Constant(3.3), new Constant(3.3)));
	EXPECT_EQ(6.6, a->evaluate());
	TreeNode::lookUpTable.insert_or_assign("X", 2.2);
	Add* b = new Add(new Variable("X"), new Variable("X"));
	EXPECT_EQ(4.4, b->evaluate());
}

TEST(expressionTree, subtractChecks){
	Subtract* a = new Subtract(new Constant(3.3), new Constant(2.3));
	EXPECT_EQ(1, a->evaluate());
	TreeNode::lookUpTable.insert_or_assign("X", 2.2);
	Subtract* b = new Subtract(new Variable("X"), new Variable("X"));
	EXPECT_EQ(0, b->evaluate());
}

TEST(expressionTree, multiplyChecks){
	Multiply* a = new Multiply(new Constant(3.0), new Constant(3.0));
	EXPECT_EQ(9.0, a->evaluate());
	TreeNode::lookUpTable.insert_or_assign("X", 2.0);
	Multiply* b = new Multiply(new Variable("X"), new Variable("X"));
	EXPECT_EQ(4.0, b->evaluate());
}

TEST(expressionTree, divideChecks){
	Divide* a = new Divide(new Constant(9.0), new Constant(3.0));
	EXPECT_EQ(3.0, a->evaluate());
	TreeNode::lookUpTable.insert_or_assign("X", 2.2);
	Divide* b = new Divide(new Variable("X"), new Variable("X"));
	EXPECT_EQ(1, b->evaluate());
}

TEST(expressionTree, multipleLevles){
	Add* a = new Add(
				new Multiply(new Constant(2.3), new Variable("Xray")),
				new Multiply(new Variable("Yellow"),
						new Subtract(new Variable("Zebra"), new Variable("Xray"))));
	TreeNode::lookUpTable.insert_or_assign("Xray", 2.0);
	TreeNode::lookUpTable.insert_or_assign("Yellow", 3.0);
	TreeNode::lookUpTable.insert_or_assign("Zebra", 5.0);

	EXPECT_EQ(13.6, a->evaluate());
}

TEST(expressionTree, print){
	Add* a = new Add(
				new Multiply(new Constant(2.3), new Variable("Xray")),
				new Multiply(new Variable("Yellow"),
						new Subtract(new Variable("Zebra"), new Variable("Xray"))));
	testing::internal::CaptureStdout();
	std::cout << *a << std::endl;
	std::string output = testing::internal::GetCapturedStdout();
	EXPECT_EQ(output, "(((2.3)*(Xray))+((Yellow)*((Zebra)-(Xray))))\n");
}



#endif // TST_EXPRESSIONTREE_H
