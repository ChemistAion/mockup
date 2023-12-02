#pragma once

namespace Primitives
{	
	template <typename Type>
	struct EmptyTestType
	{
	};

	template <typename Type>
	struct StaticTestType
	{
		static Type test;
	};
}