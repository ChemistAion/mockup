#pragma once

#include "engine_pch.hpp"

#include "index.hpp"

namespace Mockup::Engine::Scene
{
	struct Skin
	{
		struct Joint
		{
			Index node_;
			XMMATRIX ibm_ = XMMatrixIdentity();
		};

		std::vector<XMMATRIX> bones_;
		std::vector<Joint> joints_;
		Index node_;
	};
}