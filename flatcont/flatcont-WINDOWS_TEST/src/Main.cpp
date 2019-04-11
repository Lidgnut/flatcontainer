
//#include "boost/container/flat_set.hpp"
#include "benchmark/benchmark.h"
#include "include/flatcontainer/flat_set.h"
#include <include/flatcontainer/flat_map.h>
#include "include/flatcontainer/Primes.h"
#include <set>
#include <iostream>

static constexpr int iter = 500'000;

static void FlatSetFind(benchmark::State& state)
{
	mwaack::flat_set<int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % iter;
		auto it = set.find(val);
		if (it != set.end())
		{
			int p = *it;
			benchmark::DoNotOptimize(p);
		}
	}
}
// Register the function as a benchmark
BENCHMARK(FlatSetFind);

static void SetFind(benchmark::State& state)
{
	std::set<int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % iter;
		auto it = set.find(val);
		if (it != set.end())
		{
			int p = *it;
			benchmark::DoNotOptimize(p);
		}
	}
}
// Register the function as a benchmark
BENCHMARK(SetFind);

static void FlatSetEmplace(benchmark::State& state)
{
	mwaack::flat_set<int> set;

	for (auto _ : state)
	{
		int val = rand() % iter;
		set.emplace(val);
	}
}
// Register the function as a benchmark
BENCHMARK(FlatSetEmplace);

static void SetEmplace(benchmark::State& state)
{
	std::set<int> set;

	for (auto _ : state)
	{
		int val = rand() % iter;
		set.emplace(val);
	}
}
// Register the function as a benchmark
BENCHMARK(SetEmplace);

static void FlatSetIterate(benchmark::State& state)
{
	mwaack::flat_set<int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int sum = 0;
		for (const auto& entry : set)
		{
			sum += entry;
		}
		benchmark::DoNotOptimize(sum);
	}
}
// Register the function as a benchmark
BENCHMARK(FlatSetIterate);

static void SetIterate(benchmark::State& state)
{
	std::set<int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int sum = 0;
		for (const auto& entry : set)
		{
			sum += entry;
		}
		benchmark::DoNotOptimize(sum);
	}
}
// Register the function as a benchmark
BENCHMARK(SetIterate);


static void FlatSetErase(benchmark::State& state)
{
	mwaack::flat_set<int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % iter;
		set.erase(val);
	}
}
// Register the function as a benchmark
BENCHMARK(FlatSetErase);

static void SetErase(benchmark::State& state)
{
	std::set<int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % iter;
		set.erase(val);
	}
}
// Register the function as a benchmark
BENCHMARK(SetErase);




static void FlatMapFind(benchmark::State& state)
{
	mwaack::flat_map<int, int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i, i);
	}
	for (auto _ : state)
	{
		int val = rand() % iter;
		auto it = set.find(val);
		if (it != set.end())
		{
			int p = it->first + it->second;
			benchmark::DoNotOptimize(p);
		}
	}
}
// Register the function as a benchmark
BENCHMARK(FlatMapFind);

static void MapFind(benchmark::State& state)
{
	std::map<int, int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i, i);
	}
	for (auto _ : state)
	{
		int val = rand() % iter;
		auto it = set.find(val);
		if (it != set.end())
		{
			int p = it->first + it->second;
			benchmark::DoNotOptimize(p);
		}
	}
}
// Register the function as a benchmark
BENCHMARK(MapFind);

static void FlatMapEmplace(benchmark::State& state)
{
	mwaack::flat_map<int, int> set;

	for (auto _ : state)
	{
		int val = rand() % iter;
		set.emplace(val, val);
	}
}
// Register the function as a benchmark
BENCHMARK(FlatMapEmplace);

static void MapEmplace(benchmark::State& state)
{
	std::map<int, int> set;

	for (auto _ : state)
	{
		int val = rand() % iter;
		set.emplace(val, val);
	}
}
// Register the function as a benchmark
BENCHMARK(MapEmplace);

static void FlatMapIterate(benchmark::State& state)
{
	mwaack::flat_map<int, int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i, i);
	}
	for (auto _ : state)
	{
		int sum = 0;
		for (const auto& entry : set)
		{
			sum += entry.first + entry.second;
		}
		benchmark::DoNotOptimize(sum);
	}
}
// Register the function as a benchmark
BENCHMARK(FlatMapIterate);

static void MapIterate(benchmark::State& state)
{
	std::map<int, int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i, i);
	}
	for (auto _ : state)
	{
		int sum = 0;
		for (const auto& entry : set)
		{
			sum += entry.first + entry.second;
		}
		benchmark::DoNotOptimize(sum);
	}
}
// Register the function as a benchmark
BENCHMARK(MapIterate);


static void FlatMapErase(benchmark::State& state)
{
	mwaack::flat_map<int, int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i, i);
	}
	for (auto _ : state)
	{
		int val = rand() % iter;
		set.erase(val);
	}
}
// Register the function as a benchmark
BENCHMARK(FlatMapErase);

static void MapErase(benchmark::State& state)
{
	std::map<int, int> set;

	for (int i = 0; i < iter; ++i)
	{
		set.emplace(i, i);
	}
	for (auto _ : state)
	{
		int val = rand() % iter;
		set.erase(val);
	}
}
// Register the function as a benchmark
BENCHMARK(MapErase);

static void Primes(benchmark::State& state)
{
	size_t n = state.range(0);
	for (auto _ : state)
	{
		auto p = mwaack::Primes::getPrime(n);
		benchmark::DoNotOptimize(p);
	}
}
// Register the function as a benchmark
BENCHMARK(Primes)->RangeMultiplier(2)->Range(1, 8<<16);


int main(int argc, char** argv)
{
	::benchmark::Initialize(&argc, argv);
	if (::benchmark::ReportUnrecognizedArguments(argc, argv))
		return 1;
	::benchmark::RunSpecifiedBenchmarks();
	std::cin.get();
}