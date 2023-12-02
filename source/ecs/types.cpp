#include "types.hpp"

namespace Mockup::Director::Detail
{
    void Internal::TypeNameExtract(std::string_view& name)
    {
        if (name.find(probe_) == std::string_view::npos)
        {
            const std::string_view probe_name = TypeName<TypeNameProbe>();

            const size_t prefix_size = probe_name.find(probe_);
            const size_t suffix_size = probe_name.length() - prefix_size - probe_.length();
            
            name.remove_prefix(prefix_size);
            name.remove_suffix(suffix_size);
        }
    }
}