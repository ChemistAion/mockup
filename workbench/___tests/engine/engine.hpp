#pragma once

//	#include "engine/hardware.hpp"
//	#include "engine/context.hpp"
//	#include "engine/allocator.hpp"

//	#include "logger/logger.hpp"

#include <gtest/gtest.h>

//	using namespace Mockup;
//	using namespace Mockup::Engine;

//	class Bootstrap
//	{
//		std::shared_ptr<Context> context_;
//	public:
//		Bootstrap()
//		{
//			auto& logger = Logger::Instance();
//			logger.RegisterSink(std::make_unique<SinkMSVC>());
//	
//			logger.Info("Bootstrap");
//	
//			auto gfx_hardware = std::make_shared<Hardware>();
//			auto adapters = Hardware::EnumerateAdapters(gfx_hardware);
//	
//			context_ = std::make_shared<Context>(adapters.front());
//		}
//	
//		static Bootstrap& Instance() noexcept
//		{
//			static Bootstrap instance_;
//			return instance_;
//		}
//	
//		auto GetContext()
//		{
//			return context_;
//		}
//	};

//	class Engine : public ::testing::Test
//	{
//	protected:
//		std::shared_ptr<Context> context_;
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		Engine()
//		{
//	#if defined(_DEBUG)  
//			{
//				auto flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);
//	
//				flag |= _CRTDBG_ALLOC_MEM_DF;
//				flag |= _CRTDBG_CHECK_ALWAYS_DF;
//				flag |= _CRTDBG_LEAK_CHECK_DF;
//	
//				_CrtSetDbgFlag(flag);
//	
//				_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
//				_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
//				_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
//			}
//	#endif
//			auto& bootstrap = Bootstrap::Instance();
//	
//			context_ = bootstrap.GetContext();
//		}
//	
//		~Engine()
//		{
//		}
//	
//		void SetUp() override
//		{
//		}
//	
//		void TearDown() override
//		{
//		}
//	};

