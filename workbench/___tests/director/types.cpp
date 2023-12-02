#include "director.hpp"

#include "types.hpp"

TEST_F(Director, TypeInfo_Basics)
{
	using namespace Detail;

	ASSERT_NE((TypeInfo<int>::Value()), (TypeInfo<const int>::Value()));
	ASSERT_NE((TypeInfo<int>::Value()), (TypeInfo<int&&>::Value()));
	ASSERT_NE((TypeInfo<int&>::Value()), (TypeInfo<const int&>::Value()));
	ASSERT_NE((TypeInfo<int>::Value()), (TypeInfo<char>::Value()));
	ASSERT_EQ((TypeInfo<int>::Value()), (TypeInfo<int>::Value()));

	ASSERT_NE((TypeInfo<int>::Value()), (TypeInfo<const int>::Value()));
	ASSERT_NE((TypeInfo<int>::Value()), (TypeInfo<int&&>::Value()));
	ASSERT_NE((TypeInfo<int&>::Value()), (TypeInfo<const int&>::Value()));
	ASSERT_NE((TypeInfo<int>::Value()), (TypeInfo<char>::Value()));
	ASSERT_EQ((TypeInfo<int>::Value()), (TypeInfo<int>::Value()));
}

TEST_F(Director, TypeInfo_Collision)
{
	using namespace Detail;

	std::set<std::uint64_t> hash;

	////////////////////////////////////////////////////////////////////////////////

	ASSERT_TRUE(hash.insert(TypeInfo<void>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const void>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<void*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const void*>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<void>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const void>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<void*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const void*>::Value()).second);

	////////////////////////////////////////////////////////////////////////////////

	ASSERT_TRUE(hash.insert(TypeInfo<int>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const int>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<int&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const int&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<int*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const int*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<int&&>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<std::int32_t>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const std::int32_t>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<std::int32_t&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const std::int32_t&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<std::int32_t*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const std::int32_t*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<std::int32_t&&>::Value()).second);

	ASSERT_TRUE(hash.insert(TypeInfo<std::uint32_t>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const std::uint32_t>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<std::uint32_t&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const std::uint32_t&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<std::uint32_t*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const std::uint32_t*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<std::uint32_t&&>::Value()).second);

	using TestType = int;

	ASSERT_FALSE(hash.insert(TypeInfo<TestType>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const TestType>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<TestType&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const TestType&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<TestType*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const TestType*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<TestType&&>::Value()).second);

	////////////////////////////////////////////////////////////////////////////////

	ASSERT_TRUE(hash.insert(TypeInfo<char>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const char>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<char&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const char&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<char*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const char*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<char&&>::Value()).second);

	ASSERT_TRUE(hash.insert(TypeInfo<long>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const long>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<long&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const long&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<long*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const long*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<long&&>::Value()).second);

	ASSERT_TRUE(hash.insert(TypeInfo<float>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const float>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<float&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const float&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<float*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const float*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<float&&>::Value()).second);

	ASSERT_TRUE(hash.insert(TypeInfo<double>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const double>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<double&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const double&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<double*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const double*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<double&&>::Value()).second);

	////////////////////////////////////////////////////////////////////////////////

	ASSERT_FALSE(hash.insert(TypeInfo<int>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const int>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<int&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const int&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<int*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const int*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<int&&>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<char>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const char>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<char&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const char&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<char*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const char*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<char&&>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<long>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const long>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<long&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const long&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<long*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const long*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<long&&>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<float>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const float>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<float&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const float&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<float*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const float*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<float&&>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<double>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const double>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<double&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const double&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<double*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const double*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<double&&>::Value()).second);
}

