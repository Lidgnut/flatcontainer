#pragma once

#include <vector>
#include <array>
#include "include/flatcontainer/Primes.h"
namespace mwaack
{
	template <typename T>
	struct hash_table_iter
	{
		using difference_type = typename std::ptrdiff_t;
		using value_type = typename T::value_type;
		using pointer = value_type * ;
		using reference = value_type & ;
		using iterator_category = std::forward_iterator_tag;

		template<typename T>
		friend bool operator ==(const hash_table_iter<T>& lhs, const hash_table_iter<T>& rhs);
		template<typename T>
		friend bool operator !=(const hash_table_iter<T>& lhs, const hash_table_iter<T>& rhs);

		hash_table_iter operator ++()
		{
			//if (m_currBucket >= m_data->bucket_count())
			//{
			//	m_currBucket = m_data->bucket_count();
			//	m_currBucketPos = 0;
			//	return *this;
			//}
			//size_t newBucketPos = m_currBucketPos + 1;
			//for (; newBucketPos < (*m_data)[m_currBucket].second.size(); ++newBucketPos)
			//{
			//	if((*m_data)[m_currBucket].first & 1u << newBucketPos)
			//		break;
			//}
			//if (newBucketPos >= (*m_data)[m_currBucket].second.size())
			//{
			//	m_currBucket += 1;
			//	m_currBucketPos = 0;
			//}
			//else
			//{
			//	m_currBucketPos = newBucketPos;
			//}
			return *this;
		}

		hash_table_iter operator ++(int)
		{
			hash_table_iter tmp = *this;
			this->operator++();
			return tmp;
		}

		hash_table_iter() = default;
		hash_table_iter(T* data, typename T::size_type currBucket, typename T::size_type currBucketPos)
			: m_data(data)
			, m_currBucket(currBucket)
			, m_currBucketPos(currBucketPos)
		{
		}
		hash_table_iter(const hash_table_iter&) = default;
		hash_table_iter& operator=(const hash_table_iter&) = default;
		~hash_table_iter() = default;

		const value_type& operator*() const
		{
			//return (*m_data)[m_currBucket].second[m_currBucketPos];
		}

		const value_type* operator->() const
		{
			//return &(*m_data)[m_currBucket].second[m_currBucketPos];
		}
	private:
		T* m_data;
		typename T::size_type m_currBucket;
		typename T::size_type m_currBucketPos;
	};

	template<typename T>
	struct BucketIter
	{
	private:
		using bucket_type = typename T::bucket_type;
		using buffered_type = typename bucket_type::buffered_type;
		using unbuffered_type = typename bucket_type::unbuffered_type;
	public:

		using difference_type = typename std::ptrdiff_t;
		using value_type = typename T::value_type;
		using pointer = value_type * ;
		using reference = value_type & ;
		using iterator_category = std::forward_iterator_tag;

		template<typename T>
		friend bool operator ==(const BucketIter<T>& lhs, const BucketIter<T>& rhs);
		template<typename T>
		friend bool operator !=(const BucketIter<T>& lhs, const BucketIter<T>& rhs);

		BucketIter operator ++()
		{
			++m_currIter;
			return *this;
		}

		BucketIter operator ++(int)
		{
			BucketIter tmp = *this;
			this->operator++();
			return tmp;
		}

		BucketIter() = default;
		explicit BucketIter(typename bucket_type::iterator currIter)
			: m_currIter(m_currIter)
		{ }
		BucketIter(const BucketIter&) = default;
		BucketIter& operator=(const BucketIter&) = default;
		~BucketIter() = default;

		const reference operator*() const
		{
			return *m_currIter;
		}

		const pointer operator->() const
		{
			return &*m_currIter;
		}

	private:
		typename bucket_type::iterator m_currIter;
	};

