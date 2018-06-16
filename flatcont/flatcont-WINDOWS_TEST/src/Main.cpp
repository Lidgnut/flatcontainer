
#include "boost/container/flat_set.hpp"
#include "benchmark/benchmark.h"
#include "include/flat_set.h"
#include <set>
#include <iostream>

static void FlatSetFind(benchmark::State& state)
{
	mwaack::flat_set<int> set;

	for (int i = 0; i < 10'000; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % 10'000;
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

	for (int i = 0; i < 10'000; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % 10'000;
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

static void BoostFlatSetFind(benchmark::State& state)
{
	boost::container::flat_set<int> set;

	for (int i = 0; i < 10'000; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % 10'000;
		auto it = set.find(val);
		if (it != set.end())
		{
			int p = *it;
			benchmark::DoNotOptimize(p);
		}
	}
}
// Register the function as a benchmark
BENCHMARK(BoostFlatSetFind);

static void FlatSetEmplace(benchmark::State& state)
{
	mwaack::flat_set<int> set;

	//for (int i = 0; i < 10'000; ++i)
	//{
	//	set.emplace(i);
	//}
	for (auto _ : state)
	{
		int val = rand() % 10'000;
		set.emplace(val);
		//auto it = set.find(val);
		//if (it != set.end())
		//{
		//	int p = *it;
		//	benchmark::DoNotOptimize(p);
		//}
	}
}
// Register the function as a benchmark
BENCHMARK(FlatSetEmplace);

static void SetEmplace(benchmark::State& state)
{
	std::set<int> set;

	//for (int i = 0; i < 10'000; ++i)
	//{
	//	set.emplace(i);
	//}
	for (auto _ : state)
	{
		int val = rand() % 10'000;
		set.emplace(val);
		//auto it = set.find(val);
		//if (it != set.end())
		//{
		//	int p = *it;
		//	benchmark::DoNotOptimize(p);
		//}
	}
}
// Register the function as a benchmark
BENCHMARK(SetEmplace);

static void BoostFlatSetEmplace(benchmark::State& state)
{
	boost::container::flat_set<int> set;

	//for (int i = 0; i < 10'000; ++i)
	//{
	//	set.emplace(i);
	//}
	for (auto _ : state)
	{
		int val = rand() % 10'000;
		set.emplace(val);
		//auto it = set.find(val);
		//if (it != set.end())
		//{
		//	int p = *it;
		//	benchmark::DoNotOptimize(p);
		//}
	}
}
// Register the function as a benchmark
BENCHMARK(BoostFlatSetEmplace);

static void FlatSetIterate(benchmark::State& state)
{
	mwaack::flat_set<int> set;

	for (int i = 0; i < 10'000; ++i)
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

	for (int i = 0; i < 10'000; ++i)
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

static void BoostFlatSetIterate(benchmark::State& state)
{
	boost::container::flat_set<int> set;

	for (int i = 0; i < 10'000; ++i)
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
BENCHMARK(BoostFlatSetIterate);



static void FlatSetErase(benchmark::State& state)
{
	mwaack::flat_set<int> set;

	for (int i = 0; i < 10'000; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % 10'000;
		set.erase(val);
	}
}
// Register the function as a benchmark
BENCHMARK(FlatSetErase);

static void SetErase(benchmark::State& state)
{
	std::set<int> set;

	for (int i = 0; i < 10'000; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % 10'000;
		set.erase(val);
	}
}
// Register the function as a benchmark
BENCHMARK(SetErase);

static void BoostFlatSetErase(benchmark::State& state)
{
	boost::container::flat_set<int> set;

	for (int i = 0; i < 10'000; ++i)
	{
		set.emplace(i);
	}
	for (auto _ : state)
	{
		int val = rand() % 10'000;
		set.erase(val);
	}
}
// Register the function as a benchmark
BENCHMARK(BoostFlatSetErase);

int main(int argc, char** argv)
{
	::benchmark::Initialize(&argc, argv);
	if (::benchmark::ReportUnrecognizedArguments(argc, argv))
		return 1;
	::benchmark::RunSpecifiedBenchmarks();
	std::cin.get();
}