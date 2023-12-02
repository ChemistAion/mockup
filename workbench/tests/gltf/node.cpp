#include "_tests_pch.hpp"

#include "node.hpp"

TEST_F(Node, Cube)
{
	auto source = parser_.load("assets\\cube\\cube.gltf");
	ASSERT_FALSE(source.error());

	auto element = source.at_key("nodes");
	ASSERT_FALSE(element.error());

	////////////////////////////////////////////////////////////////////////////////

	auto nodes = glTF::GetNodes(element.value());

	ASSERT_EQ(nodes.size(), 1);

	ASSERT_EQ(nodes[0].mesh_, 0);
	ASSERT_EQ(nodes[0].name_, "Cube");
	
	return;
}