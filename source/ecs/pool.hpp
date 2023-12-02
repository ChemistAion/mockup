#pragma once

#include "indexer.hpp"
#include "sparse_set.hpp"
#include "sparse_map.hpp"

#include <memory>

namespace Mockup::Director
{
    namespace Detail
    {
        template<typename Key, typename Type, typename = std::void_t<>>
        struct Pool
        {
            using PoolType = SparseMap<Key, Type>;
        };

        template<typename Key, typename Type>
        struct Pool<Key, const Type>
        {
            using PoolType = std::add_const_t<typename Pool<Key, std::remove_const_t<Type>>::PoolType>;
        };
    }

    template<typename Key, typename Type>
    using PoolType = typename Detail::Pool<Key, Type>::PoolType;
}