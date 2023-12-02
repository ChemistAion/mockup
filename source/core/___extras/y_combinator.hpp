#pragma once

namespace Mockup::Core
{
	namespace Detail
	{
		template <typename Function>
		struct Y_CombinatorResult
		{
			Function function_;

			template <typename Type>
			explicit Y_CombinatorResult(Type&& type)
				: function_(std::forward<Type>(type))
			{
			}

			template <typename... Arguments>
			decltype(auto) operator()(Arguments&&... arguments)
			{
				return function_(std::ref(*this), std::forward<Arguments>(arguments)...);
			}
		};
	}

	template <typename Function>
	decltype(auto) Y_Combinator(Function&& function)
	{
		return Detail::Y_CombinatorResult<std::decay_t<Function>>(std::forward<Function>(function));
	}
}