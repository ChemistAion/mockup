#pragma once

namespace Mockup::Core
{
	namespace Detail
	{
		class RangeIterator
		{
		public:
			RangeIterator(std::size_t value)
			{
				value_ = value;
			}

			bool operator!=(RangeIterator const& rhs) const
			{
				return value_ != rhs.value_;
			}

			std::size_t const& operator*() const
			{
				return value_;
			}

			RangeIterator& operator++()
			{
				++value_;
				return *this;
			}

		private:
			std::size_t value_;
		};
	}

	class Range
	{
		std::size_t const from_;
		std::size_t const to_;
	public:
		Range(std::size_t from, std::size_t to)
			: from_(from)
			, to_(to)
		{
		}

		Range(std::size_t to)
			: from_(0)
			, to_(to)
		{
		}

		Detail::RangeIterator begin() const
		{
			return Detail::RangeIterator(from_);
		}

		Detail::RangeIterator end() const
		{
			return Detail::RangeIterator(to_);
		}
	};
}