	template<typename T>
	bool operator ==(const hash_table_iter<T>& lhs, const hash_table_iter<T>& rhs)
	{
		return lhs.m_data == rhs.m_data
			&& lhs.m_currBucket == rhs.m_currBucket
			&& lhs.m_currBucketPos == rhs.m_currBucketPos;
	}
	template<typename T>
	bool operator !=(const hash_table_iter<T>& lhs, const hash_table_iter<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename T>
	bool operator==(const BucketIter<T>& lhs, const BucketIter<T>& rhs)
	{
		return lhs.m_currIter == rhs.m_currIter;
	}

	template<typename T>
	bool operator!=(const BucketIter<T>& lhs, const BucketIter<T>& rhs)
	{
		return !(lhs == rhs);
	}

	template<typename Value, typename Hash = std::hash<Value>, typename KeyEqual = std::equal_to<Value>, typename Allocator = std::allocator<Value>>
	class flat_hash_table
	{
		class Bucket
		{
		public:
			using iterator = typename BucketIter<Bucket>;
			using const_iterator = typename BucketIter<Bucket>;
			using buffered_type = std::array<Value, 16>;
			using unbuffered_type = std::vector<Value, Allocator>;
		private:
			uint16_t m_bitmask;
			buffered_type m_bufferedData;
			unbuffered_type m_unbufferedData;

		public:
			iterator begin()
			{
				return m_data.begin();
			}
			iterator end()
			{
				return m_data.end();
			}
			const_iterator begin() const
			{
				return m_data.begin();
			}
			const_iterator end() const
			{
				m_data.end();
			}
			const_iterator cbegin()
			{
				m_data.cbegin();
			}
			const_iterator cend()
			{
				m_data.cend();
			}

			iterator insert(const Value& val)
			{
				for (size_t i = 0; i < std::numeric_limits<uint16_t>::digits; ++i)
				{
					if ((m_bitmask.first & 1u << i) == 0)
					{
						m_bufferedData[i] = val;
						m_bitmask ^= 1u << i;
						return m_bufferedData.begin() + i;
					}
				}
				return m_unbufferedData.emplace_back(val);
			}
			iterator erase(const Value& val)
			{

			}
		};
		using data_type = std::vector<Bucket>;
	public:
		using bucket_type = Bucket;
		using key_type = typename Value;
		using value_type = typename Value;
		using size_type = typename data_type::size_type;
		using difference_type = typename data_type::difference_type;
		using hasher = Hash;
		using key_equal = KeyEqual;
		using allocator_type = typename data_type::allocator_type;
		using reference = typename data_type::reference;
		using const_reference = typename data_type::const_reference;
		using pointer = typename data_type::pointer;
		using const_pointer = typename data_type::const_pointer;
		using iterator = typename hash_table_iter<flat_hash_table>;
		using const_iterator = typename data_type::const_iterator;

	private:
		data_type m_data;
		hasher m_hash;
		key_equal m_equal;
		float m_maxLoadFactor = 6;

		void init()
		{
			m_data.resize(1);
		}

	public:
		flat_hash_table() = default;

		iterator begin()
		{
			return iterator(this, 0, 0);
		}

		iterator end()
		{
			return end_iterator();
		}


		bool insertToBucket(const value_type& val, size_type bucket)
		{
			for (size_t i = 0; i < m_data[bucket].second.size(); ++i)
			{
				if ((m_data[bucket].first & 1u << i) == 0)
				{
					m_data[bucket].second[i] = val;
					m_data[bucket].first ^= 1u << i;
					return true;
				}
			}
			return false;
		}

		void insert(const value_type& val)
		{
			if (m_data.size() == 0)
				init();
			if (size_t hash = m_hash(val) % m_data.size(); insertToBucket(val, hash))
			{
				if(size() > max_load_factor() * bucket_count())
					rehash(0 /*mwaack::Primes::getPrime(m_data.size() + 1)*/);
			}
			else
			{
				rehash(mwaack::Primes::nextPrime(m_data.size() + 1));
				insert(val);
			}
		}

		void rehash(size_t bucketSize)
		{
			if (bucketSize < size() / max_load_factor())
			{
				bucketSize = std::ceil(size() / max_load_factor()); //mwaack::Primes::getPrime(m_data.size() + 1);
			}
			std::cout << "Resize to: " << std::setw(4) << bucketSize << '\n';
			//size_type oldBucketCount = m_data.size();
			//m_data.resize(bucketSize);

			std::vector<bucket_type> tmp_vals;
			tmp_vals.reserve(m_data.size());
			std::move(m_data.begin(), m_data.end(), std::back_inserter(tmp_vals));
			m_data.clear();
			m_data.resize(bucketSize);
			for (auto& arr : tmp_vals)
			{
				for (size_type i = 0; i < arr.second.size(); ++i)
				{
					if ((arr.first & 1u << i) != 0)
					{
						insert(arr.second[i]);
					}
				}
			}
		}
		const bucket_type& operator[](size_t n) const
		{
			return m_data[n];
		}

		size_type bucket_count() const
		{
			return m_data.size();
		}

		size_type size()
		{
			return std::distance(this->begin(), this->end());
		}

		float load_factor() const
		{
			return size() / static_cast<float>(bucket_count());
		}

		float max_load_factor() const
		{
			return m_maxLoadFactor;
		}

		void max_load_factor(float newMaxLoadFactor)
		{
			m_maxLoadFactor = newMaxLoadFactor;
		}

		iterator find(const value_type& val)
		{
			if (m_data.size() == 0)
				return end_iterator();
			else
			{
				size_t hash = m_hash(val);
				hash = hash % m_data.size();
				size_t i = 0;
				for (; i < m_data[hash].second.size(); ++i)
				{
					if ((m_data[hash].first & 1u << i) != 0 && m_equal(m_data[hash].second[i], val))
					{
						return iterator(this, hash, i);
					}
				}
				if (i >= m_data[hash].second.size())
					return end_iterator();
			}
		}

	private:
		iterator end_iterator()
		{
			return iterator(this, m_data.size(), 0);
		}
	};
}