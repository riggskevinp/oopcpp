#ifndef TST_PROBABILITIES_H
#define TST_PROBABILITIES_H_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <iostream>
#include <stdexcept>

#include "probabilities.h"

using namespace testing;

TEST(newgt, newgtc)
{
    EXPECT_EQ(1, 1);
    ASSERT_THAT(0, Eq(0));
}

TEST(probabilities, constructor){

    Probabilities t = Probabilities();
    EXPECT_EQ(0,t.getProbability());

    Probabilities p = Probabilities(0.5);
    EXPECT_EQ(0.5,p.getProbability());

}

TEST(probabilities, assignmentOperators){

    Probabilities p = Probabilities();
    p = 0.5;
    EXPECT_EQ(0.5,p.getProbability());

    EXPECT_THROW(p = 3, std::runtime_error);

    Probabilities t = Probabilities();
    t = p;
    EXPECT_EQ(0.5, t.getProbability());
}

TEST(probabilities, andOperator){
    Probabilities p = Probabilities(0.5);
    Probabilities t = Probabilities(0.5);

    EXPECT_EQ(0.25, p&t);
    EXPECT_EQ(0.25,p&p);
}

TEST(probabilities, orOperator){

    Probabilities p = Probabilities(0.5);
    Probabilities t = Probabilities(0.5);

    EXPECT_EQ(0.75, p|t);
    EXPECT_EQ(0.75, p|p);

}

TEST(probabilities, xorOperator){

    Probabilities p = Probabilities(0.5);
    Probabilities t = Probabilities(0.5);

    EXPECT_EQ(0.5, p^t);
    EXPECT_EQ(0.5, p^p);

}

TEST(probabilities, notAOperator){

    Probabilities p = Probabilities(0.75);
    Probabilities t = Probabilities(0.75);

    EXPECT_EQ(0.1875, p-t);
    EXPECT_EQ(0.1875, p-p);

}

TEST(probabilities, notOperator){

    Probabilities p = Probabilities(0.25);
    EXPECT_EQ(0.75, ~p);

}

#endif // TST_NEWGTC_H
