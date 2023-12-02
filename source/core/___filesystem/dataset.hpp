#pragma once

#include "entry.hpp"

#include <algorithm>
#include <chrono>
#include <cassert>
#include <iomanip>
#include <iterator>
#include <filesystem>
#include <iostream>
#include <map>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

namespace Mockup::Core::Filesystem
{
	class Dataset
	{
		std::map<std::wstring, Entry> entries_;

		std::filesystem::directory_entry self_;

		const std::size_t path_length_;
	public:
		Dataset() = delete;

		explicit Dataset(const std::wstring& path);
		~Dataset() = default;
		
		Dataset(const Dataset&) = delete;
		Dataset& operator=(const Dataset&) = delete;

		////////////////////////////////////////////////////////////////////////////////

//		BuildResult Build();
//		std::map<std::wstring, Entry> Process(const BuildResult& build);

		std::vector<Entry> Build();
		std::map<std::wstring, Entry> Process(const std::vector<Entry>& entries);


		////////////////////////////////////////////////////////////////////////////////

		inline decltype(auto) GetSize() const noexcept
		{
			return entries_.size();
		}
	};
}
