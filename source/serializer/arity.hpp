#pragma once

#include "extras/decay.hpp"

#include <type_traits>

namespace Mockup::Serializer
{
	namespace Detail
	{
		struct Instance
		{
			template <typename Type>
			operator Type () const;
		};
	
		template<typename Aggregate, typename IndexSequence = std::index_sequence<>, typename = void>
		struct ArityImpl : IndexSequence
		{
		};
	
		template<typename Aggregate, std::size_t... Indices>
		struct ArityImpl
			<
			Aggregate, std::index_sequence<Indices...>,
			std::void_t<decltype(Aggregate{ (Indices, std::declval<Instance>())..., std::declval<Instance>() }) >
			>
			: ArityImpl<Aggregate, std::index_sequence<Indices..., sizeof... (Indices)>>
		{
		};
	}
	
	template<typename Aggregate>
	constexpr std::size_t Arity()
	{
		return Detail::ArityImpl<DecayType<Aggregate>>().size();
	}
}