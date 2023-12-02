#pragma once

#include "serializer/context.hpp"
#include "serializer/archive.hpp"

#include "extras/range.hpp"

#include <gtest/gtest.h>

using namespace Mockup;
using namespace Mockup::Serializer;

class Serializer : public ::testing::Test
{
public:
protected:
	Serializer()
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

	~Serializer()
	{
//		Windows::Foundation::Uninitialize();
	}

	void SetUp() override
	{
	}

	void TearDown() override
	{
	}
};

////////////////////////////////////////////////////////////////////////////////