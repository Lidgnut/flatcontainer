#pragma once

#include "flat_tree.h"

namespace mwaack
{
	template <typename T, typename FirstCompare>
	struct pair_compare
	{
		FirstCompare m_comp;

		pair_compare(const FirstCompare& comp)
			: m_comp(comp)
		{ }

		bool operator()(const T& lhs, const T& rhs)
		{
			return m_comp(lhs.first, rhs.first);
		}
	};

	template<typename Key, typename Value, typename KeyCompare, typename Allocator>
	class flat_map : public flat_tree<std::pair<Key, Value>, pair_compare<std::pair<Key, Value>, KeyCompare>, Allocator, false>
	{

	};
}