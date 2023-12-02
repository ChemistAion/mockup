#pragma once

#include "director.hpp"

#include "system.hpp"

#include <iostream>

////////////////////////////////////////////////////////////////////////////////

BENCHMARK_DEFINE_F(Director, System_Benchmark)(benchmark::State& state)
{
	using namespace Primitives;

	////////////////////////////////////////////////////////////////////////////////

	Registry registry;

	registry.Emplace<FeatureTestA>();
	registry.Emplace<FeatureTestAB>();
	registry.Emplace<FeatureTestABC>();

	auto& featureA = registry.Get<FeatureTestA>();
	auto& featureAB = registry.Get<FeatureTestAB>();
	auto& featureABC = registry.Get<FeatureTestABC>();

	featureABC.MountSystem<TestSystemABC>(1);
	featureABC.MountSystem<TestSystemAB>(1);
	featureABC.MountSystem<TestSystemA>(1);

	featureAB.MountSystem<TestSystemAB>(1);
	featureAB.MountSystem<TestSystemA>(1);

	featureA.MountSystem<TestSystemA>(1);

	EntityType entitiesA[count];
	EntityType entitiesAB[count];
	EntityType entitiesABC[count];

	////////////////////////////////////////////////////////////////////////////////

	std::uint64_t count = 0;
	
	while (state.KeepRunning())
	{
		registry.Clear();
//		registry.Reserve(1u << 24u);
//		registry.Reserve<TestComponentA, TestComponentAB, TestComponentABC>(1u << 24u);

		registry.Create(std::begin(entitiesA), std::end(entitiesA));	
		for (const auto entity : entitiesA)
		{
			registry.Emplace<TestComponentA>(entity, 1);
			registry.Emplace<TestComponentAB>(entity, 2, TestComponentA(1));
			registry.Emplace<TestComponentABC>(entity, 3, TestComponentA(2), TestComponentAB(1, 1));
		}
		
		registry.Create(std::begin(entitiesAB), std::end(entitiesAB));
		for (const auto entity : entitiesAB)
		{
			registry.Emplace<TestComponentA>(entity, 1);
			registry.Emplace<TestComponentAB>(entity, 2, TestComponentA(1));
		}
		
		registry.Create(std::begin(entitiesABC), std::end(entitiesABC));
		for (const auto entity : entitiesABC)
		{
			registry.Emplace<TestComponentA>(entity, 1);
		}
		
		registry.Process(TestEventA(count));
		registry.Process(TestEventAB(count, TestEventA(count)));
		registry.Process(TestEventABC(count, TestEventA(count), TestEventAB(count, TestEventA(count))));
		
		++count;
	}
}

BENCHMARK_REGISTER_F(Director, System_Benchmark)->Repetitions(4)->Unit(benchmark::kNanosecond)->ReportAggregatesOnly(false)->DisplayAggregatesOnly(false);