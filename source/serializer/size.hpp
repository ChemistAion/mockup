#pragma once

//#include "bind.hpp"

//#include "extras/decay.hpp"

#include <cassert>
//#include <memory>
#include <vector>
//#include <tuple>
//#include <type_traits>

namespace Mockup::Serializer
{
	template <class...>
	struct Size;
	
	template <class Type>
	struct Size<Type>
	{
		std::size_t size_;

		explicit Size(void* self)
		{
			static_assert(std::is_pod_v<Type>, "No type size specialization...");
			size_ = sizeof(Type);
		}
	};

	template <class Type>
	struct Size<std::vector<Type>>
	{
		std::size_t size_;
	
		explicit Size(void* self)
		{
			static_assert(std::is_pod_v<Type>, "No type size specialization...");

			auto vector = reinterpret_cast<std::vector<Type>*>(self);
			size_ = sizeof(Type) * vector->size();
		}
	};

//	class Compact
//	{
//		template <class... Arguments>
//		struct Model
//		{
//			std::tuple<Arguments...> arguments_;
//	
//			explicit Model(Arguments&&... arguments) : arguments_(std::forward<Arguments>(arguments)...)
//			{
//			}
//	
//			inline constexpr std::size_t GetSize()
//			{
//				return GetSizeImpl(std::index_sequence_for<Arguments...>());
//			}
//	
//		private:
//			template<typename Type>
//			inline constexpr std::size_t CallGetSize(Type& type)
//			{
//				Size<Type> size(&type);
//				return size.size_;
//			}
//	
//			inline constexpr std::size_t SumGetSize() const
//			{
//				return 0;
//			}
//	
//			template <typename... Arguments>
//			inline constexpr std::size_t SumGetSize(std::size_t first, Arguments... arguments) const
//			{
//				return first + SumGetSize(arguments...);
//			}
//	
//			template <std::size_t... Index>
//			inline constexpr std::size_t GetSizeImpl(std::index_sequence<Index...>)
//			{
//				return SumGetSize(CallGetSize(std::get<Index>(arguments_))...);
//			}
//		};
//	
//		std::size_t size_ = 0;
//	public:
//		Compact() = delete;
//	
//		template <class... Arguments>
//		Compact(Arguments&&... arguments)
//		{
//			Model<Arguments...> model(std::forward<Arguments>(arguments)...);
//	
//			size_ = model.GetSize();
//		}
//	
//		inline std::size_t GetSize() noexcept
//		{
//			return size_;
//		}
//	};
}


//	template <class Type>
//	inline std::size_t Size(void*)
//	{
//		static_assert(std::is_pod_v<Type>, "No type size specialization...");
//		return sizeof(Type);
//	}
//	
//	template <>
//	inline std::size_t Size<std::vector<int>>(void* self)
//	{
//		auto custom = reinterpret_cast<std::vector<int>*>(self);
//		auto size = sizeof(int);
//	
//		return size * custom->size();
//	}
//	
//	template <>
//	inline std::size_t Size<std::vector<float>>(void* self)
//	{
//		auto custom = reinterpret_cast<std::vector<float>*>(self);
//		auto size = sizeof(float);
//	
//		return size * custom->size();
//	}
//	
//	template <>
//	inline std::size_t Size<std::vector<char>>(void* self)
//	{
//		auto custom = reinterpret_cast<std::vector<char>*>(self);
//		auto size = sizeof(char);
//	
//		return size * custom->size();
//	}

//	template <class Type, class...>
//	struct Size;
//	
//	template <class Type, class = typename std::enable_if<std::is_pod_v<Type>>::type>
//	struct Size<Type>
//	{
//		std::size_t size_ = sizeof(Type);
//	};

//	template <>
//	struct Size<std::vector<int>>
//	{
//		std::size_t size_ = 1234;
//	};

//	template <class Type>
//	inline std::size_t Size(void*)
//	{
//		return sizeof(Type);
//	}

//	template <class Type>
//	inline std::size_t Size<std::vector<int>>(void* self)
//	{
//		auto custom = reinterpret_cast<std::vector<int>*>(self);
//		auto size = sizeof(int);
//	
//		return size * custom->size();
//	}


//		template <typename Type>
//		class Compact
//		{
//			std::size_t size_ = 0;
//	
//			template <typename Field>
//			void AddFieldSize(Field&& field)
//			{		
//				auto size = GetSize<Field>(nullptr);
//	//			auto alignment = std::alignment_of_v<Field>;
//	
//				size_ += size;
//	
//				return;
//			}
//	
//	
//		public:
//			Compact(Type& type)
//			{
//	//			ForEachFieldAsTie(type, [&](auto&& field) { AddFieldSize(std::forward<decltype(field)>(field)); } );
//	//			ForEachFieldAsTie(type, [&](auto&& field) { AddFieldSize(field); });
//				ForEachFieldAsTie
//				(
//					type,
//					[&](auto&& field)
//					{
//	//					auto test = std::is_aggregate_v<test>;
//	
//	//					AddFieldSize(field);
//					}
//				);
//			}
//	
//			std::size_t Size() const
//			{
//				return size_;
//			}
//	};

//		void AddFieldSize(void* field, const std::size_t size, std::size_t alignment)
//		{
//			assert(alignment != 0);
//					
//			auto base = reinterpret_cast<std::uint8_t*>(&type_);
//			auto offset = base + offset_;
//			
//			auto unaligned = reinterpret_cast<void*>(offset);
//			auto space = std::numeric_limits<std::size_t>::max();
//			auto const aligned = std::align(alignment, size, unaligned, space);
//			
//			const std::size_t placement = aligned ? static_cast<std::uint8_t*>(aligned) - base : 0;
//			
//			assert(placement >= offset_);
//			
//			auto const adjustment = placement - offset_;
//			
//			offset_ += adjustment;
//		}

//	template <typename ContextType>
//	class SerializationSize
//	{
//		std::size_t offset_ = 0;
//	public:
//		template <typename Type>
//		void Write(const std::size_t position, const Type& value)
//		{
//		}
//	
//		std::size_t Write(const void* pointer, const std::size_t size, std::size_t alignment)
//		{
//			assert(alignment != 0);
//	
//			auto aligned_size = size;
//	
//			auto base = reinterpret_cast<std::uint8_t*>(const_cast<void*>(pointer));
//			auto offset = base + offset_;
//	
//			auto unaligned = reinterpret_cast<void*>(offset);
//			auto space = std::numeric_limits<std::size_t>::max();
//			auto const aligned = std::align(alignment, size, unaligned, space);
//			
//			const std::size_t placement = aligned ? static_cast<std::uint8_t*>(aligned) - base : 0;
//	
//			assert(placement >= offset_);
//	
//			auto const adjustment = placement - offset_;
//	
//			offset_ += adjustment;
//			aligned_size += adjustment;
//	
//			auto const result = offset_;
//	
//			offset_ += size;
//	
//			return result;
//		}
//	
//		std::size_t GetSize() const
//		{
//			return offset_;
//		}
//	};