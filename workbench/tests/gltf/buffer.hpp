#pragma once

#include "gltf/gltf_pch.hpp"
#include "gltf/buffer.hpp"
#include "gltf/buffer_view.hpp"

class Buffer : public Template
{
protected:
	simdjson::dom::parser parser_;
};

class BufferView : public Template
{
protected:
	simdjson::dom::parser parser_;
};
