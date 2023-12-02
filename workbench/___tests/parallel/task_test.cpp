#include "task_test.hpp"

using namespace Primitives;

//	////////////////////////////////////////////////////////////////////////////////
//	
//	TEST_F(Parallel, Task_LamdaSimple)
//	{
//		output1_ = 0x12345678;
//		output2_ = 0x12345678;
//		output3_ = 0x12345678;
//		output4_ = 0x12345678;
//	
//		int test = 0x12345678;
//		auto group = &test;
//	
//		auto incrementA = ([group](std::uint32_t& value) { ++value; return value; });
//		auto decrementA = ([group](std::uint32_t& value) { --value; return value; });
//	
//		auto incrementB = ([](std::uint32_t& value) { ++value; return value; });
//		auto decrementB = ([](std::uint32_t& value) { --value; return value; });
//	
//		auto incrementC = ([](std::uint32_t& value) { ++value; });
//		auto decrementC = ([](std::uint32_t& value) { --value; });
//	
//		auto task1A = Task::CreateTask(incrementA, output1_);
//		auto task2A = Task::CreateTask(decrementA, output2_);
//	
//		auto task1B = Task::CreateTask(incrementB, output1_);
//		auto task2B = Task::CreateTask(decrementB, output2_);
//	
//		auto task1C = Task::CreateTask(incrementC, output1_);
//		auto task2C = Task::CreateTask(decrementC, output2_);
//	
//		task1A.first.Invoke();
//		task2A.first.Invoke();
//		ASSERT_EQ(output1_, 0x12345678 + 1);
//		ASSERT_EQ(output2_, 0x12345678 - 1);
//		
//		task1B.first.Invoke();
//		task2B.first.Invoke();
//		ASSERT_EQ(output1_, 0x12345678 + 2);
//		ASSERT_EQ(output2_, 0x12345678 - 2);
//	
//		task1C.first.Invoke();
//		task2C.first.Invoke();
//		ASSERT_EQ(output1_, 0x12345678 + 3);
//		ASSERT_EQ(output2_, 0x12345678 - 3);
//	
//		auto future1A = task1A.second;
//		auto future2A = task2A.second;
//		ASSERT_EQ(future1A.Get(), 0x12345678 + 1);
//		ASSERT_EQ(future2A.Get(), 0x12345678 - 1);
//	
//		auto future1B = task1B.second;
//		auto future2B = task2B.second;
//		ASSERT_EQ(future1B.Get(), 0x12345678 + 2);
//		ASSERT_EQ(future2B.Get(), 0x12345678 - 2);
//	}
//	
//	////////////////////////////////////////////////////////////////////////////////
//	
//	TEST_F(Parallel, Task_FunctionSimple)
//	{
//		output1_ = 0x12345678;
//		output2_ = 0x12345678;
//		output3_ = 0x12345678;
//		output4_ = 0x12345678;
//	
//		const auto repeat = 16;
//	
//		auto task1 = Task::CreateTask(testfunc1);
//		auto task2 = Task::CreateTask(testfunc2);
//		auto task3 = Task::CreateTask(testfunc3);
//		auto task4 = Task::CreateTask(testfunc4);
//	
//	//	for (auto loop : Range(repeat))
//		{
//	//		loop;
//	
//			task1.first.Invoke();
//	//		task1.first.Reset();
//	
//			task2.first.Invoke();
//	//		task2.first.Reset();
//	
//			task3.first.Invoke();
//	//		task3.first.Reset();
//	
//			task4.first.Invoke();
//	//		task4.first.Reset();
//		}
//	
//	//	ASSERT_EQ(output1_, 0xffffffff);
//	//	ASSERT_EQ(output2_, 0x12345678 + repeat);
//	//	ASSERT_EQ(output3_, 0x12345678 - repeat);
//	//	ASSERT_EQ(output4_, 0xffffffff);
//	}
//	
//	////////////////////////////////////////////////////////////////////////////////
//	
//	TEST_F(Parallel, Task_FunctionArgumentsSimple)
//	{
//		output1_ = 0x12345678;
//		output2_ = 0x12345678;
//		output3_ = 0x12345678;
//		output4_ = 0x12345678;
//	
//		void* fiber = nullptr;
//		std::uint32_t arg1 = 1;
//		std::uint32_t arg2 = 2;
//		std::uint32_t arg3 = 3;
//		std::uint32_t arg4 = 4;
//	
//		auto task1 = Task::CreateTask(testfuncarg1, fiber, arg1);
//		auto task2 = Task::CreateTask(testfuncarg2, fiber, arg1, arg2);
//		auto task3 = Task::CreateTask(testfuncarg3, fiber, arg1, arg2, arg3);
//		auto task4 = Task::CreateTask(testfuncarg4, fiber, arg1, arg2, arg3, arg4);
//	
//		task1.first.Invoke();
//		task2.first.Invoke();
//		task3.first.Invoke();
//		task4.first.Invoke();
//	
//		ASSERT_EQ(output1_, 0xffffffff + arg1);
//		ASSERT_EQ(output2_, 0x12345678 + arg1 + arg2);
//		ASSERT_EQ(output3_, 0x12345678 + arg1 + arg2 + arg3);
//		ASSERT_EQ(output4_, 0xffffffff + arg1 + arg2 + arg3 + arg4);
//	}
//	
//	////////////////////////////////////////////////////////////////////////////////
//	
//	TEST_F(Parallel, Task_FunctionArguments)
//	{
//		{
//			int output = 0x12345678;
//			int input = 0x87654321;
//			void* fiber = &input;
//	
//			auto task = Task::CreateTask(testfuncspec1, fiber, output, input);
//			task.first.Invoke();
//	
//			ASSERT_EQ(output, 0x87654321);
//			ASSERT_EQ(input, 0x12345678);
//		}
//	
//		{
//			int output = 0x12345678;
//			int input = 0x87654321;
//	
//			auto task = Task::CreateTask(testfuncspec2, output, input);
//			task.first.Invoke();
//	
//			auto future = task.second;
//	
//			ASSERT_EQ(output, 0x87654321);
//			ASSERT_EQ(input, 0x87654321);
//			ASSERT_EQ(future.Get(), 0x12345678 + 0x87654321);
//		}
//	
//		{
//			int output1 = 0x12345678;
//			int output2 = 0x87654321;
//	
//			auto task = Task::CreateTask(testfuncspec3, output1, output2);
//			task.first.Invoke();
//	
//			auto future = task.second;
//	
//			ASSERT_EQ(output1, 0x87654321);
//			ASSERT_EQ(output2, 0x12345678);
//			ASSERT_EQ(future.Get(), 0x12345678 + 0x87654321);
//		}
//	}
//	
//	////////////////////////////////////////////////////////////////////////////////

