#pragma once

#include "engine_pch.hpp"

#include "index.hpp"

namespace Mockup::Engine::Scene
{
	struct Scene
	{
		std::vector<Index> nodes_;
	};
}