#pragma once

#include "engine_pch.hpp"

namespace Mockup::Engine::Scene
{
	struct Primitives
	{
		XMVECTOR center_;
		XMVECTOR radius_;
	};
	
	struct Mesh
	{
		std::vector<Primitives> primitives_;
	};
}