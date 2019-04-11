#include "pch.h"
#include "include\flatcontainer\flat_map.h"

TEST(flat_map, empty_on_construct)
{
	mwaack::flat_map<int, int> map;
	EXPECT_EQ(map.size(), 0);
}