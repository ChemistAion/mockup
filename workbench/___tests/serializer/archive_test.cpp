#include "archive_test.hpp"
#include "serializer/archive.hpp"

//#include <fstream>

using namespace Primitives;

TEST_F(Serializer, Serial_SimpleArchive)
{
	Field1 field1;
	Field2 field2;
	Field3 field3;

	const char name[] = "Serial_SimpleArchive.bin";

	////////////////////////////////////////////////////////////////////////////////

	{
		Flags flags = Archive::Flag::Empty;
		flags |= Archive::Flag::Valid;
		flags |= Archive::Flag::Debug;

		Archive archive("test", flags);

		archive.Serialize("field1", flags, field1);
		archive.Serialize("field2", flags, field2);
		archive.Serialize("field3", flags, field3);

		std::ofstream output(name, std::ios::binary | std::ios::out);

		archive.ToStream(output);
		output.close();
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::ifstream input(name, std::ios::binary | std::ios::in);

		Archive archive("test", input);

		input.close();
	}

	////////////////////////////////////////////////////////////////////////////////

	return;
}

TEST_F(Serializer, Serial_SimpleVectorArchive)
{
	ComplexStorage1 complex1;
	ComplexStorage2 complex2;

	complex1.test = { 1, 2, 3, 4, 5 };
	complex2.test1 = { 1, 2, 3, 4, 5 };
	complex2.test2 = { 'a', 'b', 'c' };
	complex2.test3 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	const char name[] = "Serial_SimpleVectorArchive.bin";

	////////////////////////////////////////////////////////////////////////////////

	{
		Flags flags = Archive::Flag::Empty;
		flags |= Archive::Flag::Valid;
		flags |= Archive::Flag::Debug;

		Archive archive("test", flags);

		archive.Serialize("complex1", flags, complex1.test);
		archive.Serialize("complex2_1", flags, complex2.test1);
		archive.Serialize("complex2_2", flags, complex2.test2);
		archive.Serialize("complex2_3", flags, complex2.test3);

		std::ofstream output(name, std::ios::binary | std::ios::out);

		archive.ToStream(output);
		output.close();
	}

	////////////////////////////////////////////////////////////////////////////////

	std::ifstream input(name, std::ios::binary | std::ios::in);

	Archive archive("test", input);

	input.close();

	////////////////////////////////////////////////////////////////////////////////

	return;
}