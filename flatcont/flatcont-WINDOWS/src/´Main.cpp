

#include "include/flatcontainer/flat_tree.h"
#include "include/flatcontainer/flat_set.h"
#include "include/flatcontainer/flat_map.h"
#include <iostream>
#include <iomanip>


int main(int argc, char** argv)
{
	std::cout << "Hello World\n";
	
	mwaack::flat_map<int, int> map;
	for (int i = 0; i < 100; map.emplace(i, i), ++i);
	for (auto& iter : map)
	{
		std::cout << std::setw(8) << iter.first + iter.second;
	}
	std::cin.get();
}