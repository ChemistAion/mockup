#include "pch.hpp"

#include "scheduler.hpp"

namespace Mockup::Core::Parallel
{
	Scheduler::Scheduler()
	{
		index_.store(0, std::memory_order_relaxed);
		done_.store(false, std::memory_order_relaxed);

		for (auto index : Range(cParallel_PoolSizeWorkers))
		{
			workers_[index] = std::move(std::thread(&Scheduler::ProcessImmediateTasks, this, index));
		}
	}

	Scheduler::~Scheduler()
	{
		done_.store(true, std::memory_order_relaxed);

		for (auto& worker : workers_)
		{
			if (worker.joinable())
			{
				worker.join();
			}
		}
	}
}