#include "storage_test.hpp"

using namespace Primitives;

////////////////////////////////////////////////////////////////////////////////

TEST_F(Assets, Storage_Registering)
{
	Manager manager;

	int value = 42;

	auto result1a = manager.RegisterStorage<SimpleStorage>("test1", "xyz", value);
	auto result2a = manager.RegisterStorage<SimpleStorage>("test2", "xyz", value);
	auto result3a = manager.RegisterStorage<DummyStorage>("test3", "xyz");

	auto result1b = manager.RegisterStorage<SimpleStorage>("test1", "xyz", value);
	auto result2b = manager.RegisterStorage<SimpleStorage>("test2", "xyz", value);
	auto result3b = manager.RegisterStorage<DummyStorage>("test3", "xyz");

	auto result4 = manager.RegisterStorage<int>("wrong", "xyz");

	ASSERT_EQ(result1a, true);
	ASSERT_EQ(result2a, true);
	ASSERT_EQ(result3a, true);

	ASSERT_EQ(result1b, false);
	ASSERT_EQ(result2b, false);
	ASSERT_EQ(result3b, false);

	ASSERT_EQ(result4, false);

	return;
}

////////////////////////////////////////////////////////////////////////////////

//	TEST_F(Assets, Storage_DummyLoads)
//	{
//		Manager manager;
//	
//		ASSERT_EQ(manager.RegisterStorage<DummyStorage>(), true);
//	
//	//	DummyStorage::Instance instance;
//	
//	//	ASSERT_EQ(instance.operator bool(), false);
//	
//		auto future1 = manager.LoadFromFile<DummyStorage>("test1");
//	//	auto future2 = manager.LoadFromInstance<DummyLoadStorage>("test2", instance);
//	//	auto future3 = manager.LoadFromMemory<DummyLoadStorage>("test3", nullptr, 0);
//	
//		auto ready1 = future1.IsReady();
//	//	auto ready2 = future2.IsReady();
//	//	auto ready3 = future3.IsReady();
//	
//		ASSERT_EQ(ready1, true);
//	//	ASSERT_EQ(ready2, true);
//	//	ASSERT_EQ(ready3, true);
//	
//		auto value1 = future1.Get();
//	//	auto value2 = future1.Get();
//	//	auto value3 = future1.Get();
//	
//		ASSERT_EQ(value1.GetAsset().operator bool(), true);
//	//	ASSERT_EQ(value2.GetAsset().operator bool(), true);
//	//	ASSERT_EQ(value3.GetAsset().operator bool(), true);
//	
//		auto find1a = manager.FindEntry<DummyStorage>("test");
//		auto find1b = manager.FindEntry<DummyStorage>("test1");
//		auto find1c = manager.FindEntry<DummyStorage>("test11");
//	
//	//	auto find2 = manager.FindEntry<DummyLoadStorage>("test2");
//	//	auto find3 = manager.FindEntry<DummyLoadStorage>("test3");
//	
//		ASSERT_EQ(find1a.IsReady(), false);
//		ASSERT_EQ(find1b.IsReady(), true);
//		ASSERT_EQ(find1c.IsReady(), false);
//	
//	//	ASSERT_EQ(find2.IsReady(), true);
//	//	ASSERT_EQ(find3.IsReady(), true);
//	}

////////////////////////////////////////////////////////////////////////////////

//	TEST_F(Assets, Storage_CheckFutures) //add more loaders and check results
//	{
//		Manager manager;
//	
//		ASSERT_EQ(manager.RegisterStorage<DummyStorage>(), true);
//	
//		auto future1a = manager.LoadFromFile<DummyStorage>("test1");
//		auto future1b = manager.LoadFromFile<DummyStorage>("test1");
//		auto future1c = manager.LoadFromFile<DummyStorage>("test1");
//		auto future2 = manager.LoadFromFile<DummyStorage>("test2");
//		auto future3 = manager.LoadFromFile<DummyStorage>("test3");
//	
//		auto ready1a = future1a.IsReady();
//		auto ready1b = future1b.IsReady();
//		auto ready1c = future1c.IsReady();
//		auto ready2 = future2.IsReady();
//		auto ready3 = future3.IsReady();
//	
//		ASSERT_EQ(ready1a, true);
//		ASSERT_EQ(ready1b, true);
//		ASSERT_EQ(ready1c, true);
//		ASSERT_EQ(ready2, true);
//		ASSERT_EQ(ready3, true);
//	}

////////////////////////////////////////////////////////////////////////////////

//	TEST_F(Assets, Storage_SimpleParallelLoads)
//	{
//		std::size_t count = 128;
//	
//		Manager manager;
//	
//		auto scheduler = std::make_shared<Parallel::Scheduler>();
//	
//		auto result = manager.RegisterStorage<ParallelDummyLoadStorage>(scheduler);
//		ASSERT_EQ(result, true);
//	
//		using TestEntry = ParallelDummyLoadStorage::EntryType;
//	
//		std::deque<Parallel::Future<std::string>> assets;
//	
//		for (auto loop : Range(count))
//		{
//			std::string name_a(std::to_string(loop) + "a");
//			std::string name_b(std::to_string(loop) + "b");
//		
//			auto task_a = manager.LoadFromFile<ParallelDummyLoadStorage>(name_a);
//			auto task_b = manager.LoadFromFile<ParallelDummyLoadStorage>(name_b);
//	
//			auto task = [](TestEntry entry_a, TestEntry entry_b)
//			{
//				auto a = entry_a.GetName();		
//				auto b = entry_b.GetName();
//	
//				return a + b;
//			};
//	
//			assets.push_back(scheduler->AddImmediateTask(task, std::move(task_a), std::move(task_b)));
//		}
//	
//		for (;;)
//		{
//			std::size_t index = 0;
//			std::size_t ready = 0;
//	
//			for (auto asset : assets)
//			{
//				if (asset.IsReady())
//				{
//					std::string check(std::to_string(index) + "a" + std::to_string(index) + "b");
//					ASSERT_EQ(asset.Get(), check);
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

//	TEST_F(Assets, Storage_CheckEmpty)
//	{
//		SimpleStorage storage;
//	
//		SimpleStorage::Future future1;
//		SimpleStorage::Future future2;
//		SimpleStorage::Future future3;
//	
//	//	SimpleStorage::Instance instance;
//	
//		auto result1 = storage.LoadFromFile(future1, "test1");
//	//	auto result2 = storage.LoadFromInstance(future2, "test2", instance);
//	//	auto result3 = storage.LoadFromMemory(future3, "test3", nullptr, 0);
//	
//		ASSERT_EQ(result1, true);
//	//	ASSERT_EQ(result2, true);
//	//	ASSERT_EQ(result3, true);
//	
//		auto valid1 = future1.IsValid();
//	//	auto valid2 = future2.IsValid();
//	//	auto valid3 = future3.IsValid();
//	
//		auto ready1 = future1.IsReady();
//	//	auto ready2 = future2.IsReady();
//	//	auto ready3 = future3.IsReady();
//	
//		ASSERT_EQ(valid1, false);
//	//	ASSERT_EQ(valid2, false);
//	//	ASSERT_EQ(valid3, false);
//	
//		ASSERT_EQ(ready1, false);
//	//	ASSERT_EQ(ready2, false);
//	//	ASSERT_EQ(ready3, false);
//	}
