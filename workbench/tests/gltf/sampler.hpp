#pragma once

#include "gltf/gltf_pch.hpp"
#include "gltf/sampler.hpp"

class Sampler: public Template
{
protected:
	simdjson::dom::parser parser_;
};

