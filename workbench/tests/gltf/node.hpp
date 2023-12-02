#pragma once

#include "gltf/gltf_pch.hpp"
#include "gltf/node.hpp"

class Node : public Template
{
protected:
	simdjson::dom::parser parser_;
};
