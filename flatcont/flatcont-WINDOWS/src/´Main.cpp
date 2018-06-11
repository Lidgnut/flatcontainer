
#include "include/flat_tree.h"
#include "include/flat_set.h"
#include "include/flat_map.h"
#include <iostream>

#include <set>


struct Test
{
	int a, b;
	friend bool operator <(const Test& lhs, const Test& rhs)
	{
		return lhs.a < rhs.a;
	}
};

int main()
{
	std::cout << "Hello World\n";

	std::set<Test> tads;

	mwaack::flat_set<Test> set;
	mwaack::flat_multiset<Test> multiSet;


	multiSet.insert(Test{ 3, 3 });
	int p = 1;
	multiSet.insert(Test{ p, 1 });
	multiSet.insert(Test{ p, 2 });
	multiSet.insert(Test{ p, 3 });

	multiSet.insert(Test{ 2, 1 });


	set.insert(Test{ 3, 3 });
	//int p = 1;
	set.insert(Test{ p, 1 });
	set.insert(Test{ p, 2 });
	set.insert(Test{ p, 3 });

	set.insert(Test{ 2, 1 });

	//std::cout << set.erase(Test{p}) << '\n';

	
	mwaack::flat_map<int, int> map;
	map.insert(std::make_pair(0, 1));
	map.insert(std::make_pair(1, 2));
	map.insert(std::make_pair(2, 3));
	map.insert(std::make_pair(3, 4));
	map.insert(std::make_pair(2, 5));

	std::cin.get();
}