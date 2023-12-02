#pragma once

namespace Mockup::glTF
{
	struct BufferView
	{
		enum class Target
		{
			ArrayBuffer = 34962,
			ElementArrayBuffer = 34963
		};

		Index buffer_;
		std::uint64_t offset_ = 0;
		std::uint64_t size_ = 0;
		std::uint64_t stride_ = 0; //optional
		std::optional<Target> target_;

		Name name_;
		Extras extras_;
	};

	using BufferViews = std::vector<BufferView>;
	BufferViews GetBufferViews(const simdjson::dom::element& element);
}