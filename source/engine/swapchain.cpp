#include "engine_pch.hpp"

#include "swapchain.hpp"
#include "renderer.hpp"
#include "context.hpp"

namespace Mockup::Engine::Framework
{
	void SwapChain::CreateSwapChain(ID3D12CommandQueue* command_queue)
	{
		assert(command_queue != nullptr);
		assert(window_);

		if (width_ == 0 || height_ == 0)
		{
			width_ = window_->GetClientWidth();
			height_ = window_->GetClientHeight();
		}

		DXGI_SWAP_CHAIN_DESC1 desc = {};

		desc.Width = (UINT)width_;
		desc.Height = (UINT)height_;

		assert(format_ != DXGI_FORMAT_UNKNOWN);

		//TODO: color/gamma scheme...
		switch (format_)
		{
		case DXGI_FORMAT_R8G8B8A8_UNORM_SRGB:
			desc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
			break;
		case DXGI_FORMAT_B8G8R8A8_UNORM_SRGB:
			desc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
			break;
		default:
			desc.Format = format_;
		}

		desc.Stereo = FALSE;

		//TODO: constexpr desc.SampleDesc
		desc.SampleDesc.Count = 1;
		desc.SampleDesc.Quality = 0;
		desc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		desc.BufferCount = cEngine_BackBufferCount;
		desc.Scaling = DXGI_SCALING_STRETCH; //DXGI_SCALING_NONE
		desc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL; //DXGI_SWAP_EFFECT_FLIP_DISCARD;
		desc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		desc.Flags = 0; //DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH; //DXGI_SWAP_CHAIN_FLAG_FRAME_LATENCY_WAITABLE_OBJECT;

		////////////////////////////////////////////////////////////////////////////////

		ComPtr<IDXGISwapChain1> preliminary;
		ComPtr<IDXGIFactory2> factory;
			
		auto result = CreateDXGIFactory1(IID_PPV_ARGS(factory.ReleaseAndGetAddressOf()));
		ThrowIfFailed(result, "SwapChain: CreateDXGIFactory failed");
			
		result = factory->CreateSwapChainForHwnd
		(
			command_queue,
			window_->GetHandle(),
			&desc,
			nullptr,
			nullptr,
			preliminary.ReleaseAndGetAddressOf()
		);
		
		ThrowIfFailed(result, "SwapChain: Create IDXGISwapChain1 failed");

		result = factory->MakeWindowAssociation(window_->GetHandle(), DXGI_MWA_NO_ALT_ENTER);
		ThrowIfFailed(result, "[SwapChain::CreateSwapChain] IDXGIFactory::MakeWindowAssociation failed");
		
		result = preliminary.As(&swapchain_);
		ThrowIfFailed(result, "SwapChain: Upgrade from IDXGISwapChain1 to IDXGISwapChain3 failed");

		////////////////////////////////////////////////////////////////////////////////

		D3D12_DESCRIPTOR_HEAP_DESC heap_desc;
		heap_desc.Type = D3D12_DESCRIPTOR_HEAP_TYPE_RTV;
		heap_desc.NumDescriptors = cEngine_BackBufferCount;
		heap_desc.Flags = D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
		heap_desc.NodeMask = GetNode();

		result = GetDevice()->CreateDescriptorHeap(&heap_desc, IID_PPV_ARGS(heap_.ReleaseAndGetAddressOf()));
		ThrowIfFailed(result, "[SwapChain::CreateSwapChain] CreateDescriptorHeap failed");
	}

	void SwapChain::InitializeSwapChain()
	{
		assert(heap_);

		auto device = GetDevice();

		const auto size = device->GetDescriptorHandleIncrementSize(D3D12_DESCRIPTOR_HEAP_TYPE_RTV);

		for (std::uint32_t index = 0; index < cEngine_BackBufferCount; ++index)
		{
			ComPtr<ID3D12Resource> resource;

			auto& view = bb_view_[index];

			view = heap_->GetCPUDescriptorHandleForHeapStart();
			view.ptr += (SIZE_T)(size * index);

			auto result = swapchain_->GetBuffer(index, IID_PPV_ARGS(resource.ReleaseAndGetAddressOf()));
			ThrowIfFailed(result, "[SwapChain::InitializeSwapChain] GetBuffer failed");

			D3D12_RESOURCE_DESC desc = resource->GetDesc();

			D3D12_RENDER_TARGET_VIEW_DESC rtv_desc = {};
			rtv_desc.Format = format_;
			rtv_desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
			rtv_desc.Texture2D.MipSlice = 0;
			rtv_desc.Texture2D.PlaneSlice = 0;

			device->CreateRenderTargetView(resource.Get(), &rtv_desc, view);
			//TODO: SetName
		}
	}

	SwapChain::SwapChain
	(
		Renderer* renderer,
		const SwapChainDesc& desc
	)
		: Object(renderer, desc)
		, window_{ desc.window_ }
		, fence_{ renderer, {} }
	{
		auto logger = Core::Logger::GetInstance();
		logger->Info("Creating SwapChain: " + GetName());

		CreateSwapChain(GetRenderer()->GetGraphicsQueue());
		InitializeSwapChain();

		//TODO: viewports!!!
	}

	void SwapChain::Present()
	{
		auto result = swapchain_->Present(0, 0);
		ThrowIfFailed(result, "SwapChain::Present failed");

		fence_.Signal(GetRenderer()->GetGraphicsQueue(), GetRenderer()->GetFrame());
	}

	void SwapChain::Wait(Frame frame)
	{
		while (false == fence_.WaitCPU(cEngine_BackBufferCount - 1))
		{
			std::this_thread::yield();
		}
	}
}