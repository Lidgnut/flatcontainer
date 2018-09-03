#pragma once

#include "flat_tree.h"

namespace mwaack::detail
{
	template <typename T, typename U, typename FirstCompare>
	struct pair_compare
	{
		FirstCompare m_comp = FirstCompare{};

		pair_compare() = default;

		pair_compare(const FirstCompare& comp)
			: m_comp(comp)
		{ }

		bool operator()(const std::pair<T, U>& lhs, const T& rhs) const
		{
			return m_comp(lhs.first, rhs);
		}

		bool operator()(const T& lhs, const std::pair<T, U>& rhs) const
		{
			return m_comp(lhs, rhs.first);
		}

		bool operator()(const std::pair<T, U>& lhs, const std::pair<T, U>& rhs) const
		{
			return m_comp(lhs.first, rhs.first);
		}
	};

	template <typename T, typename U, typename Enable = void>
	class IterWrapper
	{
	public:
		IterWrapper() = delete;
		IterWrapper(const IterWrapper&) = delete;
		IterWrapper& operator=(const IterWrapper&) = delete;
		~IterWrapper() = delete;
	};

	template <typename T, typename U>
	class IterWrapper<T, U, std::enable_if_t<std::is_same_v<typename T::value_type, std::remove_const_t<U>>>> : public T
	{
	public:
		using difference_type = typename T::difference_type;
		using value_type = U;
		using pointer = U * ;
		using reference = U & ;
		using iterator_category = typename T::iterator_category;

		IterWrapper() = default;
		explicit IterWrapper(const T& other)
			: T(other)
		{
		}

		IterWrapper(const IterWrapper&) = default;
		IterWrapper& operator=(const IterWrapper&) = default;
		~IterWrapper() = default;

		U& operator*()
		{
			return *reinterpret_cast<U*>(&T::operator*());
		}

		const U& operator*() const
		{
			return *reinterpret_cast<U*>(&T::operator*());
		}

		U* operator->()
		{
			return reinterpret_cast<U*>(&T::operator*());
		}

		const U* operator->() const
		{
			return reinterpret_cast<U*>(&T::operator*());
		}
	};

	template <typename T, typename U1, typename U2>
	class IterWrapper<T, std::pair<U1, U2>, typename std::enable_if_t<std::is_same_v<typename T::value_type::first_type, std::remove_cv_t<U1>> && std::is_same_v<typename T::value_type::second_type, std::remove_cv_t<U2>>>> : public T
	{
	public:
		using difference_type = typename T::difference_type;
		using value_type = std::pair<U1, U2>;
		using pointer = std::pair<U1, U2>*;
		using reference = std::pair<U1, U2>&;
		using iterator_category = typename T::iterator_category;

		//using T::operator==;
		//using T::operator!=;
		//using T::operator<=;
		//using T::operator>=;
		//using T::operator<;
		//using T::operator>;
		//using T::operator--;
		//using T::operator++;
		//using T::operator+;
		//using T::operator+=;
		//using T::operator-;
		//using T::operator-=;
		//using T::operator[];

		IterWrapper() = default;
		explicit IterWrapper(const T& other)
			: T(other)
		{
		}
		IterWrapper(const IterWrapper&) = default;
		IterWrapper& operator=(const IterWrapper&) = default;
		~IterWrapper() = default;

		std::pair<U1, U2>& operator*()
		{
			return *reinterpret_cast<std::pair<U1, U2>*>(&T::operator*());
		}

		const std::pair<U1, U2>& operator*() const
		{
			return *reinterpret_cast<std::pair<U1, U2>*>(&T::operator*());
		}

		std::pair<U1, U2>* operator->()
		{
			return reinterpret_cast<std::pair<U1, U2>*>(&T::operator*());
		}

