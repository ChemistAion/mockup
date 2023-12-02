#pragma once

#include "sparse_set.hpp"

#include <vector>
#include <type_traits>

namespace Mockup::Director::Detail
{
	template<typename Key, typename Type, typename = std::void_t<>>
	class SparseMap final : public SparseSet<Key>
	{
		static_assert(std::is_move_constructible_v<Type> && std::is_move_assignable_v<Type>);
	
		std::vector<Type> values_;
	public:
		[[nodiscard]] const Type& Get(const Key key) const
		{
			return values_[SparseSet::Index(key)];
		}

		[[nodiscard]] Type& Get(const Key key)
		{
			return const_cast<Type&>(std::as_const(*this).Get(key));
		}

		[[nodiscard]] const Type* TryGet(const Key key) const
		{
			return SparseSet::Contains(key)
				? (values_.data() + SparseSet::Index(key))
				: nullptr;
		}

		[[nodiscard]] Type* TryGet(const Key key)
		{
			return const_cast<Type*>(std::as_const(*this).TryGet(key));
		}

		template<typename... Arguments>
		[[maybe_unused]] void Emplace(const Key key, Arguments&&... arguments)
		{
			SparseSet::Emplace(key);

			if constexpr (std::is_aggregate_v<Type>)
			{
				values_.push_back(Type { std::forward<Arguments>(arguments)... });
			}
			else
			{
				values_.emplace_back(std::forward<Arguments>(arguments)...);
			}
		}

		void Erase(const Key key)
		{
			auto element = std::move(values_.back());

			values_[SparseSet::Index(key)] = std::move(element);
			values_.pop_back();

			SparseSet::Erase(key);
		}

		template<typename Iterator>
		void Remove(Iterator first, Iterator last)
		{
			if (std::distance(first, last) == std::distance(begin(), end()))
			{
				this->Clear();
			}
			else
			{
				while (first != last)
				{
					this->Erase(*(first++));
				}
			}
		}

		void Clear()
		{
			SparseSet::Clear();
			values_.clear();
		}
	};

	////////////////////////////////////////////////////////////////////////////////

//	template<typename Key, typename Type>
//	class SparseMap<typename Key, Type, std::enable_if_t<std::is_empty_v<Type>>> : public SparseSet<EntityType>
//	{
//	public:
//		template<typename... Arguments>
//		void Emplace(const Key key, Arguments&&... arguments)
//		{
//			[[maybe_unused]] Type instance { std::forward<Arguments>(arguments)... };
//	
//			SparseSet::Emplace(key);
//		}
//	};
}