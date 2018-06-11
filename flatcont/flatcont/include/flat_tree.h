#pragma once

#include <vector>
#include <algorithm>

namespace mwaack
{
	template<typename T,
		typename Compare,
		typename Allocator,
		bool IsMulti>
	class flat_tree
	{
		using data_type = std::vector<T, Allocator>;
	public:
		using key_type = T;
		using key_compare = Compare;
		using value_compare = Compare;
		using value_type = T;
		using size_type = typename data_type::size_type;
		using difference_type = typename data_type::difference_type;
		using allocator_type = typename data_type::allocator_type;
		using reference = typename data_type::reference;
		using const_reference = typename data_type::const_reference;
		using pointer = typename data_type::pointer;
		using const_pointer = typename data_type::const_pointer;
		using iterator = typename data_type::iterator;
		using const_iterator = typename data_type::const_iterator;
		using reverse_iterator = typename std::reverse_iterator<iterator>;
		using const_reverse_iterator = typename std::reverse_iterator<const_iterator>;
	private:
		data_type m_data;
		value_compare m_value_comp;

	public:
		flat_tree()
			: m_data()
		{ }

		explicit flat_tree(const Compare& comp, const Allocator& alloc = Allocator()) noexcept
			: m_data(alloc)
			, m_value_comp(comp)
		{ }

		explicit flat_tree(const Allocator& alloc) noexcept
			: m_data(alloc)
		{ }

		template< class InputIt >
		flat_tree(InputIt first, InputIt last, const Compare& comp = Compare(), const Allocator& alloc = Allocator())
			: m_data(comp, alloc)
		{
			std::copy(first, last, std::inserter(*this, end()));
		}

		template< class InputIt >
		flat_tree(InputIt first, InputIt last, const Allocator& alloc = Allocator())
			: m_data(alloc)
		{
			std::copy(first, last, std::inserter(*this, end()));
		}

		flat_tree(const flat_tree& other)
			: m_data(other.m_data)
		{ }

		flat_tree(const flat_tree& other, const Allocator& alloc)
			: m_data(other.m_data, alloc)
		{ }

		flat_tree(flat_tree&& other) noexcept
			: m_data(std::move(other.m_data))
		{ }
		flat_tree(flat_tree&& other, const Allocator& alloc)
			: m_data(std::move(other.m_data))
		{ }

		flat_tree(std::initializer_list<value_type> init, const Compare& comp, const Allocator& alloc = Allocator())
			: m_data(alloc)
			, m_value_comp(comp)
		{
			std::copy(init.begin(), init.end(), std::inserter(*this, end()));
		}

		flat_tree(std::initializer_list<value_type> init, const Allocator& alloc = Allocator())
			: m_data(alloc)
		{
			std::copy(init.begin(), init.end(), std::inserter(*this, end()));
		}

		iterator begin() noexcept
		{
			return m_data.begin();
		}
		const_iterator begin() const noexcept
		{
			return m_data.begin();
		}
		const_iterator cbegin() noexcept
		{
			return m_data.cbegin();
		}

		iterator end() noexcept
		{
			return m_data.end();
		}
		const_iterator end() const noexcept
		{
			return m_data.end();
		}
		const_iterator cend() noexcept
		{
			return m_data.cend();
		}

		reverse_iterator rbegin() noexcept
		{
			return m_data.rbegin();
		}
		const_reverse_iterator rbegin() const noexcept
		{
			return m_data.rbegin();
		}
		const_iterator rcbegin() noexcept
		{
			return m_data.crbegin();
		}

		reverse_iterator rend() noexcept
		{
			return m_data.rend();
		}
		const_reverse_iterator rend() const noexcept
		{
			return m_data.rend();
		}
		const_reverse_iterator rcend() noexcept
		{
			return m_data.rcend();
		}

		bool empty() const
		{
			return m_data.empty();
		}

		size_type size() const
		{
			return m_data.size();
		}

		size_type max_size() const
		{
			return m_data.max_size();
		}

		void clear()
		{
			m_data.clear();
		}

