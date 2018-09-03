

#include "include/flatcontainer/flat_tree.h"
#include "include/flatcontainer/flat_set.h"
#include "include/flatcontainer/flat_map.h"
#include <iostream>
#include <iomanip>

#include <set>

struct Test
{
	int a, b;
	friend bool operator <(const Test& lhs, const Test& rhs)
	{
		return lhs.a < rhs.a;
	}
};

//template <typename T, typename U, typename Enable = void>
//class MyIteratorWrapper
//{
//public:
//	MyIteratorWrapper() = delete;
//	MyIteratorWrapper(const MyIteratorWrapper&) = delete;
//	MyIteratorWrapper& operator=(const MyIteratorWrapper&) = delete;
//	~MyIteratorWrapper() = delete;
//};
//
//template <typename T, typename U>
//class MyIteratorWrapper<T, U, std::enable_if_t<std::is_same_v<typename T::value_type, std::remove_const_t<U>>>> : private T
//{
//public:
//	using difference_type = typename T::difference_type;
//	using value_type = U;
//	using pointer = U*;
//	using reference = U&;
//	using iterator_category = typename T::iterator_category;
//
//	MyIteratorWrapper() = default;
//	explicit MyIteratorWrapper(const T& other)
//		: T(other)
//	{
//	}
//	MyIteratorWrapper(const MyIteratorWrapper&) = default;
//	MyIteratorWrapper& operator=(const MyIteratorWrapper&) = default;
//	~MyIteratorWrapper() = default;
//
//	U& operator*()
//	{
//		return *reinterpret_cast<U*>(&T::operator*());
//	}
//
//	const U& operator*() const
//	{
//		return *reinterpret_cast<U*>(&T::operator*());
//	}
//
//	U* operator->()
//	{
//		return reinterpret_cast<U*>(&T::operator*());
//	}
//
//	const U* operator->() const
//	{
//		return reinterpret_cast<U*>(&T::operator*());
//	}
//};
//
//template <typename T, typename U1, typename U2>
//class MyIteratorWrapper<T, std::pair<U1, U2>, typename std::enable_if_t<std::is_same_v<typename T::value_type::first_type, std::remove_cv_t<U1>> && std::is_same_v<typename T::value_type::second_type, std::remove_cv_t<U2>>>> : private T
//{
//public:
//	using difference_type = typename T::difference_type;
//	using value_type = std::pair<U1, U2>;
//	using pointer = std::pair<U1, U2>*;
//	using reference = std::pair<U1, U2>&;
//	using iterator_category = typename T::iterator_category;
//
//	MyIteratorWrapper() = default;
//	explicit MyIteratorWrapper(const T& other)
//		: T(other)
//	{
//	}
//	MyIteratorWrapper(const MyIteratorWrapper&) = default;
//	MyIteratorWrapper& operator=(const MyIteratorWrapper&) = default;
//	~MyIteratorWrapper() = default;
//
//	std::pair<U1, U2>& operator*()
//	{
//		return *reinterpret_cast<std::pair<U1, U2>*>(&T::operator*());
//	}
//
//	const std::pair<U1, U2>& operator*() const
//	{
//		return *reinterpret_cast<std::pair<U1, U2>*>(&T::operator*());
//	}
//
//	std::pair<U1, U2>* operator->()
//	{
//		return reinterpret_cast<std::pair<U1, U2>*>(&T::operator*());
//	}
//
//	const std::pair<U1, U2>* operator->() const
//	{
//		return reinterpret_cast<std::pair<U1, U2>*>(&T::operator*());
//	}
//};

template <typename T, typename U>
struct PairWrapper
{
	PairWrapper(std::pair<T, U>& pair)
		: first(pair.first)
		, second(pair.second)
	{

	}
	const T& first;
	U& second;
};


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