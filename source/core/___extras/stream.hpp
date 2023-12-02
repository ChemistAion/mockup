#pragma once

namespace Mockup::Core
{
	template <typename Container, typename CharType = char, typename Traits = std::char_traits<CharType>, typename Allocator = std::allocator<CharType>>
	auto ReadStream(std::basic_istream<CharType, Traits>& stream, Allocator allocator = {})
	{
		auto const start = stream.tellg();

		if (start == std::streamsize(-1) || !stream.ignore(std::numeric_limits<std::streamsize>::max()))
		{
			return Container();
		};
		
		auto const size = stream.gcount();
		
		if (size == 0 || !stream.seekg(start))
		{
			return Container();
		};
		
		auto container = Container(std::move(allocator));
		container.resize(static_cast<std::size_t>(size));
		
		if (!container.empty())
		{
			if (!stream.read(reinterpret_cast<CharType*>(&container[0]), size))
			{
				return Container();
			};
		}
		
		return container;
	}
}