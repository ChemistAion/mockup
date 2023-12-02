#include "_tests_pch.hpp"

#include "buffer.hpp"

TEST_F(Buffer, Cube)
{
	auto source = parser_.load("assets\\cube\\cube.gltf");
	ASSERT_FALSE(source.error());

	auto element = source.at_key("buffers");
	ASSERT_FALSE(element.error());

	////////////////////////////////////////////////////////////////////////////////

	auto buffers = glTF::GetBuffers(element.value());

	ASSERT_EQ(buffers.size(), 1);

	ASSERT_EQ(buffers[0].size_, 1800);
	ASSERT_TRUE(buffers[0].uri_.value() == "Cube.bin");
	
	return;
}

TEST_F(BufferView, Cube)
{
	auto source = parser_.load("assets\\cube\\cube.gltf");
	ASSERT_FALSE(source.error());

	auto element = source.at_key("bufferViews");
	ASSERT_FALSE(element.error());

	////////////////////////////////////////////////////////////////////////////////

	auto views = glTF::GetBufferViews(element.value());

	ASSERT_EQ(views.size(), 5);

	ASSERT_EQ(views[0].size_, 72);
	ASSERT_EQ(views[0].offset_, 0);
	ASSERT_EQ(views[0].target_, glTF::BufferView::Target::ElementArrayBuffer);

	ASSERT_EQ(views[1].size_, 432);
	ASSERT_EQ(views[1].offset_, 72);
	ASSERT_EQ(views[1].target_, glTF::BufferView::Target::ArrayBuffer);

	ASSERT_EQ(views[2].size_, 432);
	ASSERT_EQ(views[2].offset_, 504);
	ASSERT_EQ(views[2].target_, glTF::BufferView::Target::ArrayBuffer);

	ASSERT_EQ(views[3].size_, 576);
	ASSERT_EQ(views[3].offset_, 936);
	ASSERT_EQ(views[3].target_, glTF::BufferView::Target::ArrayBuffer);

	ASSERT_EQ(views[4].size_, 288);
	ASSERT_EQ(views[4].offset_, 1512);
	ASSERT_EQ(views[4].target_, glTF::BufferView::Target::ArrayBuffer);

	return;
}