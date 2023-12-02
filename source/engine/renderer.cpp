#include "engine_pch.hpp"

#include "renderer.hpp"
#include "buffer.hpp"
#include "texture.hpp"
#include "pipeline.hpp"
#include "swapchain.hpp"

namespace Mockup::Engine::Framework
{
	//	Renderer::Renderer(Adapter& adapter)
	Renderer::Renderer()
		: Device()
		, heaps_
		{
			{ this, cHeapDescriptor_GenericSize, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV },
			{ this, cHeapDescriptor_SamplerSize, D3D12_DESCRIPTOR_HEAP_TYPE_SAMPLER },
			{ this, cHeapDescriptor_RTVSize, D3D12_DESCRIPTOR_HEAP_TYPE_RTV },
			{ this, cHeapDescriptor_DSVSize, D3D12_DESCRIPTOR_HEAP_TYPE_DSV }
		}
		, commands_ { this, cEngine_BackBufferCount, 8u, GetGraphicsQueue()->GetDesc() }
		, upload_ { this, cHeapUpload_Size }
		, context_ { this }
		, frame_ { 0 }
	{
	}

	////////////////////////////////////////////////////////////////////////////////

	std::shared_ptr<Buffer> Renderer::CreateBuffer(const BufferDesc& desc, const BufferData* data)
	{
		std::shared_ptr<Buffer> buffer;

		CreateObject([&]() { buffer = std::make_shared<Buffer>(this, desc, data); });
		return buffer;
	}

	std::shared_ptr<Texture> Renderer::CreateTexture(const TextureDesc& desc, const TextureData* data)
	{
		std::shared_ptr<Texture> texture;

		CreateObject([&]() { texture = std::make_shared<Texture>(this, desc, data); });
		return texture;
	}

//	std::shared_ptr<Texture> Renderer::CreateTexture(const TextureDesc& desc, ID3D12Resource* resource, D3D12_RESOURCE_STATES state)
//	{
//		std::shared_ptr<Texture> texture;
//	
//		CreateObject([&]() { texture = std::make_shared<Texture>(this, desc, resource, state); });
//		return texture;
//	}

	std::shared_ptr<Shader> Renderer::CreateShader(const ShaderDesc& desc)
	{
		std::shared_ptr<Shader> shader;

		CreateObject([&]() { shader = std::make_shared<Shader>(this, desc);	});
		return shader;
	}

	std::shared_ptr<Pipeline> Renderer::CreatePipeline(const PipelineDesc& desc)
	{
		std::shared_ptr<Pipeline> pipeline;

		CreateObject([&]() { pipeline = std::make_shared<Pipeline>(this, desc);	});

		return pipeline;
	}

    std::shared_ptr<SwapChain> Renderer::CreateSwapChain(const SwapChainDesc& desc)
    {
		std::shared_ptr<SwapChain> swapchain;
		CreateObject([&]() { swapchain = std::make_shared<SwapChain>(this, desc); });
		return swapchain;
    }

    void Renderer::BeginFrame()
    {
		try
		{
			commands_.BeginFrame(frame_);
			context_.BeginFrame(frame_);
		}
		catch (const _com_error& error)
		{
			auto logger = Core::Logger::GetInstance();

			std::wstring error_message(error.ErrorMessage());
			logger->Critical("[Renderer::BeginFrame]: " + std::string(error_message.cbegin(), error_message.cend()));
		}
		catch (const std::runtime_error& error)
		{
			auto logger = Core::Logger::GetInstance();
			logger->Critical("[Renderer::BeginFrame]: " + std::string(error.what()));
		}
		catch (...)
		{
			auto logger = Core::Logger::GetInstance();
			logger->Critical("[Renderer::BeginFrame]: Unhandled exception");
		}
    }
}
