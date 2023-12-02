#pragma once

#include <map>
#include <memory>
#include <vector>

namespace Mockup::Serializer
{
	struct Storage
	{
		using StorageType = std::vector<std::uint8_t>;

		StorageType storage_;
		std::size_t offset_ = 0;
	
		std::uint8_t* GetAddres(std::size_t const offset)
		{
			return (&storage_[0]) + offset;
		}
	
		std::uint8_t* BaseAddres()
		{
			return &storage_[0];
		}
	
		template <typename Type>
		void Write(std::size_t const position, Type const& value)
		{
			auto size = sizeof(value);

			if (storage_.size() >= position + size)
			{
				std::memcpy(&storage_[position], &value, size);
			}
		}
	
		std::size_t Write(void const* pointer, std::size_t const size, std::size_t alignment = 0)
		{
			auto aligned_size = size;
	
			if (alignment != 0 && alignment != 1 && storage_.size() != 0)
			{
				auto unaligned_ptr = static_cast<void*>(GetAddres(offset_));
				auto space = std::numeric_limits<std::size_t>::max();
				auto const aligned_ptr = std::align(alignment, size, unaligned_ptr, space);
				auto const new_offset = static_cast<std::size_t>(aligned_ptr ? static_cast<uint8_t*>(aligned_ptr) - BaseAddres() : 0);
				auto const adjustment = new_offset - offset_;
	
				offset_ += adjustment;
				aligned_size += adjustment;
			}
	
			auto const space_left = static_cast<int64_t>(storage_.size()) - static_cast<int64_t>(offset_);
			if (space_left < static_cast<int64_t>(aligned_size))
			{
				auto const missing = static_cast<std::size_t>(static_cast<int64_t>(aligned_size) - space_left);
				storage_.resize(storage_.size() + missing);
			}
	
			auto const start = offset_;
	
			std::memcpy(GetAddres(offset_), pointer, size);
			offset_ += size;
	
			return start;
		}
	};
}