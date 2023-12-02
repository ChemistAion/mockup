#pragma once

#include "gltf/gltf_pch.hpp"
#include "gltf/mesh.hpp"

class Mesh : public Template
{
protected:
	simdjson::dom::parser parser_;
};

