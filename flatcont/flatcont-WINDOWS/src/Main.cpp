

#include "include/flatcontainer/flat_tree.h"
#include "include/flatcontainer/flat_set.h"
#include "include/flatcontainer/flat_map.h"
#include "include/flatcontainer/flat_hash_table.h"
#include <iostream>
#include <unordered_set>
#include <iomanip>


int main(int argc, char** argv)
{
	//std::cout <<  << '\n';

	mwaack::flat_map<int, int> map;
	for (int i = 0; i < 100; ++i)
	{
		map.emplace(i, i);
	}

	for (auto& val : map)
	{
		std::cout << val.second;
	}

	//for (int i = 0; i < 1'000; ++i)
	//{
	//	std::cout << std::setw(4) << i << ':' << std::setw(4) << mwaack::Primes::isPrime(i) << '\n';
	//}

	std::cin.get();
}