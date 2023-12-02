#pragma once

#include "../extras/detector.hpp"

#include <atomic>
#include <chrono>
#include <future>
#include <memory>
#include <optional>
#include <type_traits>
#include <utility>

namespace Mockup::Core::Parallel
{
	namespace Detail
	{
		template <typename Type>

		using HasMark = decltype(std::declval<Type>().MarkAsFuture());

		template <typename Type>
		using IsFutureImpl = IsDetected<HasMark, Type>;

		////////////////////////////////////////////////////////////////////////////////

		template <typename Type>
		struct DecayFutureImpl
		{
			using type = Type;
		};

		template <template <typename> class Class, typename Type>
		struct DecayFutureImpl<Class<Type>>
		{
			using type = Type;
		};

		template <template <typename> class Class, typename Type>
		struct DecayFutureImpl<Class<Type>&>
		{
			using type = Type;
		};

		template <template <typename> class Class, typename Type>
		struct DecayFutureImpl<const Class<Type>&>
		{
			using type = Type;
		};
	}

	////////////////////////////////////////////////////////////////////////////////

	template <typename Type>
	constexpr bool IsFuture = Detail::IsFutureImpl<std::decay_t<Type>>::value;

	template <typename Type>
	using DecayFutureType = typename Detail::DecayFutureImpl<Type>::type;

	template <typename Type>
	using DecayIfFuture = std::conditional_t<IsFuture<Type>, DecayFutureType<Type>, Type>;

	////////////////////////////////////////////////////////////////////////////////

	template <typename Type>
	class Future
	{
	private:
		std::shared_future<Type> future_;

		void MarkAsFuture()
		{
		}
	public:
		Future() = default;

		explicit Future(std::shared_future<Type>&& future)
		{
			future_ = std::move(future);
		}

		bool IsValid() const
		{
			return future_.valid();
		}

		bool IsReady() const
		{
			if (future_.valid())
			{
				return future_.wait_for(std::chrono::steady_clock::duration::zero()) == std::future_status::ready;
			}
			
			return false;
		}

		decltype(auto) Get()
		{
			return future_.get();
		}
	};
}
