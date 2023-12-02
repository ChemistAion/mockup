#include "pch.hpp"

#include "entry.hpp"

namespace Mockup::Core::Filesystem
{
	Entry Entry::BuildEntry(const std::wstring& path) noexcept
	{
		Entry entry;
		std::error_code error;
	
		entry.path_.assign(path);
		auto status = std::filesystem::status(path, error);
	
		if (!std::filesystem::status_known(status))
		{
			entry.status_ = Error;
			return entry;
		}
	
		auto type = status.type();
		
		if (entry.type_ = type; type == std::filesystem::file_type::not_found)
		{
			return entry;
		}
	
		if (entry.time_ = std::filesystem::last_write_time(path, error); error)
		{
			entry.status_ = Error;
			return entry;
		}
	
		if (type == std::filesystem::file_type::regular)
		{	
			if (entry.size_ = std::filesystem::file_size(path, error); error)
			{
				entry.status_ = Error;
				return entry;
			}

			entry.status_ = Created;
		}
		else
		{
			if (type == std::filesystem::file_type::directory)
			{
				entry.status_ = Created;
			}
		}

		return entry;
	}
}