#pragma once

#include "platform/prerequisites.hpp"
#include "extras/range.hpp"

#include "parallel/scheduler.hpp"
#include "parallel/future.hpp"
#include "parallel/task.hpp"

#include <benchmark/benchmark.h>

using namespace Mockup;
using namespace Mockup::Parallel;

class Parallel : public benchmark::Fixture
{
public:
	Scheduler* scheduler_;
protected:
	Parallel()
	{
#if defined(_DEBUG)  
		{
			auto flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

			flag |= _CRTDBG_ALLOC_MEM_DF;
			flag |= _CRTDBG_CHECK_ALWAYS_DF;
			flag |= _CRTDBG_LEAK_CHECK_DF;

			_CrtSetDbgFlag(flag);

			_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
			_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
		}
#endif
//		Windows::Foundation::Initialize(RO_INIT_MULTITHREADED);
	}

	~Parallel()
	{
//		Windows::Foundation::Uninitialize();
	}

	void SetUp(const ::benchmark::State&)
	{
		scheduler_ = new (std::nothrow) Scheduler;
	}

	void TearDown(const ::benchmark::State&)
	{
		delete (scheduler_);
	}
};

////////////////////////////////////////////////////////////////////////////////