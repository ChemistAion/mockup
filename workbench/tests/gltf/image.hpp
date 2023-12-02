#pragma once

#include "gltf/gltf_pch.hpp"
#include "gltf/image.hpp"

class Image : public Template
{
protected:
	simdjson::dom::parser parser_;
};

