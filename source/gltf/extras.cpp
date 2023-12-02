#include "gltf_pch.hpp"

namespace Mockup::glTF
{
	Extras GetExtras(const simdjson::dom::element& element)
	{
		return GetValue(element);
	}
}
