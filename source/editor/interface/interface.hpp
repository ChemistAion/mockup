#pragma once

#include "engine/renderer.hpp"
#include "engine/swapchain.hpp"

#include "imgui/imgui.h"

namespace Mockup::Editor
{
	class Interface final
	{
		std::shared_ptr<Core::Window> window_;
		std::shared_ptr<Engine::Framework::Renderer> renderer_;
		std::shared_ptr<Engine::Framework::Pipeline> pipeline_;

		std::shared_ptr<Engine::Framework::Texture> fonts_;
		Engine::Framework::TextureView fonts_srv_;

		const DXGI_FORMAT buffer_color_format_ = DXGI_FORMAT_UNKNOWN;
		const DXGI_FORMAT buffer_depth_format_ = DXGI_FORMAT_UNKNOWN;

		void CreateInternalResources();
	public:
		Interface
		(
			std::shared_ptr<Core::Window>& window,
			std::shared_ptr<Engine::Framework::Renderer>& render,
			DXGI_FORMAT buffer_color_format,
			DXGI_FORMAT buffer_depth_format
		);

		Interface(const Interface&) = delete;
		Interface(Interface&&) = delete;
		Interface& operator=(const Interface&) = delete;
		Interface& operator=(Interface&&) = delete;

		~Interface();
		
		////////////////////////////////////////////////////////////////////////////////
		
		void BeginFrame(std::shared_ptr<Engine::Framework::SwapChain>& swapchain);
		void RenderFrame();
		void EndFrame(std::shared_ptr<Engine::Framework::SwapChain>& swapchain);
		
		//LRESULT Pump(HWND handle, UINT message, WPARAM wParam, LPARAM lParam);
	};
}