#pragma once

#include <type_traits>	

namespace Mockup::Director::Detail
{
    template <typename Type, typename = std::void_t<>>
    constexpr std::size_t Indexer(const Type) noexcept
    {
        static_assert(false);
    }
}