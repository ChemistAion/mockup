#pragma once

#include "engine_pch.hpp"

#include "index.hpp"

namespace Mockup::Engine::Scene
{
	struct Camera
	{
		Index node_;
		XMMATRIX projection_;
	};
}