#pragma once

#include "gltf/gltf_pch.hpp"
#include "gltf/material.hpp"

class Material : public Template
{
protected:
	simdjson::dom::parser parser_;
};

