#ifndef TST_ELEVATORSIM_H
#define TST_ELEVATORSIM_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include <iostream>
#include <stdexcept>
#include <memory>
#include <cmath>


using namespace testing;

TEST(newgt, newgtc)
{
	EXPECT_EQ(1, 1);
	ASSERT_THAT(0, Eq(0));
}




#endif // TST_ELEVATORSIM_H
