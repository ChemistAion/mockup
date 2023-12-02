#pragma once

#include "arity.hpp"

namespace Mockup::Serializer
{
	template <typename Type>
	inline auto BindAsTuple(Type& type)
	{
		constexpr auto const arity = Arity<Type>();

		if constexpr (arity == 0)
		{
			return std::make_tuple();
		}
		else if constexpr (arity == 1)
		{
			auto&[p1] = type;
			return std::make_tuple(&p1);
		}
		else if constexpr (arity == 2)
		{
			auto&[p1, p2] = type;
			return std::make_tuple(&p1, &p2);
		}
		else if constexpr (arity == 3)
		{
			auto&[p1, p2, p3] = type;
			return std::make_tuple(&p1, &p2, &p3);
		}
		else if constexpr (arity == 4)
		{
			auto&[p1, p2, p3, p4] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4);
		}
		else if constexpr (arity == 5)
		{
			auto&[p1, p2, p3, p4, p5] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5);
		}
		else if constexpr (arity == 6)
		{
			auto&[p1, p2, p3, p4, p5, p6] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6);
		}
		else if constexpr (arity == 7)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7);
		}
		else if constexpr (arity == 8)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8);
		}
		else if constexpr (arity == 9)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9);
		}
		else if constexpr (arity == 10)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10);
		}
		else if constexpr (arity == 11)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11);
		}
		else if constexpr (arity == 12)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12);
		}
		else if constexpr (arity == 13)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13);
		}
		else if constexpr (arity == 14)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14);
		}
		else if constexpr (arity == 15)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15);
		}
		else if constexpr (arity == 16)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16] = type;
			return std::make_tuple(&p1, &p2, &p3, &p4, &p5, &p6, &p7, &p8, &p9, &p10, &p11, &p12, &p13, &p14, &p15, &p16);
		}
	}

	template <typename Type>
	inline auto BindAsTie(Type& type)
	{
		constexpr auto const arity = Arity<Type>();

		if constexpr (arity == 0)
		{
			return std::tie();
		}
		else if constexpr (arity == 1)
		{
			auto&[p1] = type;
			return std::tie(p1);
		}
		else if constexpr (arity == 2)
		{
			auto&[p1, p2] = type;
			return std::tie(p1, p2);
		}
		else if constexpr (arity == 3)
		{
			auto&[p1, p2, p3] = type;
			return std::tie(p1, p2, p3);
		}
		else if constexpr (arity == 4)
		{
			auto&[p1, p2, p3, p4] = type;
			return std::tie(p1, p2, p3, p4);
		}
		else if constexpr (arity == 5)
		{
			auto&[p1, p2, p3, p4, p5] = type;
			return std::tie(p1, p2, p3, p4, p5);
		}
		else if constexpr (arity == 6)
		{
			auto&[p1, p2, p3, p4, p5, p6] = type;
			return std::tie(p1, p2, p3, p4, p5, p6);
		}
		else if constexpr (arity == 7)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7);
		}
		else if constexpr (arity == 8)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7, p8);
		}
		else if constexpr (arity == 9)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7, p8, p9);
		}
		else if constexpr (arity == 10)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10);
		}
		else if constexpr (arity == 11)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11);
		}
		else if constexpr (arity == 12)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12);
		}
		else if constexpr (arity == 13)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13);
		}
		else if constexpr (arity == 14)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14);
		}
		else if constexpr (arity == 15)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15);
		}
		else if constexpr (arity == 16)
		{
			auto&[p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16] = type;
			return std::tie(p1, p2, p3, p4, p5, p6, p7, p8, p9, p10, p11, p12, p13, p14, p15, p16);
		}
	}

	template <typename Field, typename Function>
	inline void ForEachFieldAsTuple(Field&& field, Function&& function)
	{
		std::apply([&](auto&&... arguments) { (function(arguments), ...); }, BindAsTuple(std::forward<Field>(field)));
	}

	template <typename Field, typename Function>
	inline void ForEachFieldAsTie(Field&& field, Function&& function)
	{
		std::apply([&](auto&&... arguments) { (function(arguments), ...); }, BindAsTie(std::forward<Field>(field)));
	}
}