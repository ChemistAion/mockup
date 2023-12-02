#pragma once

namespace Mockup::Core
{
    namespace Internal
    {
        class TypeNameProbe;
        constexpr std::string_view type_probe_("class Mockup::Core::Internal::TypeNameProbe");
    
        void TypeNameExtract(std::string_view& name) noexcept;
    }
    
    template <typename Type>
    constexpr auto TypeName() noexcept
    {
        std::string_view name(__FUNCSIG__);

        Internal::TypeNameExtract(name);
        return name;
    }
    
    ////////////////////////////////////////////////////////////////////////////////
    
    template <typename Type>
    class TypeInfo final
    {
    public:
        [[nodiscard]] static constexpr std::uint64_t Value() noexcept
        {
            constexpr std::uint64_t fnv1a_offset_ = 14695981039346656037ull;
            constexpr std::uint64_t fnv1a_prime_ = 1099511628211ull;
    
            auto hash = fnv1a_offset_;
    
            for (const std::uint64_t element : TypeName<Type>())
            {
                hash = (hash ^ element) * fnv1a_prime_;
            }
    
            return hash;
        };
    };
    
    ////////////////////////////////////////////////////////////////////////////////
    
    template <typename...>
    class TypeIndex final
    {
        inline static std::atomic_size_t identity_{};
    public:
        template <typename... Types>
        static constexpr std::size_t Value() noexcept
        {
            static_assert(sizeof...(Types) > 0);
    
            static const std::size_t result = identity_++;
            return result;
        }
    };
}

//  namespace Internal
//  {
//      template <typename Type, typename = std::void_t<>>
//      struct HasTypeIndex : std::false_type
//      {
//      };
//  
//      template <typename Type>
//      struct HasTypeIndex<Type, std::void_t<decltype(TypeIndex<Type>::Value())>> : std::true_type
//      {
//      };
//  }
//  
//  template<typename Type>
//  inline constexpr bool HasTypeIndex = Internal::HasTypeIndex<Type>::value;    