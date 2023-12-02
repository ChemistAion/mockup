#include "parallel.hpp"

#include "wait.hpp"

using namespace Primitives;

////////////////////////////////////////////////////////////////////////////////

BENCHMARK_DEFINE_F(Parallel, SimpleTask_Benchmark)(benchmark::State& state)
{
	std::vector<int> values(count);
	std::generate(values.begin(), values.end(), [&]() { return distribution(generator); });

	while (state.KeepRunning())
	{
		std::deque<Future<int>> result;

		for (auto index : Mockup::Range(count))
		{
			auto func_inc = [](int value)
			{
				return value + 1;
			};

			auto func_dec = [](int value)
			{
				return value - 1;
			};

			auto func_none = [](int value)
			{
				return value;
			};

			auto func_final = [](int value1, int value2, int value3)
			{
				return value1 + value2 + value3;
			};

			auto task1 = scheduler_->AddImmediateTask(func_inc, values[index]);
			auto task2 = scheduler_->AddImmediateTask(func_dec, values[index]);
			auto task3 = scheduler_->AddImmediateTask(func_dec, values[index]);

			result.push_back(scheduler_->AddImmediateTask(func_final, std::move(task1), std::move(task2), std::move(task3)));
		}

		auto done = result.begin();

		for (;;)
		{
			done = std::partition
			(
				done, result.end(),
				[](auto& result) { return result.IsReady(); }
			);

			if (done == result.end())
			{
				break;
			}	
		}
	}
}

BENCHMARK_REGISTER_F(Parallel, SimpleTask_Benchmark)->Repetitions(4)->Unit(benchmark::kMicrosecond)->ReportAggregatesOnly(false)->DisplayAggregatesOnly(false);
//->Threads(4)

////////////////////////////////////////////////////////////////////////////////

//	BENCHMARK_DEFINE_F(Parallel, ModerateTask_Benchmark)(benchmark::State& state)
//	{
//		while (state.KeepRunning())
//		{
//		}
//	}
//	
//	BENCHMARK_REGISTER_F(Parallel, ModerateTask_Benchmark)->Repetitions(4)->Unit(benchmark::kMicrosecond)->ReportAggregatesOnly(false)->DisplayAggregatesOnly(false);

////////////////////////////////////////////////////////////////////////////////