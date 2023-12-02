#pragma once

#include "pool.hpp"

#include <initializer_list>
#include <tuple>
#include <type_traits>

namespace Mockup::Director
{
	template<typename...>
	class View;

	////////////////////////////////////////////////////////////////////////////////

	template <typename Entity, typename... Component>
	class View<Entity, Component...>
	{
		const std::tuple<PoolType<Entity, Component>* ...> pools_;

		template <typename ComponentType>
		[[nodiscard]] constexpr PoolType<Entity, ComponentType>* GetPool() const
		{
			return std::get<PoolType<Entity, ComponentType>*>(pools_);
		}
	public:
		View(PoolType<Entity, Component>& ...component) noexcept
			: pools_ { &component... }
		{
		}

		[[nodiscard]] constexpr bool Empty() const noexcept
		{
			return (GetPool<Component>()->Empty() || ...);
		}

		template <typename ComponentType>
		[[nodiscard]] constexpr std::size_t Size() const noexcept
		{
			return GetPool<ComponentType>()->Size();
		}

		[[nodiscard]] constexpr bool Contains(const Entity entity) const
		{
			return (GetPool<Component>()->Contains(entity) && ...);
		}

		template<typename... ComponentType>
		[[nodiscard]] decltype(auto) Get(const Entity entity) const
		{
			static_assert(sizeof...(ComponentType) > 0);

			assert(Contains(entity));

			if constexpr (sizeof...(ComponentType) == 1)
			{
				return (GetPool<ComponentType>()->Get(entity), ...);
			}
			else
			{
				return std::tuple<decltype(Get<ComponentType>({}))...> { Get<ComponentType>(entity)...};
			}
		}

		template <typename Functor>
		void Each(Functor functor)
		{
			const std::initializer_list<const Detail::SparseSet<Entity>*> pool_list
			{
				GetPool<Component>()...
			};

			auto pool_less = [](const auto* lhs, const auto* rhs)
			{
				return lhs->Size() < rhs->Size();
			};
			
			for (const auto entity : *(std::min(pool_list, pool_less)))
			{
				if (Contains(entity))
				{
					functor(entity, GetPool<Component>()->Get(entity)...);
				}
				else
				{
					assert(false);
				}
			}
		}
	};

	////////////////////////////////////////////////////////////////////////////////

	template <typename Entity, typename Component>
	class View<Entity, Component>
	{
		PoolType<Entity, Component>* pool_;

		using ConstIterator = typename Detail::SparseSet<Entity>::ConstIterator;

		ConstIterator begin() const noexcept
		{
			return pool_->Detail::SparseSet<Entity>::begin();
		}

		ConstIterator end() const noexcept
		{
			return pool_->Detail::SparseSet<Entity>::end();
		}
	public:
		View(PoolType<Entity, Component>& component) noexcept
			: pool_ { &component }
		{
		}

		[[nodiscard]] constexpr bool Empty() const noexcept
		{
			return pool_->Empty();
		}

		template <typename ComponentType>
		[[nodiscard]] constexpr std::size_t Size() const noexcept
		{
			static_assert(std::is_same_v<ComponentType, Component>);
			return pool_->Size();
		}

		[[nodiscard]] constexpr bool Contains(const Entity entity) const
		{
			return pool_->Contains(entity);
		}

		template<typename ComponentType>
		[[nodiscard]] decltype(auto) Get(const Entity entity) const
		{
			static_assert(std::is_same_v<ComponentType, Component>);

			assert(Contains(entity));

			return pool_->Get(entity);
		}

		template <typename Functor>
		void Each(Functor functor)
		{
			for (const auto entity : *this)
			{
				functor(entity, pool_->Get(entity));
			}
		}
	};
}