		auto insert(const value_type& value)
		{
			auto hintIt = this->lower_bound(value);
			if constexpr(IsMulti)
			{
				return this->insert(hintIt, value);
			}
			else
			{
				if (hintIt == m_data.end() || m_value_comp(value, *hintIt))
				{
					return std::make_pair(this->insert(hintIt, value), true);
				}
				else
				{
					return std::make_pair(hintIt, false);
				}
			}
		}

		auto insert(value_type&& value)
		{
			auto hintIt = this->lower_bound(value);
			if constexpr(IsMulti)
			{
				return this->insert(hintIt, std::forward<value_type>(value));
			}
			else
			{
				if (hintIt == m_data.end() || m_value_comp(value, *hintIt))
				{
					return std::make_pair(this->insert(hintIt, std::forward<value_type>(value)), true);
				}
				else
				{
					return std::make_pair(hintIt, false);
				}
			}
		}

		iterator insert(const_iterator hint, const value_type& value)
		{
			if constexpr(IsMulti)
			{
				if (((hint == m_data.end()) ? true : (m_value_comp(value, *hint) || (!m_value_comp(value, *hint) && !m_value_comp(*hint, value))))
					&& ((hint == m_data.begin()) ? true : m_value_comp(*(hint - 1), value)))
				{
					return m_data.insert(hint, value);
				}
			}
			else
			{
				if (((hint == m_data.end()) ? true : m_value_comp(value, *hint))
					&& ((hint == m_data.begin()) ? true : m_value_comp(*(hint - 1), value)))
				{
					return m_data.insert(hint, value);
				}
				else
				{
					return insert(value).first;
				}
			}
		}

		iterator insert(const_iterator hint, value_type&& value)
		{
			if constexpr(IsMulti)
			{
				if (((hint == m_data.end()) ? true : (m_value_comp(value, *hint) || (!m_value_comp(value, *hint) && !m_value_comp(*hint, value))))
					&& ((hint == m_data.begin()) ? true : m_value_comp(*(hint - 1), value)))
				{
					return m_data.insert(hint, std::forward<value_type>(value));
				}
				else
				{
					return this->insert(std::forward<value_type>(value));
				}
			}
			else
			{
				if (((hint == m_data.end()) ? true : m_value_comp(value, *hint))
					&& ((hint == m_data.begin()) ? true : m_value_comp(*(hint - 1), value)))
				{
					return m_data.insert(hint, std::forward<value_type>(value));
				}
				else
				{
					return insert(std::forward<value_type>(value)).first;
				}
			}
		}


		template<typename InputIt>
		void insert(InputIt first, InputIt last)
		{
			const size_type currSize = m_data.size();
			for (InputIt curr = first; curr != last; ++curr)
				m_data.emplace_back(*curr);
			std::inplace_merge(m_data.begin(), m_data.begin() + currSize, m_data.end());
		}

		void insert(std::initializer_list<value_type> ilist)
		{
			const size_type currSize = m_data.size();
			for (const auto& value : ilist)
				m_data.emplace_back(value);
			std::inplace_merge(m_data.begin(), m_data.begin() + currSize, m_data.end());
		}

		template<typename... Args>
		std::pair<iterator, bool> emplace(Args&&... args)
		{
			return insert(value_type{ std::forward<Args>(args)... });
		}

		template<typename... Args>
		iterator emplace_hint(const_iterator hint, Args&&... args)
		{
			return insert(hint, value_type{ std::forward<Args>(args)... });
		}

		iterator erase(iterator pos)
		{
			return m_data.erase(pos);
		}

		iterator erase(const_iterator pos)
		{
			return m_data.erase(pos);
		}

		iterator erase(const_iterator first, const_iterator last)
		{
			return m_data.erase(first, last);
		}

		size_type erase(const key_type& key)
		{
			auto eraseIt = this->equal_range(key);
			const size_type erasedElems = eraseIt.second - eraseIt.first;;
			m_data.erase(eraseIt.first, eraseIt.second);
			return erasedElems;
		}


