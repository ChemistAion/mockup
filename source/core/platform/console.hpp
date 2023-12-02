#pragma once

#include <stdio.h>

namespace Mockup::Core
{
	constexpr decltype(auto) cConsoleTitle_Name = _T("mockup::console");

	class Console final : public Singleton<Console>
	{
		friend Singleton<Console>;
		Console();
	};
}