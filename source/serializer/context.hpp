#pragma once

#include <cstddef>
#include <cstring>
#include <memory>
#include <string>
#include <vector>
#include <typeinfo>
#include <type_traits>

namespace Mockup::Serializer
{
	class Context
	{
		friend class Chunk;

		std::string name_;
		std::string debug_;

		std::size_t size_ = 0;

		std::unique_ptr<std::byte[]> storage_;

	public:
		Context() = default;

		template <class Type>
		Context(const char* name, Type&& type)
		{
			name_ = std::string(name);
			debug_ = typeid(type).name();

			size_ = sizeof(Type);

			storage_ = std::make_unique<std::byte[]>(size_);
			std::memcpy(storage_.get(), &type, size_);

			return;
		}

		template <class Type>
		Context(const char* name, std::vector<Type>& vector)
		{
			name_ = std::string(name);
			debug_ = typeid(vector).name();

			size_ = sizeof(Type) * vector.size();
		
			storage_ = std::make_unique<std::byte[]>(size_);
			std::memcpy(storage_.get(), vector.data(), size_);

			return;
		}

		////////////////////////////////////////////////////////////////////////////////

		auto GetName() const
		{
			return name_;
		}

		auto GetDebugInfo() const
		{
			return debug_;
		}

		auto GetSize() const
		{
			return size_;
		}

		auto GetData() const
		{
			return storage_.get();
		}
	};
}

//	template <typename ContextType>
//	class Context
//	{
//		ContextType& context_;
//	public:
//		explicit Context(ContextType& context) : context_(context)
//		{
//		}
//	
//		std::size_t Write(const void* pointer, const std::size_t size, std::size_t alignment)
//		{
//			return context_.Write(pointer, size, alignment);
//		}
//		
//		template <typename Type>
//		void Write(const std::size_t position, const Type& element)
//		{
//			context_.Write(position, element);
//		}
//	};

//	template <class...>
//	struct Size;
//	
//	template <class Type>
//	struct Size<Type>
//	{
//		std::size_t size_;
//	
//		explicit Size(void* self)
//		{
//			static_assert(std::is_pod_v<Type>, "No type size specialization");
//			size_ = sizeof(Type);
//		}
//	};
//	
//	template <class Type>
//	struct Size<std::vector<Type>>
//	{
//		std::size_t size_;
//	
//		explicit Size(void* self)
//		{
//			static_assert(std::is_pod_v<Type>, "No type size specialization");
//	
//			auto vector = reinterpret_cast<std::vector<Type>*>(self);
//			size_ = sizeof(Type) * vector->size();
//		}
//	};