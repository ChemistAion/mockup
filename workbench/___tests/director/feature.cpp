#include "director.hpp"

TEST_F(Director, Feature_Basics)
{
	Registry registryA;
	Registry registryB;

	struct EmptyType
	{
	};

	struct OtherEmptyType
	{
	};

	struct ChildTest : EmptyType
	{
	};

	ASSERT_FALSE(registryA.Has<EmptyType>());
	ASSERT_FALSE(registryA.Has<void>());
	ASSERT_FALSE(registryA.Has<void*>());

	ASSERT_FALSE(registryB.Has<EmptyType>());
	ASSERT_FALSE(registryB.Has<void>());
	ASSERT_FALSE(registryB.Has<void*>());
	
	registryA.Emplace<EmptyType>();
	registryA.Emplace<OtherEmptyType>();
	registryA.Emplace<ChildTest>();

//	registry.Emplace<EmptyType>();
//	registry.Emplace<OtherEmptyType>();
	registryB.Emplace<ChildTest>();
	registryB.Emplace<void>();
	
	ASSERT_TRUE(registryA.Has<EmptyType>());
	ASSERT_TRUE(registryA.Has<OtherEmptyType>());
	ASSERT_TRUE(registryA.Has<ChildTest>());

	ASSERT_FALSE(registryB.Has<EmptyType>());
	ASSERT_FALSE(registryB.Has<OtherEmptyType>());
	ASSERT_TRUE(registryB.Has<ChildTest>());

	ASSERT_FALSE(registryA.Has<void>());
	ASSERT_TRUE(registryB.Has<void>());

	return;
}