#pragma once

#include "gltf/gltf_pch.hpp"
#include "gltf/asset.hpp"

class Asset : public Template
{
protected:
	simdjson::dom::parser parser_;
};

