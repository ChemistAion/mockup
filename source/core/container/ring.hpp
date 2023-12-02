#pragma once

namespace Mockup::Core
{
	//TODO: concept/template...

	class Ring
	{
		const std::uint32_t total_ = 0;

		std::uint32_t head_ = 0;
		std::uint32_t size_ = 0;
	public:
		Ring(std::uint32_t total)
			: total_ { total }
		{
		}

		auto GetHead() const noexcept
		{
			return head_;
		}

		auto GetSize() const noexcept
		{
			return size_;
		}

		auto GetTail() const noexcept
		{
			return (head_ + size_) % total_;
		}

		////////////////////////////////////////////////////////////////////////////////

		//TODO: check likely/unlikely
		std::uint32_t Padding(std::uint32_t size) const noexcept
		{
			if (auto tail = GetTail(); (tail + size) > total_) [[unlikely]]
			{			
				return total_ - tail;
			}
			
			[[likely]] return 0;
		}

		//TODO: check likely/unlikely
		bool Allocate(std::uint32_t size, std::uint32_t* output)
		{
			if (size_ + size <= total_) [[likely]]
			{
				if (output != nullptr)
				{
					*output = GetTail();
				}
				
				size_ += size;
				return true;
			}

			assert(false);
			[[unlikely]] return false;		
		}

		bool Free(std::uint32_t size) noexcept
		{
			if (size_ >= size) [[likely]]
			{				
				head_ = (head_ + size) % total_;
				size_ -= size;

				return true;
			}

			assert(false);
			[[unlikely]] return false;
		}
	};
}