#pragma once

#include "flat_tree.h"

namespace mwaack
{
	template<
		typename Key,
		typename Compare = std::less<Key>,
		typename Allocator = std::allocator<Key>>
		class flat_set : public flat_tree<Key, detail::CompareInfo<Key, Key, Compare, Compare>, Allocator, false>
	{
		using MyBase = flat_tree<Key, detail::CompareInfo<Key, Key, Compare, Compare>, Allocator, false>;

	public:
		using key_type = typename MyBase::key_type;
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


		flat_set()
			: MyBase()
		{ }

		explicit flat_set(const Compare& comp, const Allocator& alloc = Allocator()) noexcept
			: MyBase(comp, alloc)
		{ }

		explicit flat_set(const Allocator& alloc) noexcept
			: MyBase(alloc)
		{ }

		template< class InputIt >
		flat_set(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: MyBase(first, last, comp, alloc)
		{
			//std::copy(first, last, std::inserter(*this, this->end()));
		}

		template< class InputIt >
		flat_set(InputIt first, InputIt last, const Allocator& alloc = Allocator())
			: MyBase(first, last, alloc)
		{
			//std::copy(first, last, std::inserter(*this, this->end()));
		}

		flat_set(const flat_set& other)
			: MyBase(other)
		{ }

		flat_set(const flat_set& other, const Allocator& alloc)
			: MyBase(other, alloc)
		{ }

		flat_set(flat_set&& other) noexcept
			: MyBase(std::move(other))
		{ }
		flat_set(flat_set&& other, const Allocator& alloc)
			: MyBase(std::move(other), alloc)
		{ }

		flat_set& operator=(const flat_set&) = default;
		flat_set& operator=(flat_set&&) = default;

		flat_set(std::initializer_list<value_type> init, const Compare& comp, const Allocator& alloc = Allocator())
			: MyBase(init, comp, alloc)
		{
			//std::copy(init.begin(), init.end(), std::inserter(*this, this->end()));
		}

		flat_set(std::initializer_list<value_type> init, const Allocator& alloc = Allocator())
			: MyBase(init, alloc)
		{
			//std::copy(init.begin(), init.end(), std::inserter(*this, this->end()));
		}
	};


	template<
		typename Key,
		typename Compare = std::less<Key>,
		typename Allocator = std::allocator<Key>>
		class flat_multiset : public flat_tree<Key, detail::CompareInfo<Key, Key, Compare, Compare>, Allocator, true>
	{

		using MyBase = flat_tree<Key, detail::CompareInfo<Key, Key, Compare, Compare>, Allocator, true>;

	public:
		using key_type = typename MyBase::key_type;
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


		flat_multiset()
			: MyBase()
		{ }

		explicit flat_multiset(const Compare& comp, const Allocator& alloc = Allocator()) noexcept
			: MyBase(comp, alloc)
		{ }

		explicit flat_multiset(const Allocator& alloc) noexcept
			: MyBase(alloc)
		{ }

		template< class InputIt >
		flat_multiset(InputIt first, InputIt last, const Compare& comp, const Allocator& alloc = Allocator())
			: MyBase(first, last, comp, alloc)
		{
			//std::copy(first, last, std::inserter(*this, this->end()));
		}

		template< class InputIt >
		flat_multiset(InputIt first, InputIt last, const Allocator& alloc = Allocator())
			: MyBase(first, last, alloc)
		{
			//std::copy(first, last, std::inserter(*this, this->end()));
		}

		flat_multiset(const flat_multiset& other)
			: MyBase(other)
		{ }

		flat_multiset(const flat_multiset& other, const Allocator& alloc)
			: MyBase(other, alloc)
		{ }

		flat_multiset(flat_multiset&& other) noexcept
			: MyBase(std::move(other))
		{ }
		flat_multiset(flat_multiset&& other, const Allocator& alloc)
			: MyBase(std::move(other), alloc)
		{ }

		flat_multiset& operator=(const flat_multiset&) = default;
		flat_multiset& operator=(flat_multiset&&) = default;

		flat_multiset(std::initializer_list<value_type> init, const Compare& comp, const Allocator& alloc = Allocator())
			: MyBase(init, comp, alloc)
		{
			//std::copy(init.begin(), init.end(), std::inserter(*this, this->end()));
		}

		flat_multiset(std::initializer_list<value_type> init, const Allocator& alloc = Allocator())
			: MyBase(init, alloc)
		{
			//std::copy(init.begin(), init.end(), std::inserter(*this, this->end()));
		}
	};
}