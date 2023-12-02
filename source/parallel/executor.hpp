#pragma once

#include "task.hpp"

#include <algorithm>
#include <array>
#include <atomic>
#include <chrono>
#include <condition_variable>	
#include <deque>
#include <execution>
#include <functional>
#include <limits>
#include <mutex>
#include <new>
#include <optional>
#include <thread>

#include <iostream>

#pragma warning(disable:4324) // structure was padded due to __declspec(align())

namespace Mockup::Core::Parallel
{
	constexpr std::size_t cParallel_ExecutorTasksCapacity = 1024;
	constexpr std::size_t cParallel_ExecutorCacheLineSize = std::hardware_destructive_interference_size;

	class Executor final
	{
		struct Cell
		{
			std::atomic_size_t sequence_;
			Task task_;
		};

		alignas(cParallel_ExecutorCacheLineSize) Cell* storage_;
		alignas(cParallel_ExecutorCacheLineSize) std::atomic_size_t enqueue_;
		alignas(cParallel_ExecutorCacheLineSize) std::atomic_size_t dequeue_;
	public:
		Executor()
		{
			static_assert((cParallel_ExecutorTasksCapacity > 0 && ((cParallel_ExecutorTasksCapacity & (cParallel_ExecutorTasksCapacity - 1)) == 0)));

			storage_ = new Cell[cParallel_ExecutorTasksCapacity];

			for (auto index : Range(cParallel_ExecutorTasksCapacity))
			{
				storage_[index].sequence_.store(index, std::memory_order_relaxed);
			}

			enqueue_.store(0, std::memory_order_relaxed);
			dequeue_.store(0, std::memory_order_relaxed);
		}

		~Executor()
		{
			delete[] storage_;
		}

		Executor(const Executor&) = delete;
		Executor& operator=(const Executor&) = delete;

		Executor(Executor&& other) noexcept = delete;
		Executor& operator=(Executor&& other) noexcept = delete;

		bool TryPush(Task&& task)
		{
//			auto position = enqueue_.load(std::memory_order_relaxed);
//			auto cell = &storage_[position & (cParallel_ExecutorTasksCapacity - 1)];
//			auto sequence = cell->sequence_.load(std::memory_order_acquire);
//			
//			if (sequence == position)
//			{
//				enqueue_.fetch_add(1, std::memory_order_relaxed);
//			
//				cell->task_ = std::move(task);
//				cell->sequence_.store(position + 1, std::memory_order_release);
//			
//				return true;
//			}
//			
//			return false;

			Cell* cell;
			
			auto position = enqueue_.load(std::memory_order_relaxed);
			
			////////////////////////////////////////////////////////////////////////////////
			
			for (;;)
			{
				cell = &storage_[position & (cParallel_ExecutorTasksCapacity - 1)];
			
				auto sequence = cell->sequence_.load(std::memory_order_acquire);
			
				auto diff = (std::intptr_t)sequence - (std::intptr_t)position;
			
				if (diff == 0)
				{
					if (enqueue_.compare_exchange_weak(position, position + 1, std::memory_order_acq_rel))
					{
						break;
					}
			
					continue;
				}
			
				if (diff < 0)
				{
					return false;
				}
			
				position = enqueue_.load(std::memory_order_relaxed);
			}
			
			////////////////////////////////////////////////////////////////////////////////
			
			cell->task_ = std::move(task);
			cell->sequence_.store(position + 1, std::memory_order_release);
			
			return true;
		}

		bool TryProcess()
		{
			auto position = dequeue_.load(std::memory_order_relaxed);
			auto cell = &storage_[position & (cParallel_ExecutorTasksCapacity - 1)];
			auto sequence = cell->sequence_.load(std::memory_order_acquire);

			if (sequence == position + 1)
			{
				if (cell->task_.Done())
				{
					dequeue_.fetch_add(1, std::memory_order_relaxed);
					cell->sequence_.store(position + cParallel_ExecutorTasksCapacity, std::memory_order_release);

					return true;
				}

				if (!cell->task_.Ready())
				{
					auto end = enqueue_.load(std::memory_order_relaxed);
					
					for (auto ready = position + 1; ready < end; ++ready)
					{
						auto victim = &storage_[ready & (cParallel_ExecutorTasksCapacity - 1)];
					
						if (victim->task_.Done())
						{
							continue;
						}

						if (victim->task_.Ready())
						{
							victim->task_.Invoke();
						}
					}

					return true;
				}

				dequeue_.fetch_add(1, std::memory_order_relaxed);
				
				cell->task_.Invoke();
				cell->sequence_.store(position + cParallel_ExecutorTasksCapacity, std::memory_order_release);

				return true;		
			}

			return false;
		}
	};
}
