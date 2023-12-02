#include "context_test.hpp"
#include "serializer/context.hpp"

#include <memory>

using namespace Primitives;

TEST_F(Serializer, Serial_SimpleContext)
{
	Field1 field1;
	Field2 field2;
	Field3 field3;

	Context context1("field1", field1);
	Context context2("field2", field2);
	Context context3("field3", field3);

	ASSERT_EQ(context1.GetSize(), sizeof(Field1));
	ASSERT_EQ(context2.GetSize(), sizeof(Field2));
	ASSERT_EQ(context3.GetSize(), sizeof(Field3));

	return;
}

TEST_F(Serializer, Serial_SimpleVectorContext)
{
	ComplexStorage1 complex1;
	ComplexStorage2 complex2;

	complex1.test = { 1, 2, 3, 4, 5 };
	complex2.test1 = { 1, 2, 3, 4, 5 };
	complex2.test2 = { 'a', 'b', 'c' };
	complex2.test3 = { 1.0f, 2.0f, 3.0f, 4.0f, 5.0f };

	Context context1("complex1", complex1.test);
	Context context2_1("complex2_1", complex2.test1);
	Context context2_2("complex2_2", complex2.test2);
	Context context2_3("complex2_3", complex2.test3);

	ASSERT_EQ(context1.GetSize(), complex1.test.size() * sizeof(decltype(complex1.test)::value_type));

	ASSERT_EQ(context2_1.GetSize(), complex2.test1.size() * sizeof(decltype(complex2.test1)::value_type));
	ASSERT_EQ(context2_2.GetSize(), complex2.test2.size() * sizeof(decltype(complex2.test2)::value_type));
	ASSERT_EQ(context2_3.GetSize(), complex2.test3.size() * sizeof(decltype(complex2.test3)::value_type));

	return;
}

TEST_F(Serializer, Serial_AllignedContext)
{
	AlignTest1 align1;
	AlignTest2 align2;
	AlignTest3 align3;
	AlignTest4 align4;
	AlignTest5 align5;
	AlignTest6 align6;
	AlignTest7 align7;
	AlignTest8 align8;
	AlignTest9 align9;

	Context context1("align1", std::forward<AlignTest1>(align1));
	Context context2("align2", std::forward<AlignTest2>(align2));
	Context context3("align3", std::forward<AlignTest3>(align3));
	Context context4("align4", std::forward<AlignTest4>(align4));
	Context context5("align5", std::forward<AlignTest5>(align5));
	Context context6("align6", std::forward<AlignTest6>(align6));
	Context context7("align7", std::forward<AlignTest7>(align7));
	Context context8("align8", std::forward<AlignTest8>(align8));
	Context context9("align9", std::forward<AlignTest9>(align9));

	return;
}