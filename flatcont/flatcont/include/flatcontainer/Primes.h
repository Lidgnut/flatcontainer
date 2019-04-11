#pragma once
#include <vector>
#include <algorithm>

namespace mwaack
{
	class Primes
	{
		inline static std::vector<size_t> m_buffPrimes = std::vector<size_t>();
	public:
		static bool isPrimeLoop(int i, int k) 
		{
			if (k*k > i)
			{
				m_buffPrimes.emplace_back(i);
				return true;
			}
			else if (i%k == 0)
			{
				return false;
			}
			else
			{
				return isPrimeLoop(i, k + 1);
			}
		}

		static bool isPrime(size_t i) 
		{
			if (auto it = std::lower_bound(m_buffPrimes.begin(), m_buffPrimes.end(), i); it != m_buffPrimes.end())
			{
				if (*it == i)
				{
					return true;
				}
				else
				{
					return isPrimeLoop(i, *it);
				}
			}
			else
			{
				return isPrimeLoop(i, 2);
			}
		}

		static size_t nextPrime(size_t k) 
		{
			if (isPrime(k))
			{
				return k;
			}
			else
			{
				return nextPrime(k + 1);
			}
		}

		static size_t getPrimeLoop(size_t i, size_t k) 
		{
			if (i == 0)
			{
				return k;
			}
			else if (i % 2)
			{
				return getPrimeLoop(i - 1, nextPrime(k + 1));
			}
			else
			{
				return getPrimeLoop(i / 2, getPrimeLoop(i / 2, k));
			}
		}

		static size_t getPrime(size_t i)
		{
			if (m_buffPrimes.size() > i)
			{
				return m_buffPrimes[i];
			}
			else if (m_buffPrimes.size() == 0)
			{
				return getPrimeLoop(i, 2);
			}
			else
			{
				return getPrimeLoop(i, m_buffPrimes.back());
			}
		}
	};


	

	

	
}