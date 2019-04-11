#include "stdafx.h"
#include "CppUnitTest.h"
#include "include/flatcontainer/flat_map.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace flatcont
{		
	TEST_CLASS(flat_map)
	{
	public:
		
		TEST_METHOD(empty_on_construct)
		{
			mwaack::flat_map<int, int> map;
			Assert::AreEqual(0u, map.size());
		}
		TEST_METHOD(grow_on_insert)
		{
			mwaack::flat_map<int, int> map;
			map.insert(std::pair(1, 1));
			Assert::AreEqual(1u, map.size());
		}
		TEST_METHOD(contained_on_insert)
		{
			mwaack::flat_map<int, int> map;
			map.insert(std::pair(1, 1));
			//Assert::AreNotEqual(map.find(1), map.end());
		}
	};
}