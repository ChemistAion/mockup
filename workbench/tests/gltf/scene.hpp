#pragma once

#include "gltf/gltf_pch.hpp"
#include "gltf/scene.hpp"

class Scene : public Template
{
protected:
	simdjson::dom::parser parser_;
};
