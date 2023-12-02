#include "_tests_pch.hpp"

#include "sampler.hpp"

TEST_F(Sampler, Cube)
{
	auto source = parser_.load("assets\\cube\\cube.gltf");
	ASSERT_FALSE(source.error());

	auto element = source.at_key("samplers");
	ASSERT_FALSE(element.error());

	////////////////////////////////////////////////////////////////////////////////

	auto samplers = glTF::GetSamplers(element.value());

	ASSERT_EQ(samplers.size(), 1);

	return;
}