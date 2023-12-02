#pragma once

#include "indexer.hpp"

#include <algorithm>
#include <cassert>
#include <vector>

namespace Mockup::Director::Detail
{
    template <typename Key>
    class SparseSet
    {
        std::vector<Key> packed_;
        std::vector<std::size_t> sparse_;
    public:
        using Iterator = typename std::vector<Key>::iterator;
        using ConstIterator = typename std::vector<Key>::const_iterator;

        Iterator begin() noexcept
        {
            return packed_.begin();
        }

        Iterator end() noexcept
        {
            return packed_.end();
        }

        ConstIterator begin() const noexcept
        {
            return packed_.begin();
        }

        ConstIterator end() const noexcept
        {
            return packed_.end();
        }

        ConstIterator cbegin() const noexcept
        {
            return packed_.cbegin();
        }

        ConstIterator cend() const noexcept
        {
            return packed_.cend();
        }

        ////////////////////////////////////////////////////////////////////////////////

        SparseSet() = default;

        SparseSet(const SparseSet&) = default;
        SparseSet& operator=(const SparseSet&) = default;

        SparseSet(SparseSet&&) noexcept = default;
        SparseSet& operator=(SparseSet&&) noexcept = default;

        virtual ~SparseSet() = default;

        ////////////////////////////////////////////////////////////////////////////////

        [[nodiscard]] constexpr std::size_t Size() const noexcept
        {
            return packed_.size();
        }

        constexpr void Reserve(const std::size_t capacity)
        {
            packed_.reserve(capacity);
        }

        [[nodiscard]] constexpr std::size_t Capacity() const noexcept
        {
            return packed_.capacity();
        }

        [[nodiscard]] constexpr bool Empty() const noexcept
        {
            return packed_.empty();
        }

//      [[nodiscard]] const Type* Data() const noexcept
//      {
//          return packed_.data();
//      }

        constexpr void Clear() noexcept
        {
            packed_.clear();
        }

        ////////////////////////////////////////////////////////////////////////////////

        [[nodiscard]] constexpr std::size_t Index(const Key key) const
        {
            assert(Contains(key));
            return sparse_[Indexer<Key>(key)];
        }

        [[nodiscard]] constexpr bool Contains(const Key key) const noexcept
        {
            const auto index = Indexer<Key>(key);
            
            return
                index < sparse_.size() &&
                sparse_[index] < packed_.size() &&
                packed_[sparse_[index]] == key;
        }

        [[nodiscard]] ConstIterator Find(const Key key) const noexcept
        {
            return Contains(key)
                ? begin() + sparse_[indexer_(key)]
                : end();
        }

        void Emplace(const Key key)
        {
            assert(!Contains(key));

            const auto index = Indexer<Key>(key);

            if (index >= sparse_.size())
            {
                //TODO: check max size vs number of types
                sparse_.resize(std::max(sparse_.size() * 2u, index + 1));
            }

            packed_.push_back(key);
            sparse_[index] = packed_.size() - 1u;
        }

        void Erase(const Key key)
        {
            assert(Contains(key));

            const auto index = Indexer<Key>(key);
            const auto packed_index = sparse_[index];

            if (packed_index != (packed_.size() - 1))
            {
                auto element = std::move(packed_.back());
                packed_[packed_index] = std::move(element);

                sparse_[Indexer<Key>(packed_[packed_index])] = packed_index;
            }

            packed_.pop_back();
        }
    };
}