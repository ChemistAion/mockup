#pragma once

#include "gltf/gltf_pch.hpp"
#include "gltf/accessor.hpp"

class Accessor : public Template
{
protected:
	simdjson::dom::parser parser_;
};
