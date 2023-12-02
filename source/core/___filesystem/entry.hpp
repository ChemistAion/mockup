#pragma once

#include <atomic>
#include <filesystem>
#include <string>
#include <tuple>

namespace Mockup::Core::Filesystem
{
	class Dataset;

	class Entry
	{
		friend Dataset;
	public:
		enum Type
		{
			File,
			Directory,
			None
		};

		enum Status
		{
			Unknown,
			Valid,
			Created,
			Modified,
			Removed,
			Error
		};

	private:
		Status status_ = Status::Unknown;

		std::filesystem::file_time_type time_;
		std::uintmax_t size_ = 0;

		std::filesystem::file_type type_ = std::filesystem::file_type::none;

		std::filesystem::path path_;
	public:
		static Entry BuildEntry(const std::wstring& path) noexcept;

		////////////////////////////////////////////////////////////////////////////////

		inline bool operator==(const Entry& other) const noexcept
		{
			if (type_ == other.type_ && time_ == other.time_ && size_ == other.size_)
			{
				return true;
			}
		
			return false;
		}

		////////////////////////////////////////////////////////////////////////////////
		
		inline decltype(auto) GetStatus() const noexcept
		{
			return status_;
		}

		inline decltype(auto) GetPath() const noexcept
		{
			return path_;
		}

		inline decltype(auto) GetType() const noexcept
		{
			if (type_ == std::filesystem::file_type::regular)
			{
				return Type::File;
			}

			if (type_ == std::filesystem::file_type::directory)
			{
				return Type::Directory;
			}

			return Type::None;
		}

	};
}