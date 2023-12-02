#include "parallel.hpp"

namespace Primitives
{
	static constexpr std::uint32_t data1_ = 0xa5a5a5a5;
	static constexpr std::uint32_t data2_ = 0x3c3c3c3c;
	static constexpr std::uint32_t data3_ = 0x99999999;
	static constexpr std::uint32_t data4_ = 0x66666666;

	std::uint32_t output1_;
	std::uint32_t output2_;
	std::uint32_t output3_;
	std::uint32_t output4_;

	void testfunc1()
	{
		output1_ = data1_ ^ data2_;
		output1_ ^= data3_;
		output1_ += data4_;
		output1_ ^= data3_;
	}

	void testfunc2()
	{
		++output2_;
	}

	void testfunc3()
	{
		--output3_;
	}

	void testfunc4()
	{
		output4_ = data3_ ^ data4_;
	}

	void testfuncarg1(void* fiber, std::uint32_t arg1)
	{
		fiber;

		output1_ = data1_ ^ data2_;
		output1_ ^= data3_;
		output1_ += data4_;
		output1_ ^= data3_;

		output1_ += arg1;
	}

	void testfuncarg2(void* fiber, std::uint32_t arg1, std::uint32_t arg2)
	{
		fiber;

		output2_ += arg1 + arg2;
	}

	void testfuncarg3(void* fiber, std::uint32_t arg1, std::uint32_t arg2, std::uint32_t arg3)
	{
		fiber;

 		output3_ += arg1 + arg2 + arg3;
	}

	void testfuncarg4(void* fiber, std::uint32_t arg1, std::uint32_t arg2, std::uint32_t arg3, std::uint32_t arg4)
	{
		fiber;

		output4_ = data3_ ^ data4_;
		output4_ += arg1 + arg2 + arg3 + arg4;
	}

	void testfuncspec1(void* fiber, int& arg1, const int arg2)
	{
		auto temp = arg1;

		arg1 = arg2;
		*(int*)fiber = temp;
	}
	
	int testfuncspec2(int& arg1, int arg2)
	{
		auto temp = arg1;
		arg1 = arg2;
		return temp + arg1;
	}

	int testfuncspec3(int& arg1, int& arg2)
	{
		auto temp = arg1;
		arg1 = arg2;
		arg2 = temp;

		return arg1 + arg2;
	}
}