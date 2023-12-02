#pragma once

#include "size.hpp"
#include "context.hpp"

#include "extras/decay.hpp"

#include <type_traits>		

namespace Mockup::Serializer
{

	////////////////////////////////////////////////////////////////////////////////

	template <typename ContextType, typename Type>
	void Serialize(ContextType& context, const Type* origin, const std::size_t position)
	{
		using TargetType = DecayType<Type>;
	
		if constexpr (!std::is_scalar_v<TargetType>)
		{
			static_assert(std::is_aggregate_v<TargetType> && std::is_standard_layout_v<TargetType> && !std::is_polymorphic_v<TargetType>, "This type cannot be automatically serialized.");
	
			ForEachFieldAsTuple
			(
				*origin,
				[&](auto& field)
				{
					auto const offset = static_cast<std::size_t>(reinterpret_cast<const char*>(field) - reinterpret_cast<const char*>(origin));
					Serialize(context, field, position + offset);
				}
			);
		}
		else if constexpr (std::is_pointer_v<TargetType>)
		{
			origin;
			context.Write(position, TargetType(0));
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	template <typename Type>
	std::size_t Serialize(Type& element)
	{
		return 0;

//		Compact compact(element);
//		
//		auto size = compact.Size();
//		
//		return size;

//		SerializationSize serialization_size;
//		Context<SerializationSize> context(serialization_size);

////	auto size = Size<Type>();
////	auto alignment = std::alignment_of_v<DecayType<Type>>;
////	auto result = context.Write(&element, 0, alignment);
	
//		ForEachFieldAsTie
//		(
//			element,
//			[&](auto& field)
//			{
//				auto size = Size<decltype(field)>();
//				auto alignment = std::alignment_of_v<decltype(field)>;
//	
//				auto const test = sizeof(field);
//				auto const field_offset = static_cast<std::size_t>(reinterpret_cast<const char*>(&field) - reinterpret_cast<const char*>(&element));
//	
//				auto result = context.Write(&element, size, alignment);
//			}
//		);

//		return serialization_size.GetSize();

////	Storage storage;
////	Context<Storage> context(storage);
////	
////	auto size = Size<Type>();
////	auto alignment = std::alignment_of_v<DecayType<Type>>;
////	auto position = context.Write(&element, 0, alignment);
////	
////	auto origin = &element;
////	
////	ForEachField
////	(
////		*origin,
////		[&](auto& field)
////		{
////			auto const field_offset = static_cast<std::size_t>(reinterpret_cast<const char*>(field) - reinterpret_cast<const char*>(origin));
////			Serialize(context, field, position + field_offset);
////		}
////	);
////	
////	return std::move(storage.storage_);
	}

	////////////////////////////////////////////////////////////////////////////////

//	template <typename Target>
//	void Deserialize(std::uint8_t* origin, Target** target)
//	{
//		using Type = DecayType<Target>;
//	
//		if constexpr (!std::is_pointer_v<Type> && !std::is_scalar_v<Type>)
//		{
//			ForEachField
//			(
//				*(*target),
//				[&](auto& field) { Deserialize(origin, &field); }
//			);
//		}
//	}
//	
//	template <typename Type, typename Container>
//	Type* Deserialize(Container& container)
//	{
//		auto result = reinterpret_cast<Type*>(&container[0]);
//	
//		Deserialize(&container[0], &result);
//		return result;
//	}
}