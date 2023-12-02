#include "scheduler_test.hpp"

#include "extras/y_combinator.hpp"

#include <algorithm>
#include <deque>
#include <limits>
#include <random>
#include <utility>
#include <vector>

using namespace Primitives;

////////////////////////////////////////////////////////////////////////////////
	
TEST_F(Parallel, Scheduler_WaitingSimple)
{
	int value1 = 12345;
	int result1 = 76193340; //1+2+...+12345-1

	int value2 = 54321;
	int result2 = 1475358360; //1+2+...+54321-1

	auto func_loop = [](int value)
	{
		int output = 0;

		for (auto loop : Range(value))
		{
			output += (int)loop;
		}

		return output;
	};

	auto func_final = [](int value1, int value2)
	{
		return value1 + value2;
	};

	auto task_loop1 = scheduler_->AddImmediateTask(func_loop, value1);
	auto task_loop2 = scheduler_->AddImmediateTask(func_loop, value2);
	auto task_final = scheduler_->AddImmediateTask(func_final, std::move(task_loop1), std::move(task_loop2));

	while (!task_final.IsReady());
	auto result_final = task_final.Get();

	ASSERT_EQ(result_final, result1 + result2);

	return;
}
	
////////////////////////////////////////////////////////////////////////////////

TEST_F(Parallel, Scheduler_WaitingSimpleMany)
{
	std::size_t count = 1024;

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<> distribution(std::numeric_limits<int>::max() - 20, std::numeric_limits<int>::max() - 10);

	std::vector<int> value1(count);
	std::vector<int> value2(count);

	std::generate(value1.begin(), value1.end(), [&]() { return distribution(generator); });
	std::generate(value2.begin(), value2.end(), [&]() { return distribution(generator); });

	std::deque<Future<int>> result_value1;
	std::deque<Future<int>> result_value2;
	std::deque<Future<int>> result_final;

	for (auto loop : Range(count))
	{
		auto func_inc = [](int value) 
		{
			return value + 1;
		};

		auto func_dec = [](int value) 
		{
			return value - 1;
		};

		auto func_final = [](int value1, int value2) 
		{
			return value1 + value2;
		};

		result_value1.push_back(scheduler_->AddImmediateTask(func_inc, value1[loop]));
		result_value2.push_back(scheduler_->AddImmediateTask(func_dec, value2[loop]));
	
		result_final.push_back(scheduler_->AddImmediateTask(func_final, result_value1.back(), result_value2.back()));
	}

	for(;;)
	{
		std::size_t index = 0;
		std::size_t ready = 0;

		for (auto result : result_final)
		{
			if (result.IsReady())
			{
				ASSERT_EQ(result_value1[index].Get(), value1[index] + 1);
				ASSERT_EQ(result_value2[index].Get(), value2[index] - 1);
				ASSERT_EQ(result.Get(), value1[index] + value2[index]);
				++ready;
			}

			++index;
		}

		if (ready == count)
		{
			break;
		}
	}
}

////////////////////////////////////////////////////////////////////////////////

//	TEST_F(Parallel, Scheduler_WaitingYCombinator)
//	{
//		int value = 16;
//	
//		auto fibonnaci = Y_Combinator
//		(
//			[](auto fibonnaci, int value) ->int
//			{
//				return value < 1 ? -1 : (value == 1 || value == 2 ? 1 : fibonnaci(value - 1) + fibonnaci(value - 2));
//			}
//		);
//	
//		auto task = scheduler_->AddImmediateTask(fibonnaci, value);
//	
//		while (!task.IsReady());
//	
//		ASSERT_EQ(task.Get(), 987);
//	}

////////////////////////////////////////////////////////////////////////////////

//	TEST_F(Parallel, Scheduler_WaitingYCombinatorMany)
//	{
//		std::size_t count = 1024;
//	
//		int value = 16;
//	
//		auto fibonnaci = Y_Combinator
//		(
//			[](auto fibonnaci, int value) ->int
//			{
//				return value < 1 ? -1 : (value == 1 || value == 2 ? 1 : fibonnaci(value - 1) + fibonnaci(value - 2));
//			}
//		);
//	
//		std::vector<Future<int>> results_;
//	
//		for (auto loop : Range(count))
//		{
//			loop;
//			results_.push_back(scheduler_->AddImmediateTask(fibonnaci, value));
//		}
//	
//		for (;;)
//		{
//			std::size_t index = 0;
//			std::size_t ready = 0;
//	
//			for (auto result : results_)
//			{
//				if (result.IsReady())
//				{
//					ASSERT_EQ(result.Get(), 987);
//					++ready;
//				}
//	
//				++index;
//			}
//	
//			if (ready == count)
//			{
//				break;
//			}
//		}
//	}

////////////////////////////////////////////////////////////////////////////////