		const std::pair<U1, U2>* operator->() const
		{
			return reinterpret_cast<std::pair<U1, U2>*>(&T::operator*());
		}
	};
}
namespace mwaack
{
	template<typename Key, typename Value, typename KeyCompare = std::less<Key>, typename Allocator = std::allocator<std::pair<Key, Value>>>
	class flat_map : public flat_tree<std::pair<Key, Value>, detail::CompareInfo<Key, std::pair<Key, Value>, KeyCompare, detail::pair_compare<Key, Value, KeyCompare>>, Allocator, false>
	{
		using MyBase = flat_tree<std::pair<Key, Value>, detail::CompareInfo<Key, std::pair<Key, Value>, KeyCompare, detail::pair_compare<Key, Value, KeyCompare>>, Allocator, false>;

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
		using iterator = detail::IterWrapper<typename MyBase::iterator, std::pair<const Key, Value>>;
		using const_iterator = detail::IterWrapper<typename MyBase::const_iterator, std::pair<const Key, Value>>;
		using reverse_iterator = detail::IterWrapper<typename std::reverse_iterator<iterator>, std::pair<const Key, Value>>;
		using const_reverse_iterator = detail::IterWrapper<typename std::reverse_iterator<const_iterator>, std::pair<const Key, Value>>;

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
			: MyBase(std::forward<flat_map>(other))
		{ }
		flat_map(flat_map&& other, const Allocator& alloc)
			: MyBase(std::forward<flat_map>(other), alloc)
		{ }

		flat_map& operator=(const flat_map&) = default;
		flat_map& operator=(flat_map&&) = default;

		flat_map(std::initializer_list<value_type> init, const KeyCompare& comp, const Allocator& alloc = Allocator())
			: MyBase(init, comp, alloc)
		{
		}

		flat_map(std::initializer_list<value_type> init, const Allocator& alloc = Allocator())
			: MyBase(init, alloc)
		{
		}


		iterator begin() noexcept
		{
			return iterator(MyBase::begin());
		}
		const_iterator begin() const noexcept
		{
			return const_iterator(MyBase::begin());
		}
		const_iterator cbegin() noexcept
		{
			return const_iterator(MyBase::cbegin());
		}

