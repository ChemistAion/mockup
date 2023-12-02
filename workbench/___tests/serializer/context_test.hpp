#include "serializer.hpp"

#include "serializer/size.hpp"
#include "serializer/context.hpp"

#include <memory>
#include <vector>

namespace Primitives
{
	struct Field1
	{
		int number1 = 1;
	};

	struct Field2
	{
		int number1 = 1;
		int number2 = 2;
	};

	struct Field3
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
	};

	struct Field4
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
	};

	struct Field5
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
	};

	struct Field6
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
	};

	struct Field7
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
	};

	struct Field8
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
		int number8 = 8;
	};

	struct Field9
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
		int number8 = 8;
		int number9 = 9;
	};

	struct Field10
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
		int number8 = 8;
		int number9 = 9;
		int number10 = 10;
	};

	struct Field11
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
		int number8 = 8;
		int number9 = 9;
		int number10 = 10;
		int number11 = 11;
	};

	struct Field12
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
		int number8 = 8;
		int number9 = 9;
		int number10 = 10;
		int number11 = 11;
		int number12 = 12;
	};

	struct Field13
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
		int number8 = 8;
		int number9 = 9;
		int number10 = 10;
		int number11 = 11;
		int number12 = 12;
		int number13 = 13;
	};

	struct Field14
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
		int number8 = 8;
		int number9 = 9;
		int number10 = 10;
		int number11 = 11;
		int number12 = 12;
		int number13 = 13;
		int number14 = 14;
	};

	struct Field15
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
		int number8 = 8;
		int number9 = 9;
		int number10 = 10;
		int number11 = 11;
		int number12 = 12;
		int number13 = 13;
		int number14 = 14;
		int number15 = 15;
	};

	struct Field16
	{
		int number1 = 1;
		int number2 = 2;
		int number3 = 3;
		int number4 = 4;
		int number5 = 5;
		int number6 = 6;
		int number7 = 7;
		int number8 = 8;
		int number9 = 9;
		int number10 = 10;
		int number11 = 11;
		int number12 = 12;
		int number13 = 13;
		int number14 = 14;
		int number15 = 15;
		int number16 = 16;
	};

	////////////////////////////////////////////////////////////////////////////////

	struct Embedded
	{
		int number = 42;

		struct Internal
		{
			int embedded = 11;
		};

		Internal internal;
	};

	////////////////////////////////////////////////////////////////////////////////
	
	struct Pointer
	{
		int number = 42;

		Field1 field1;
		Field2 field2;
		Field3 field3;

		Field1* ptr1 = &field1;
		Field2* ptr2 = &field2;
		Field3* ptr3 = &field3;
	};

	struct PointerSelf
	{
		int number = 42;
		PointerSelf* ptrs = nullptr;
	};

	////////////////////////////////////////////////////////////////////////////////

	struct ComplexStorage1
	{
		std::vector<int> test;
	};


	struct ComplexStorage2
	{
		std::vector<int> test1;
		std::vector<char> test2;
		std::vector<float> test3;
	};

	struct ComplexStorage3
	{
		std::vector<std::vector<int>> test1;
		std::vector<std::vector<char>> test2;
	};

	struct ComplexStorage4
	{
		std::vector<ComplexStorage1> test1;
		std::vector<ComplexStorage2> test2;
	};

	struct ComplexStorage5
	{
		std::vector<ComplexStorage3> test1;
		std::unique_ptr<ComplexStorage1> test2;
		std::unique_ptr<ComplexStorage2> test3;
	};

	////////////////////////////////////////////////////////////////////////////////

	struct AlignTest1
	{
		std::uint8_t number = 42;
		void* ptrs = nullptr;
	};

	struct AlignTest2
	{
		int number = 42;
		void* ptrs = nullptr;
	};

	struct AlignTest3
	{
		int number = 42;
		AlignTest1* ptrs = nullptr;
	};

	struct AlignTest4
	{
		std::uint8_t number1 = 1;
		std::uint8_t number2 = 2;
		std::uint8_t number3 = 3;
		AlignTest1* ptrs = nullptr;
	};

	struct AlignTest5
	{
		std::uint8_t number1 = 1;
		std::uint8_t number2 = 2;
		std::uint8_t number3 = 3;
	};

	struct AlignTest6
	{
		AlignTest1* ptrs = nullptr;

		std::uint8_t number1 = 1;
		std::uint8_t number2 = 2;
		std::uint8_t number3 = 3;
	};

	struct AlignTest7
	{
		AlignTest1* ptrs1 = nullptr;

		std::uint8_t number1 = 1;
		std::uint8_t number2 = 2;
		std::uint8_t number3 = 3;

		AlignTest1* ptrs2 = nullptr;
	};

	struct AlignTest8
	{
		void* ptrs1 = nullptr;
		void* ptrs2 = nullptr;
	};

	struct AlignTest9
	{
		AlignTest1* ptrs1 = nullptr;
	
		alignas(16) std::uint8_t number1 = 1;
		alignas(16) std::uint8_t number2 = 2;
		alignas(16) std::uint8_t number3 = 3;
	
		AlignTest1* ptrs2 = nullptr;
	};
}