		void swap(flat_tree& other) noexcept(m_data.swap(other))
		{
			m_data.swap(other);
		}

		size_type count(const value_type& value) const
		{
			const auto range = this->equal_range(value);
			return range.second - range.first;
		}

		template<typename K, typename = Compare::is_transparent>
		size_type count(const K& x) const
		{
			return count(static_cast<typename Compare::is_transparent>(key));
		}

		iterator find(const key_type& key)
		{
			auto hintIt = std::lower_bound(m_data.begin(), m_data.end(), key, m_value_comp);
			if (hintIt == m_data.end() || m_value_comp(key, *hintIt))
			{
				return m_data.end();
			}
			else
			{
				return hintIt;
			}
		}

		const_iterator find(const key_type& key) const
		{
			auto hintIt = std::lower_bound(m_data.begin(), m_data.end(), key, m_value_comp);
			if (hintIt == m_data.end() || m_value_comp(key, *hintIt))
			{
				return m_data.end();
			}
			else
			{
				return hintIt;
			}
		}

		template<typename K, typename = Compare::is_tranparent>
		iterator find(const K& key)
		{
			return find(static_cast<typename Compare::is_transparent>(key));
		}

		template<typename K, typename = Compare::is_tranparent>
		iterator find(const K& key) const
		{
			return find(static_cast<typename Compare::is_transparent>(key));
		}



		std::pair<iterator, iterator> equal_range(const key_type& key)
		{
			return std::equal_range(m_data.begin(), m_data.end(), key, m_value_comp);
		}

		std::pair<const_iterator, const_iterator> equal_range(const key_type& key) const
		{
			return std::equal_range(m_data.begin(), m_data.end(), key, [this](const value_type& lhs, const key_type& rhs) {return m_key_compare(lhs.first, rhs); });
		}

		template<typename K, typename = Compare::is_tranparent>
		std::pair<iterator, iterator> equal_range(const K& key)
		{
			return std::equal_range(m_data.begin(), m_data.end(), key, m_value_comp);
		}

		template<typename K, typename = Compare::is_tranparent>
		std::pair<const_iterator, const_iterator> equal_range(const K& key) const
		{
			return std::equal_range(m_data.begin(), m_data.end(), key, m_value_comp);
		}

		iterator lower_bound(const key_type& key)
		{
			return std::lower_bound(m_data.begin(), m_data.end(), key, m_value_comp);
		}

		const_iterator lower_bound(const key_type& key) const
		{
			return std::lower_bound(m_data.begin(), m_data.end(), key, m_value_comp);
		}

		template<typename K, typename = Compare::is_tranparent>
		iterator lower_bound(const K& key)
		{
			return lower_bound(static_cast<typename Compare::is_transparent>(key));
		}

		template<typename K, typename = Compare::is_tranparent>
		iterator lower_bound(const K& key) const
		{
			return lower_bound(static_cast<typename Compare::is_transparent>(key));
		}

		iterator upper_bound(const key_type& key)
		{
			return std::upper_bound(m_data.begin(), m_data.end(), key, m_value_comp);
		}

		const_iterator upper_bound(const key_type& key) const
		{
			return std::upper_bound(m_data.begin(), m_data.end(), key, m_value_comp);
		}

		template<typename K, typename = Compare::is_tranparent>
		iterator upper_bound(const K& key)
		{
			return upper_bound(static_cast<typename Compare::is_transparent>(key));
		}

		template<typename K, typename = Compare::is_tranparent>
		iterator upper_bound(const K& key) const
		{
			return upper_bound(static_cast<typename Compare::is_transparent>(key));
		}

		key_compare key_comp() const
		{
			return m_value_comp;
		}

		value_compare value_comp() const
		{
			return m_value_comp;
		}

		void reserve(size_t size)
		{
			m_data.reserve(size);
		}

		void shrink_to_fit()
		{
			m_data.shrink_to_fit();
		}

		size_type capacity()
		{
			return m_data.capacity();
		}
	};
}