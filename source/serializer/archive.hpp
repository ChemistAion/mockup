#pragma once

#include "context.hpp"
#include "chunk.hpp"

#include <fstream>
#include <limits>
#include <string>
#include <vector>

namespace Mockup::Serializer
{
	class Archive
	{
	public:
		using Flag = Chunk::Flag;

	private:
		std::string name_;
		Flags flags_ = Flag::Empty;

		std::vector<Chunk> chunks_;

	public:
		Archive() = delete;

		Archive(const char* name, Flags flags)
		{	
			name_ = std::string(name);
			flags_ = flags;
		}

		Archive(const char* name, std::ifstream& input)
		{
			name_ = std::string(name);

//			input.ignore(std::numeric_limits<std::streamsize>::max());		
//			
//			auto length = input.gcount();
//			std::ios::pos_type position = 0;
//			
//			input.clear();
//			input.seekg(position, std::ios_base::beg);

			while(input.good() && !input.eof())
			{
				auto position = input.tellg();

				Chunk chunk;
				auto result = chunk.FromStream(name_, input);

				if (result.second)
				{
					chunks_.push_back(std::move(chunk));
					continue;
				}
			}

			return;
		}

		////////////////////////////////////////////////////////////////////////////////

		template <class Type>
		void Serialize(const char* name, Flags flags, Type&& type)
		{		
			chunks_.emplace_back(name, flags | flags_, std::forward<Type>(type));
		}

		void ToStream(std::ofstream& output) const
		{
			for (const auto &chunk : chunks_)
			{
				chunk.ToStream(name_, output);
			}
		}
	};
}