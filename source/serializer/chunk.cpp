#include "chunk.hpp"

namespace Mockup::Serializer
{
	std::uint8_t Chunk::ClampTextStringSize(const std::string& string) const
	{
		return (string.size() > 0xff ? 0xff : (std::uint8_t)string.size());
	}

	void Chunk::WriteTextString(const std::string& string, std::ofstream& output) const
	{
		auto size = ClampTextStringSize(string);
		
		output.write(reinterpret_cast<const char*>(&size), sizeof(size));
		output.write(reinterpret_cast<const char*>(string.c_str()), size);
	}

	std::string Chunk::ReadTextString(std::ifstream& input)
	{
		char text[256];

		std::uint8_t size;
		input.read(reinterpret_cast<char*>(&size), sizeof(size));
		input.read(reinterpret_cast<char*>(text), size);

		if (input.good())
		{
			return std::string(text, size);
		}

		return {};
	}

	std::uint32_t Chunk::CalculateOffset(const std::string& name) const
	{
		auto size = (std::uint32_t)(sizeof(std::uint32_t) + context_.GetSize() + sizeof(std::uint32_t));

		size += sizeof(std::uint8_t) + ClampTextStringSize(name);

		if (flags_ & Flag::Valid)
		{
			size += sizeof(std::uint8_t) + ClampTextStringSize(context_.GetName());
		}

		if (flags_ & Flag::Debug)
		{
			size += sizeof(std::uint8_t) + ClampTextStringSize(context_.GetDebugInfo());
		}

		return size;
	}

	void Chunk::ToStream(const std::string& name, std::ofstream& output) const
	{
		auto offset = CalculateOffset(name);

		output.write(reinterpret_cast<const char*>(&cSerializer_MetadataPrefix), sizeof(cSerializer_MetadataPrefix));
		output.write(reinterpret_cast<const char*>(&flags_), sizeof(flags_));
		output.write(reinterpret_cast<const char*>(&offset), sizeof(offset));
		output.write(reinterpret_cast<const char*>(&cSerializer_MetadataSuffix), sizeof(cSerializer_MetadataSuffix));

		WriteTextString(name, output);

		if (flags_ & Flag::Valid)
		{
			WriteTextString(context_.GetName(), output);
		}

		if (flags_ & Flag::Debug)
		{
			WriteTextString(context_.GetDebugInfo(), output);
		}

		{
			auto size = (std::uint32_t)(context_.GetSize());
			auto negation = ~size;

			output.write(reinterpret_cast<const char*>(&negation), sizeof(negation));
			output.write(reinterpret_cast<const char*>(context_.GetData()), size);
			output.write(reinterpret_cast<const char*>(&size), sizeof(size));
		}
	}

	std::pair<std::streampos, bool> Chunk::FromStream(const std::string& name, std::ifstream& input)
	{
		Flags flags;
		std::uint32_t offset;

		////////////////////////////////////////////////////////////////////////////////

		{
			std::uint16_t prefix;
			std::uint16_t suffix;

			auto position = input.tellg();

			input.read(reinterpret_cast<char*>(&prefix), sizeof(prefix));
			input.read(reinterpret_cast<char*>(&flags), sizeof(flags));
			input.read(reinterpret_cast<char*>(&offset), sizeof(offset));
			input.read(reinterpret_cast<char*>(&suffix), sizeof(suffix));

			if (input.rdstate() != std::ios::goodbit)
			{
				return std::make_pair(position, false);
			}

			if (prefix != cSerializer_MetadataPrefix || suffix != cSerializer_MetadataSuffix)
			{
				return std::make_pair(position, false);
			}
		}

		////////////////////////////////////////////////////////////////////////////////

		{
			auto position = input.tellg();

			auto chunk_end = position + (std::streamoff)offset;

			std::uint32_t size;
			std::uint32_t negation;

			input.seekg(chunk_end - (std::streamoff)sizeof(size));
			input.read(reinterpret_cast<char*>(&size), sizeof(size));

			if (!input.good())
			{
				input.seekg(position);
				return std::make_pair(position, false);
			}

			input.seekg(chunk_end - (std::streamoff)(sizeof(size) * 2) - (std::streamoff)(size));
			input.read(reinterpret_cast<char*>(&negation), sizeof(negation));

			if (!input.good())
			{
				input.seekg(position);
				return std::make_pair(position, false);
			}

			input.seekg(position);

			if (size != ~negation)
			{
				return std::make_pair(position, false);
			}
		}

		////////////////////////////////////////////////////////////////////////////////
		
		auto position = input.tellg() + (std::streamoff)offset;

		auto archive_name = std::move(ReadTextString(input));

		if (archive_name != name)
		{
			return std::make_pair(position, true);
		}

		if (flags & Flag::Valid)
		{
			context_.name_ = std::move(ReadTextString(input));
		}

		if (flags & Flag::Debug)
		{
			context_.debug_ = std::move(ReadTextString(input));
		}

		{
			std::uint32_t negation;

			input.read(reinterpret_cast<char*>(&negation), sizeof(negation));

			std::uint32_t size = ~negation;

			auto& storage = context_.storage_;
			storage = std::make_unique<std::byte[]>(size);

			input.read(reinterpret_cast<char*>(storage.get()), size);
			input.read(reinterpret_cast<char*>(&size), sizeof(size));

			if (!input.good() || input.tellg() != position || size != ~negation)
			{
				return std::make_pair(position - (std::streamoff)offset, false);
			}

			context_.size_ = size;
			flags_ = flags;
		}

		return std::make_pair(position, true);
	}
}