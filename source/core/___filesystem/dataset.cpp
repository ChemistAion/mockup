#include "pch.hpp"

#include "dataset.hpp"

namespace Mockup::Core::Filesystem
{
	Dataset::Dataset(const std::wstring& path)
		: path_length_(path.size())
	{
		std::error_code error;

		if (self_.assign({ path }, error), error)
		{
			return;
		}
		
		if (auto status = std::filesystem::status(path, error); !std::filesystem::status_known(status))
		{
			return;
		}

		for (const auto& element : Build())
		{
			auto entry_path = element.path_.wstring();
			auto entry_name = entry_path.substr(path_length_);
		
			entries_.emplace(std::move(entry_name), element);
		}
	}

	std::vector<Entry> Dataset::Build()
	{
		std::error_code error;

		if (self_.refresh(error), error)
		{
			return {};
		}

		const auto time = std::filesystem::last_write_time(self_.path(), error);

		if (error)
		{
			return {};
		}

		////////////////////////////////////////////////////////////////////////////////

		std::filesystem::recursive_directory_iterator iterator
		(
			self_.path(),
			std::filesystem::directory_options::skip_permission_denied,
			error
		);

		if (error)
		{
			return {};
		}

		////////////////////////////////////////////////////////////////////////////////

		std::vector<Entry> result;

		for (const auto& element : iterator)
		{
			auto entry = Entry::BuildEntry(element.path().wstring());
			result.emplace_back(std::move(entry));
		}

		return result;
	}

	std::map<std::wstring, Entry> Dataset::Process(const std::vector<Entry>& entries)
	{	
		for (auto iterator = entries_.begin(); iterator != entries_.end();)
		{
			auto& element = iterator->second;

			if (element.status_ == Entry::Removed || element.status_ == Entry::Error || element.status_ == Entry::Unknown)
			{
				iterator = entries_.erase(iterator);
				continue;
			}

			element.status_ = Entry::Status::Removed;
			iterator++;
		}

		////////////////////////////////////////////////////////////////////////////////

		for (const auto& element : entries)
		{
			const auto path = element.path_.wstring();
			const auto name = path.substr(path_length_);

			auto search = entries_.find(name);

			if (search == entries_.end())
			{
				entries_.emplace(std::move(name), element);
				continue;
			}

			////////////////////////////////////////////////////////////////////////////////

			auto& found = search->second;

			if (element.status_ == Entry::Error || element.status_ == Entry::Unknown)
			{
				found.status_ = element.status_;
				continue;
			}

			if (found == element)
			{
				found.status_ = Entry::Valid;
				continue;
			}

			////////////////////////////////////////////////////////////////////////////////

			assert(found.type_ == element.type_);

			found.status_ = Entry::Modified;

			found.time_ = element.time_;
			found.size_ = element.size_;
		}

		return entries_;
	}
}