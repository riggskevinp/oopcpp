#ifndef TST_NEWGTC_H
#define TST_NEWGTC_H

#include <gtest/gtest.h>
#include <gmock/gmock-matchers.h>

#include "statistics.h"

#include <iostream>

using namespace testing;

TEST(newgt, newgtc)
{
	EXPECT_EQ(1, 1);
	ASSERT_THAT(0, Eq(0));
}

TEST(statistics, average){
	Statistics stats = Statistics();
	stats.add(3.0);
	stats.add(4.0);
	stats.add(5.0);
	ASSERT_EQ(4, stats.getAverage());
	ASSERT_NE(3, stats.getAverage());
}

TEST(statistics, stddev){
	Statistics stats = Statistics();
	stats.add(3.0);
	stats.add(4.0);
	stats.add(5.0);
	ASSERT_EQ(1, stats.getSTD());
	ASSERT_NE(2, stats.getSTD());
}

#endif // TST_NEWGTC_H
