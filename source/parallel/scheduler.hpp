#pragma once

#include "future.hpp"
#include "task.hpp"
#include "executor.hpp"

#include "../extras/range.hpp"

#include <array>
#include <atomic>
#include <chrono>
#include <vector>
#include <thread>

namespace Mockup::Core::Parallel
{
	constexpr std::size_t cParallel_PoolSizeWorkers = 4;

	class Scheduler final
	{
		std::atomic_size_t index_;
		std::atomic_bool done_;

		std::array<Executor, cParallel_PoolSizeWorkers> executors_;
		std::array<std::thread, cParallel_PoolSizeWorkers> workers_;

		void ProcessImmediateTasks(std::size_t index)
		{
			auto& executor = executors_[index];

			for(;;)
			{
				if (executor.TryProcess())
				{
					continue;
				}

				if (done_.load(std::memory_order_relaxed))
				{
					return;
				}
			}
		}
	public:
		Scheduler();
		~Scheduler();

		Scheduler(const Scheduler&) = delete;
		Scheduler& operator=(const Scheduler&) = delete;

		template <class Callable, class... Arguments>
		decltype(auto) AddImmediateTask(Callable&& callable, Arguments&&... arguments)
		{
			auto[task, future] = Task::CreateTask(std::forward<Callable>(callable), std::forward<Arguments>(arguments)...);	

			auto index = index_.fetch_add(1, std::memory_order_relaxed);

			for (;;)
			{			
				auto& executor = executors_[index++ & (cParallel_PoolSizeWorkers - 1)];

				if (executor.TryPush(std::move(task)))
				{
					break;
				}
			}

			return future;
		}
		
//		template <class Callable, class... Arguments>
//		decltype(auto) AddWaitingTask(Callable&& callable, Arguments&&... arguments)
//		{
//			auto[task, future] = Task::CreateTask(std::forward<Callable>(callable), std::forward<Arguments>(arguments)...);
//			
//			executors_[0].Push(std::move(task));		
//			return future;
//		}
	};
}
