#pragma once

#include "flat_tree.h"

namespace mwaack
{
	template <typename T, typename FirstCompare>
	struct pair_compare
	{
		FirstCompare m_comp = FirstCompare{};

		pair_compare() = default;

		pair_compare(const FirstCompare& comp)
			: m_comp(comp)
		{ }

		bool operator()(const T& lhs, const T& rhs)
		{
			return m_comp(lhs.first, rhs.first);
		}
	};

	template<typename Key, typename Value, typename KeyCompare = std::less<Key>, typename Allocator = std::allocator<std::pair<Key, Value>>>
	class flat_map : public flat_tree<std::pair<Key, Value>, CompareInfo<KeyCompare, pair_compare<std::pair<Key, Value>, KeyCompare>>, Allocator, false>
	{
		using MyBase = flat_tree<std::pair<Key, Value>, CompareInfo<KeyCompare, pair_compare<std::pair<Key, Value>, KeyCompare>>, Allocator, false>;

	public:
		using key_type = typename Key;
		using mapped_type = typename Value;
		using key_compare = typename MyBase::key_compare;
		using value_compare = typename MyBase::value_compare;
		using value_type = typename MyBase::value_type;
		using size_type = typename MyBase::size_type;
		using difference_type = typename MyBase::difference_type;
		using allocator_type = typename MyBase::allocator_type;
		using reference = typename MyBase::reference;
		using const_reference = typename MyBase::const_reference;
		using pointer = typename MyBase::pointer;
		using const_pointer = typename MyBase::const_pointer;
		using iterator = typename MyBase::iterator;
		using const_iterator = typename MyBase::const_iterator;
		using reverse_iterator = typename std::reverse_iterator<iterator>;
		using const_reverse_iterator = typename std::reverse_iterator<const_iterator>;


		flat_map()
			: MyBase()
		{ }

		explicit flat_map(const KeyCompare& comp, const Allocator& alloc = Allocator()) noexcept
			: MyBase(comp, alloc)
		{ }

		explicit flat_map(const Allocator& alloc) noexcept
			: MyBase(alloc)
		{ }

		template< class InputIt >
		flat_map(InputIt first, InputIt last, const KeyCompare& comp = KeyCompare(), const Allocator& alloc = Allocator())
			: MyBase(first, last, comp, alloc)
		{
		}

		template< class InputIt >
		flat_map(InputIt first, InputIt last, const Allocator& alloc = Allocator())
			: MyBase(first, last, alloc)
		{
		}

		flat_map(const flat_map& other)
			: MyBase(other)
		{ }

		flat_map(const flat_map& other, const Allocator& alloc)
			: MyBase(other, alloc)
		{ }

		flat_map(flat_map&& other) noexcept
			: MyBase(std::forward<flat_map>(other), alloc)
		{ }
		flat_map(flat_map&& other, const Allocator& alloc)
			: MyBase(std::forward<flat_map>(other), alloc)
		{ }

		flat_map(std::initializer_list<value_type> init, const KeyCompare& comp, const Allocator& alloc = Allocator())
			: MyBase(init, comp, alloc)
		{
		}

		flat_map(std::initializer_list<value_type> init, const Allocator& alloc = Allocator())
			: MyBase(init, alloc)
		{
		}
	};

	template<typename Key, typename Value, typename KeyCompare = std::less<Key>, typename Allocator = std::allocator<std::pair<Key, Value>>>
	class flat_multimap : public flat_tree<std::pair<Key, Value>, CompareInfo<KeyCompare, pair_compare<std::pair<Key, Value>, KeyCompare>>, Allocator, true>
	{
		using MyBase = flat_tree<std::pair<Key, Value>, CompareInfo<KeyCompare, pair_compare<std::pair<Key, Value>, KeyCompare>>, Allocator, true>;

	public:
		using key_type = typename Key;
		using mapped_type = typename Value;
		using key_compare = typename MyBase::key_compare;
		using value_compare = typename MyBase::value_compare;
		using value_type = typename MyBase::value_type;
		using size_type = typename MyBase::size_type;
		using difference_type = typename MyBase::difference_type;
		using allocator_type = typename MyBase::allocator_type;
		using reference = typename MyBase::reference;
		using const_reference = typename MyBase::const_reference;
		using pointer = typename MyBase::pointer;
		using const_pointer = typename MyBase::const_pointer;
		using iterator = typename MyBase::iterator;
		using const_iterator = typename MyBase::const_iterator;
		using reverse_iterator = typename std::reverse_iterator<iterator>;
		using const_reverse_iterator = typename std::reverse_iterator<const_iterator>;


		flat_multimap()
			: MyBase()
		{ }

		explicit flat_multimap(const KeyCompare& comp, const Allocator& alloc = Allocator()) noexcept
			: MyBase(comp, alloc)
		{ }

		explicit flat_multimap(const Allocator& alloc) noexcept
			: MyBase(alloc)
		{ }

		template< class InputIt >
		flat_multimap(InputIt first, InputIt last, const KeyCompare& comp = KeyCompare(), const Allocator& alloc = Allocator())
			: MyBase(first, last, comp, alloc)
		{
		}

		template< class InputIt >
		flat_multimap(InputIt first, InputIt last, const Allocator& alloc = Allocator())
			: MyBase(first, last, alloc)
		{
		}

		flat_multimap(const flat_multimap& other)
			: MyBase(other)
		{ }

		flat_multimap(const flat_multimap& other, const Allocator& alloc)
			: MyBase(other, alloc)
		{ }

		flat_multimap(flat_multimap&& other) noexcept
			: MyBase(std::forward<flat_map>(other), alloc)
		{ }
		flat_multimap(flat_multimap&& other, const Allocator& alloc)
			: MyBase(std::forward<flat_map>(other), alloc)
		{ }

		flat_multimap(std::initializer_list<value_type> init, const KeyCompare& comp, const Allocator& alloc = Allocator())
			: MyBase(init, comp, alloc)
		{
		}

		flat_multimap(std::initializer_list<value_type> init, const Allocator& alloc = Allocator())
			: MyBase(init, alloc)
		{
		}
	};
}