TEST_F(Director, TypeInfo_EmptyTypes)
{
	using namespace Detail;

	std::set<std::uint64_t> hash;

	////////////////////////////////////////////////////////////////////////////////

	struct EmptyType
	{
	};

	struct OtherEmptyType
	{
	};

	struct ChildTest : EmptyType
	{
	};

	ASSERT_TRUE(hash.insert(TypeInfo<EmptyType>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const EmptyType>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<EmptyType&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const EmptyType&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<EmptyType*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const EmptyType*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<EmptyType&&>::Value()).second);

	ASSERT_TRUE(hash.insert(TypeInfo<OtherEmptyType>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const OtherEmptyType>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<OtherEmptyType&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const OtherEmptyType&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<OtherEmptyType*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const OtherEmptyType*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<OtherEmptyType&&>::Value()).second);

	ASSERT_TRUE(hash.insert(TypeInfo<ChildTest>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const ChildTest>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<ChildTest&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const ChildTest&>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<ChildTest*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<const ChildTest*>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<ChildTest&&>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<EmptyType>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const EmptyType>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<EmptyType&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const EmptyType&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<EmptyType*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const EmptyType*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<EmptyType&&>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<OtherEmptyType>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const OtherEmptyType>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<OtherEmptyType&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const OtherEmptyType&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<OtherEmptyType*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const OtherEmptyType*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<OtherEmptyType&&>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<ChildTest>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const ChildTest>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<ChildTest&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const ChildTest&>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<ChildTest*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<const ChildTest*>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<ChildTest&&>::Value()).second);

	////////////////////////////////////////////////////////////////////////////////

	ASSERT_TRUE(hash.insert(TypeInfo<struct LocalEmptyA>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<struct LocalEmptyA>::Value()).second);

	ASSERT_TRUE(hash.insert(TypeInfo<struct LocalEmptyB>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<struct LocalEmptyB>::Value()).second);

	////////////////////////////////////////////////////////////////////////////////

	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<EmptyType>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<OtherEmptyType>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<int>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<char>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<void>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<int*>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<char*>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<void*>>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::EmptyTestType<EmptyType>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::EmptyTestType<OtherEmptyType>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::EmptyTestType<int>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::EmptyTestType<char>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::EmptyTestType<void>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::EmptyTestType<int*>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::EmptyTestType<char*>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::EmptyTestType<void*>>::Value()).second);

	////////////////////////////////////////////////////////////////////////////////

	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<struct LocalEmptyA>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<struct LocalEmptyA>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<struct LocalEmptyB>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::EmptyTestType<struct LocalEmptyB>>::Value()).second);

	////////////////////////////////////////////////////////////////////////////////

	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::StaticTestType<EmptyType>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::StaticTestType<OtherEmptyType>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::StaticTestType<int>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::StaticTestType<char>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::StaticTestType<void>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::StaticTestType<int*>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::StaticTestType<char*>>::Value()).second);
	ASSERT_TRUE(hash.insert(TypeInfo<Primitives::StaticTestType<void*>>::Value()).second);

	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::StaticTestType<EmptyType>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::StaticTestType<OtherEmptyType>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::StaticTestType<int>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::StaticTestType<char>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::StaticTestType<void>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::StaticTestType<int*>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::StaticTestType<char*>>::Value()).second);
	ASSERT_FALSE(hash.insert(TypeInfo<Primitives::StaticTestType<void*>>::Value()).second);
}

TEST_F(Director, TypeIndex_Basics)
{
	using namespace Detail;

	std::set<std::uint32_t> index;

	struct Tag;

	////////////////////////////////////////////////////////////////////////////////

	ASSERT_TRUE(index.insert(TypeIndex<Tag>::Value<int>()).second);
	ASSERT_FALSE(index.insert(TypeIndex<Tag>::Value<int>()).second);

	ASSERT_TRUE(index.insert(TypeIndex<Tag>::Value<char>()).second);
	ASSERT_FALSE(index.insert(TypeIndex<Tag>::Value<char>()).second);

	ASSERT_TRUE(index.insert(TypeIndex<Tag>::Value<float>()).second);
	ASSERT_FALSE(index.insert(TypeIndex<Tag>::Value<float>()).second);

	ASSERT_FALSE(index.insert(TypeIndex<char>::Value<Tag>()).second);
	ASSERT_FALSE(index.insert(TypeIndex<int>::Value<Tag>()).second);

	////////////////////////////////////////////////////////////////////////////////

	index.clear();

	ASSERT_EQ(*(index.insert(TypeIndex<int>::Value<Tag>()).first), 0u);
	ASSERT_EQ(*(index.insert(TypeIndex<const int>::Value<Tag>()).first), 0u);
	ASSERT_EQ(*(index.insert(TypeIndex<int&>::Value<Tag>()).first), 0u);
	ASSERT_EQ(*(index.insert(TypeIndex<const int&>::Value<Tag>()).first), 0u);
	ASSERT_EQ(*(index.insert(TypeIndex<int*>::Value<Tag>()).first), 0u);
	ASSERT_EQ(*(index.insert(TypeIndex<const int*>::Value<Tag>()).first), 0u);
	ASSERT_EQ(*(index.insert(TypeIndex<int&&>::Value<Tag>()).first), 0u);
		   
	ASSERT_EQ(*(index.insert(TypeIndex<void>::Value<Tag>()).first), 0u);
	ASSERT_EQ(*(index.insert(TypeIndex<const void>::Value<Tag>()).first), 0u);
	ASSERT_EQ(*(index.insert(TypeIndex<void*>::Value<Tag>()).first), 0u);
	ASSERT_EQ(*(index.insert(TypeIndex<const void*>::Value<Tag>()).first), 0u);
}