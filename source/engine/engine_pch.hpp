#pragma once

#include "..\core\core_pch.hpp"

namespace Mockup::Engine
{
	constexpr bool cEngineMode_Experimental = true;
	constexpr bool cEngineMode_Debug = true;
	constexpr bool cEngineMode_PIX = false;
	constexpr bool cEngineMode_Aftermatch = false;

	constexpr UINT cEngine_BackBufferCount = 3;

	typedef UINT64 Frame;
}

#include <d3d12.h>
	
#include <dxgitype.h>
#include <dxgi1_4.h>
#include <dxgidebug.h>

#include <d3d12shader.h>
	
#include "xcompiler/include/dxc/dxcapi.h"
#include "xheaders/include/directx/d3dx12.h"
	
#include <directxmath.h>
using namespace DirectX;

//#include <pix.h>
//#include "GFSDK_Aftermath.h"

////////////////////////////////////////////////////////////////////////////////

constexpr D3D12_RESOURCE_STATES D3D12_RESOURCE_STATE_INVALID = (D3D12_RESOURCE_STATES)-1;
typedef void* D3D12_CPU_VIRTUAL_ADDRESS;

////////////////////////////////////////////////////////////////////////////////

#include "exception.hpp"
#include "format.hpp"

#include "object.hpp"
#include "resource.hpp"
#include "draw.hpp"

#include "heap_descriptor.hpp"
#include "heap_upload.hpp"
#include "pool_dynamic.hpp"
