#pragma once

#include "fence.hpp"
#include "device.hpp"
#include "buffer.hpp"
#include "texture.hpp"
#include "pipeline.hpp"
#include "commands.hpp"
#include "swapchain.hpp"

namespace Mockup::Engine::Framework
{
	class Pipeline;
	class SwapChain;
	struct SwapChainDesc;
	struct PipelineLayoutDesc;

	class Renderer final : public Device
	{
		Commands commands_;

		HeapDescriptor heaps_[D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES];
		HeapUpload upload_;
		
		Context context_;	

		Frame frame_;
	public:
		//TODO: explicit Renderer(Adapter& adapter);
		Renderer();

		Renderer(const Renderer&) = delete;
		Renderer& operator=(const Renderer&) = delete;

		Renderer(Renderer&&) = delete;
		Renderer& operator=(Renderer&&) = delete;

		////////////////////////////////////////////////////////////////////////////////

		//TODO: change to concept with args...
		//template <typename Object, typename ObjectDesc, typename ObjectCtor>
		//void CreateObject(const char* name, const ObjectDesc& desc, std::shared_ptr<Object>& object, ObjectCtor construct)
		template <typename Construct>
		void CreateObject(Construct construct)
		{
			try
			{
				construct();
			}
			catch (const std::runtime_error& error)
			{
				auto logger = Core::Logger::GetInstance();
				logger->Critical("[Renderer::CreateObject]: " + std::string(error.what()));
			}
		}

		std::shared_ptr<Buffer> CreateBuffer(const BufferDesc& desc, const BufferData* data);

		std::shared_ptr<Texture> CreateTexture(const TextureDesc& desc, const TextureData* data);
		//std::shared_ptr<Texture> CreateTexture(const TextureDesc& desc, ID3D12Resource* resource, D3D12_RESOURCE_STATES state);

		std::shared_ptr<Shader> CreateShader(const ShaderDesc& desc);
		std::shared_ptr<Pipeline> CreatePipeline(const PipelineDesc& desc);
		std::shared_ptr<SwapChain> CreateSwapChain(const SwapChainDesc& desc);

		////////////////////////////////////////////////////////////////////////////////

		Context& GetContext()
		{
			return context_;
		}

		Commands& GetCommands()
		{
			return commands_;
		}

		HeapUpload* GetHeapUpload()
		{
			return &upload_;
		}

		////////////////////////////////////////////////////////////////////////////////

		HeapDescriptor::Element AllocateDescriptor(D3D12_DESCRIPTOR_HEAP_TYPE heap_type, std::uint32_t count)
		{
			assert(heap_type >= D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV && heap_type < D3D12_DESCRIPTOR_HEAP_TYPE_NUM_TYPES);
			return heaps_[heap_type].Allocate(count);
		}

		void BeginFrame();

		void EndFrame()
		{
			++frame_;
		}

		Frame GetFrame() const noexcept
		{
			return frame_;
		}
	};
}
