#pragma once

#include "context.hpp"

#include <fstream>
#include <string>
#include <vector>

namespace Mockup::Serializer
{
	using Flags = std::uint32_t;

	constexpr Flags cSerializer_FlagsMaskFunction = 0x000000ff;
	constexpr Flags cSerializer_FlagsMaskType = 0x0000ff00;
	constexpr Flags cSerializer_FlagsMaskAlgorithm = 0x0fff0000;
	constexpr Flags cSerializer_FlagsMaskVersion = 0xf0000000;

	constexpr std::uint16_t cSerializer_MetadataPrefix = 0x4B4D;
	constexpr std::uint16_t cSerializer_MetadataSuffix = 0x5043;

	class Chunk
	{
	public:
		enum Flag : Flags
		{
			Empty = 0u << 0,
			Valid = 1u << 0, // 1 byte size + string
			Debug = 1u << 1, // 1 byte size + string
			Checksum = 1u << 2,
			Hash = 1u << 3,
			Pack = 1u << 4,
			//Reserved	= 1u << 5,
			//Reserved	= 1u << 6,
			//Reserved	= 1u << 7,

			Const = 1u << 8,
			Dynamic = 1u << 9,
			Elusive = 1u << 10,
			Stream = 1u << 11,
			//Reserved = 1u << 12,
			//Reserved = 1u << 13,
			//Reserved = 1u << 14,
			//Reserved = 1u << 15,

			//MetaData = 1u << 16,
			//MetaData = 1u << 17,
			//MetaData = 1u << 18,
			//MetaData = 1u << 19,
			//MetaData = 1u << 20,
			//MetaData = 1u << 21,
			//MetaData = 1u << 22,
			//MetaData = 1u << 23,
			//MetaData = 1u << 24,
			//MetaData = 1u << 25,
			//MetaData = 1u << 26,
			//MetaData = 1u << 27,

			Version1 = 1u << 28,
			Version2 = 1u << 29,
			Version3 = 1u << 30,
			NextGen = 1u << 31
		};
	private:
		Flags flags_ = Flag::Empty;
		Context context_;

		////////////////////////////////////////////////////////////////////////////////

		std::uint8_t ClampTextStringSize(const std::string& string) const;
		void WriteTextString(const std::string& string, std::ofstream& output) const;

		std::string ReadTextString(std::ifstream& input);

		std::uint32_t CalculateOffset(const std::string& name) const;
	public:
		Chunk() = default;

		template <class Type>
		explicit Chunk(const char* name, Flags flags, Type&& type)
			: context_(name, std::forward<Type>(type))
			, flags_(flags)
		{
		}
	
		void ToStream(const std::string& name, std::ofstream& output) const;
		std::pair<std::streampos, bool> FromStream(const std::string& name, std::ifstream& input);
	};
}