		iterator end() noexcept
		{
			return iterator(MyBase::end());
		}
		const_iterator end() const noexcept
		{
			return const_iterator(MyBase::end());
		}
		const_iterator cend() noexcept
		{
			return const_iterator(MyBase::cend());
		}

		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(MyBase::rbegin());
		}
		const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator(MyBase::rbegin());
		}
		const_reverse_iterator crbegin() noexcept
		{
			return const_reverse_iterator(MyBase::crbegin());
		}

		reverse_iterator rend() noexcept
		{
			return reverse_iterator(MyBase::rend());
		}
		const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator(MyBase::rend());
		}
		const_reverse_iterator crend() noexcept
		{
			return const_reverse_iterator(MyBase::crend());
		}


		template<typename M>
		std::pair<iterator, bool> insert_or_assign(const key_type& key, M&& obj)
		{
			auto hintIt = std::lower_bound(this->begin(), this->end(), key, [this](const value_type& lhs, const key_type& rhs) {return m_key_compare(lhs.first, rhs); });
			if (hintIt == this->end() || m_key_compare(key, hintIt->first))
			{
				*hintIt = std::forward<M>(obj);
				return std::make_pair(hintIt, false);
			}
			else
			{
				return std::make_pair(this->m_data.insert(hintIt, value_type{ key, std::forward<M>(obj) }), true);
			}
		}

		template<typename M>
		std::pair<iterator, bool> insert_or_assign(key_type&& key, M&& obj)
		{
			auto hintIt = std::lower_bound(this->begin(), this->end(), key, [this](const value_type& lhs, const key_type& rhs) {return m_key_compare(lhs.first, rhs); });
			if (hintIt == this->end() || m_key_compare(key, hintIt->first))
			{
				return std::make_pair(this->m_data.insert(hintIt, value_type{ std::forward<key_type>(key), std::forward<M>(obj) }), true);
			}
			else
			{
				hintIt->second = std::forward<M>(obj);
				return std::make_pair(hintIt, false);
			}
		}


		template<typename... Args>
		std::pair<iterator, bool> try_emplace(const key_type& k, Args&&... args)
		{
			return this->insert(value_type{ std::piecewise_construct, std::forward_as_tuple(k), std::forward_as_tuple(std::forward<Args>(args)...) });
		}

		template<typename... Args>
		std::pair<iterator, bool> try_emplace(key_type&& k, Args&&... args)
		{
			return this->insert(value_type{ std::piecewise_construct, std::forward_as_tuple(std::forward<key_type>(k)), std::forward_as_tuple(std::forward<Args>(args)...) });
		}

		template<typename... Args>
		iterator try_emplace(const_iterator hint, const key_type& k, Args&&... args)
		{
			return this->insert(hint, value_type{ std::piecewise_construct, std::forward_as_tuple(k), std::forward_as_tuple(std::forward<Args>(args)...) });
		}

		template<typename... Args>
		iterator try_emplace(const_iterator hint, key_type&& k, Args&&... args)
		{
			return this->insert(hint, value_type{ std::piecewise_construct, std::forward_as_tuple(std::forward<key_type>(k)), std::forward_as_tuple(std::forward<Args>(args)...) });
		}

	};

	template<typename Key, typename Value, typename KeyCompare = std::less<Key>, typename Allocator = std::allocator<std::pair<Key, Value>>>
	class flat_multimap : public flat_tree<std::pair<Key, Value>, detail::CompareInfo<Key, std::pair<Key, Value>, KeyCompare, detail::pair_compare<Key, Value, KeyCompare>>, Allocator, true>
	{
		using MyBase = flat_tree < std::pair<Key, Value>, detail::CompareInfo < Key, std::pair<Key, Value>, KeyCompare, detail::pair_compare<Key, Value, KeyCompare >> , Allocator, true > ;

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
		using iterator = detail::IterWrapper<typename MyBase::iterator, std::pair<const Key, Value>>;
		using const_iterator = detail::IterWrapper<typename MyBase::const_iterator, std::pair<const Key, Value>>;
		using reverse_iterator = detail::IterWrapper<typename std::reverse_iterator<iterator>, std::pair<const Key, Value>>;
		using const_reverse_iterator = detail::IterWrapper<typename std::reverse_iterator<const_iterator>, std::pair<const Key, Value>>;


		flat_multimap()
			//: MyBase()
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
			: MyBase(std::forward<flat_multimap>(other))
		{ }
		flat_multimap(flat_multimap&& other, const Allocator& alloc)
			: MyBase(std::forward<flat_multimap>(other), alloc)
		{ }

		flat_multimap& operator=(const flat_multimap&) = default; 
		flat_multimap& operator=(flat_multimap&&) = default;

		flat_multimap(std::initializer_list<value_type> init, const KeyCompare& comp, const Allocator& alloc = Allocator())
			: MyBase(init, comp, alloc)
		{
		}

		flat_multimap(std::initializer_list<value_type> init, const Allocator& alloc = Allocator())
			: MyBase(init, alloc)
		{
		}

		iterator begin() noexcept
		{
			return iterator(MyBase::begin());
		}
		const_iterator begin() const noexcept
		{
			return const_iterator(MyBase::begin());
		}
		const_iterator cbegin() noexcept
		{
			return const_iterator(MyBase::cbegin());
		}

		iterator end() noexcept
		{
			return iterator(MyBase::end());
		}
		const_iterator end() const noexcept
		{
			return const_iterator(MyBase::end());
		}
		const_iterator cend() noexcept
		{
			return const_iterator(MyBase::cend());
		}

		reverse_iterator rbegin() noexcept
		{
			return reverse_iterator(MyBase::rbegin());
		}
		const_reverse_iterator rbegin() const noexcept
		{
			return const_reverse_iterator(MyBase::rbegin());
		}
		const_reverse_iterator crbegin() noexcept
		{
			return const_reverse_iterator(MyBase::crbegin());
		}

		reverse_iterator rend() noexcept
		{
			return reverse_iterator(MyBase::rend());
		}
		const_reverse_iterator rend() const noexcept
		{
			return const_reverse_iterator(MyBase::rend());
		}
		const_reverse_iterator crend() noexcept
		{
			return const_reverse_iterator(MyBase::crend());
		}
	};
}