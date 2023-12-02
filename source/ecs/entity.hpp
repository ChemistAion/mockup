#pragma once

#include "indexer.hpp"

#include <cstdint>
#include <cstddef>
#include <limits>
#include <stdexcept>
#include <tuple>
#include <type_traits>
#include <utility>

namespace Mockup::Director
{
    namespace EntityTraits
    {
        using EntityType = std::uint32_t;
        using VersionType = std::uint32_t;
        
        static constexpr EntityType EntityMask = 0xfffff;
        static constexpr EntityType VersionMask = 0xfff;
        static constexpr std::size_t MaskShift = 20u;
    };

    ////////////////////////////////////////////////////////////////////////////////

    using namespace EntityTraits;

    template <>
    constexpr std::size_t Detail::Indexer<EntityType>(const EntityType entity) noexcept
    {
        return std::size_t(entity & EntityMask);
    };

    ////////////////////////////////////////////////////////////////////////////////

    struct EntityInvalidType
    {
        [[nodiscard]] constexpr operator EntityType() const noexcept
        {
            return EntityType{ EntityMask };
        }

        [[nodiscard]] constexpr bool operator==(EntityInvalidType) const noexcept
        {
            return true;
        }

        [[nodiscard]] constexpr bool operator!=(EntityInvalidType) const noexcept
        {
            return false;
        }

        [[nodiscard]] constexpr bool operator==(const EntityType entity) const noexcept
        {
            return (entity & EntityMask) == static_cast<EntityType>(*this);
        }

        [[nodiscard]] constexpr bool operator!=(const EntityType entity) const noexcept
        {
            return !(entity == *this);
        }
    };

    ////////////////////////////////////////////////////////////////////////////////

    inline constexpr EntityInvalidType EntityInvalid
    {
    };

    [[nodiscard]] constexpr bool operator==(const EntityType entity, EntityInvalidType invalid) noexcept
    {
        return invalid.operator==(entity);
    }

    [[nodiscard]] constexpr bool operator!=(const EntityType entity, EntityInvalidType invalid) noexcept
    {
        return !(invalid == entity);
    }
}