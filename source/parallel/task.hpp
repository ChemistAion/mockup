#pragma once

#include "future.hpp"

#include "../extras/decay.hpp"

#include <functional>
#include <future>
#include <memory>
#include <tuple>
#include <type_traits>
#include <utility>

namespace Mockup::Core::Parallel
{
	constexpr std::size_t cParallel_TaskModelCapacity = 256 - sizeof(void*);
	
	class Task final
	{
		std::aligned_storage_t<cParallel_TaskModelCapacity> model_;
	
		////////////////////////////////////////////////////////////////////////////////
	
		struct Concept
		{
			bool(*ready_)(void* self) noexcept;
			bool(*done_)(void* self) noexcept;
			void(*move_)(void* self, void* source) noexcept;
	
			void(*invoke_)(void* self);
			void*(*data_)(void* self) noexcept;
	
			void(*dtor_)(void* self);
		};
	
		////////////////////////////////////////////////////////////////////////////////
	
		template <class...>
		struct Model;
	
		template <class Result, class... Archetypes, class... Futures>
		struct Model<Result(Archetypes...), Futures...>
		{
			std::packaged_task<Result(Archetypes...)> trampoline_;
			std::tuple<DecayReferenceWrapperType<Futures>...> arguments_;
			bool completed_;
	
			Model(Model&&) noexcept = default;
	
			template <class Callable, class... Arguments>
			explicit Model(Callable&& callable, Arguments&&... arguments) :
				trampoline_(std::forward<Callable>(callable)),
				arguments_(std::forward<Arguments>(arguments)...),
				completed_(false)
			{
			}
	
			decltype(auto) GetFuture()
			{
				return Future<Result>(trampoline_.get_future().share());
			}
	
			static bool ready_(void* self) noexcept
			{
				return static_cast<Model*>(self)->ReadyImpl(std::index_sequence_for<Futures...>());
			}

			static bool done_(void* self) noexcept
			{
				return static_cast<Model*>(self)->completed_;
			}
	
			static void move_(void* self, void* source) noexcept
			{
				new (source) Model(std::move(*static_cast<Model*>(self)));
			}
	
			static void invoke_(void* self)
			{
				static_cast<Model*>(self)->InvokeImpl(std::index_sequence_for<Futures...>());
				static_cast<Model*>(self)->completed_ = true;
			}
	
			static void* data_(void* self) noexcept
			{
				return self;
			}
	
			static void dtor_(void* self)
			{
				static_cast<Model*>(self)->~Model();
			}
	
			static constexpr Concept vtable_ = { ready_, done_, move_, invoke_, data_, dtor_ };
	
		private:
			template <typename Type>
			inline decltype(auto) CallGet(Type&& type)
			{
				if constexpr (IsFuture<Type>)
				{
					return type.Get();
				}
				else
				{
					return std::forward<Type>(type);
				}
			}
	
			template <std::size_t... Index>
			inline void InvokeImpl(std::index_sequence<Index...>)
			{
				std::invoke(trampoline_, CallGet(std::get<Index>(std::move(arguments_)))...);
			}
	
			////////////////////////////////////////////////////////////////////////////////
	
			template <typename Type>
			inline bool CallReady(const Type& type) const
			{
				if constexpr (IsFuture<Type>)
				{
					return type.IsReady();
				}
				else
				{
					(void)type;
					return true;
				}
			}
	
			inline bool CheckIfReady() const
			{
				return true;
			}
	
			template <typename... Arguments>
			inline bool CheckIfReady(bool first, Arguments... arguments) const
			{
				return first & CheckIfReady(arguments...);
			}
	
			template <std::size_t... Index>
			inline bool ReadyImpl(std::index_sequence<Index...>) const
			{
				return CheckIfReady(CallReady(std::get<Index>(arguments_))...);
			}
		};
	
		////////////////////////////////////////////////////////////////////////////////
	
		static bool ready_(void*) noexcept
		{
			return true;
		}

		static bool done_(void*) noexcept
		{
			return true;
		}
	
		static void move_(void*, void*) noexcept
		{
		}
	
		static void invoke_(void*)
		{
			throw std::bad_function_call();
		}
	
		static void* data_(void*) noexcept
		{
			return nullptr;
		}
	
		static void dtor_(void*)
		{
		}
	
		static constexpr Concept vtable_ = { ready_, done_, move_, invoke_, data_, dtor_ };
		const Concept* vtable_ptr_ = &vtable_;
	
		////////////////////////////////////////////////////////////////////////////////
	
		template <class Callable, class... Arguments>
		Task(Callable&& callable, Arguments&&... arguments)
		{
			using result = std::invoke_result_t<Callable, DecayIfFuture<Arguments>...>;
			using model = Model<result(DecayIfFuture<Arguments>...), Arguments...>;
	
			static_assert(sizeof(model) <= cParallel_TaskModelCapacity);
	
			new (&model_) model(std::forward<Callable>(callable), std::forward<Arguments>(arguments)...);
			vtable_ptr_ = &model::vtable_;
		}
	
	public:
		Task() noexcept = default;
	
		~Task()
		{
			vtable_ptr_->dtor_(&model_);
		}
	
		////////////////////////////////////////////////////////////////////////////////
	
		Task(const Task&) = delete;
		Task& operator=(const Task&) = delete;
	
		Task(Task&& other) noexcept
		{
			vtable_ptr_ = other.vtable_ptr_;
			vtable_ptr_->move_(&other.model_, &model_);
		}
	
		Task& operator=(Task&& other) noexcept
		{
			vtable_ptr_->dtor_(&model_);
	
			vtable_ptr_ = other.vtable_ptr_;
			vtable_ptr_->move_(&other.model_, &model_);
	
			return *this;
		}
	
		////////////////////////////////////////////////////////////////////////////////
	
		template <class Callable, class... Arguments>
		static decltype(auto) CreateTask(Callable&& callable, Arguments&&... arguments)
		{
			using result = std::invoke_result_t<Callable, DecayIfFuture<Arguments>...>;
			using model = Model<result(DecayIfFuture<Arguments>...), Arguments...>;
	
			Task task(std::forward<Callable>(callable), std::forward<Arguments>(arguments)...);
			auto future = static_cast<model*>(task.Data())->GetFuture();

			return std::pair<Task, Future<result>>(std::move(task), std::move(future));
		}
	
		////////////////////////////////////////////////////////////////////////////////
	
		inline bool Ready() noexcept
		{
			return vtable_ptr_->ready_(&model_);
		}

		inline bool Done() noexcept
		{
			return vtable_ptr_->done_(&model_);
		}
	
		inline void Invoke()
		{
			vtable_ptr_->invoke_(&model_);
		}
		
		inline void* Data() noexcept
		{
			return vtable_ptr_->data_(&model_);
		}
	};
}