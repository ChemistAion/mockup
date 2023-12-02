#include "dataset_test.hpp"

using namespace Primitives;

TEST_F(Filesystem, Dataset_Valid)
{
	Dataset dataset1(dir1_);
	Dataset dataset2(dir2_);
	Dataset dataset3(dir3_);

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}
}

TEST_F(Filesystem, Dataset_ModifiedHard)
{
	Dataset dataset1(dir1_);
	Dataset dataset2(dir2_);
	Dataset dataset3(dir3_);

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::error_code error;

		auto time = std::filesystem::file_time_type::clock::now();

		std::filesystem::last_write_time(entry21_, time, error);
		std::filesystem::last_write_time(entry22_, time, error);
		std::filesystem::last_write_time(entry23_, time, error);

		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		std::size_t modified2 = 0;

		for (const auto& entry : update2)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Modified, entry.second.GetStatus());
				modified2++;
			}
		}

		ASSERT_EQ(modified2, 3);

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}
}
	
TEST_F(Filesystem, Dataset_Created)
{
	std::error_code error;

	auto path_created21 = entry21_;
	auto path_created22 = entry22_;
	auto path_created23 = entry23_;

	path_created21 += L"_new";
	path_created22 += L"_new";
	path_created23 += L"_new";

	std::filesystem::remove(path_created21, error);
	std::filesystem::remove(path_created22, error);
	std::filesystem::remove(path_created23, error);

	Dataset dataset1(dir1_);
	Dataset dataset2(dir2_);
	Dataset dataset3(dir3_);

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		GenerateContent(path_created21, size1_);
		GenerateContent(path_created22, size2_);
		GenerateContent(path_created23, size3_);

		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		std::size_t created2 = 0;

		for (const auto& entry : update2)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Created, entry.second.GetStatus());
				created2++;
			}
		}

		ASSERT_EQ(created2, 3);

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}
}

TEST_F(Filesystem, Dataset_CreatedRemoved)
{
	using namespace std::chrono_literals;

	std::error_code error;

	auto path_created22 = entry22_;
	auto path_created21 = entry21_;
	auto path_created23 = entry23_;

	path_created21 += L"_new";
	path_created22 += L"_new";
	path_created23 += L"_new";

	std::filesystem::remove(path_created21, error);
	std::filesystem::remove(path_created22, error);
	std::filesystem::remove(path_created23, error);

	auto path_created31 = entry31_;
	auto path_created32 = entry32_;
	auto path_created33 = entry33_;

	path_created31 += L"_new";
	path_created32 += L"_new";
	path_created33 += L"_new";

	std::filesystem::remove(path_created31, error);
	std::filesystem::remove(path_created32, error);
	std::filesystem::remove(path_created33, error);

	Dataset dataset1(dir1_);
	Dataset dataset2(dir2_);
	Dataset dataset3(dir3_);

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		GenerateContent(path_created21, size1_);
		GenerateContent(path_created22, size2_);
		GenerateContent(path_created23, size3_);

		GenerateContent(path_created31, size1_);
		GenerateContent(path_created32, size2_);
		GenerateContent(path_created33, size3_);

		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		std::size_t created2 = 0;

		for (const auto& entry : update2)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Created, entry.second.GetStatus());
				created2++;
			}
		}

		ASSERT_EQ(created2, 3);

		std::size_t created3 = 0;

		for (const auto& entry : update3)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Created, entry.second.GetStatus());
				created3++;
			}
		}

		ASSERT_EQ(created2, 3);
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::filesystem::remove(path_created21, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::remove(path_created22, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::remove(path_created23, error);
		std::this_thread::sleep_for(3ms);

		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		std::size_t removed2 = 0;

		for (const auto& entry : update2)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Removed, entry.second.GetStatus());
				removed2++;
			}
		}

		ASSERT_EQ(removed2, 3);

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::filesystem::remove(path_created31, error);
		std::filesystem::remove(path_created32, error);
		std::filesystem::remove(path_created33, error);

		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		std::size_t removed3 = 0;

		for (const auto& entry : update3)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Removed, entry.second.GetStatus());
				removed3++;
			}
		}

		ASSERT_EQ(removed3, 3);
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}
}

TEST_F(Filesystem, Dataset_DuplicatedRemoved)
{
	using namespace std::chrono_literals;

	std::error_code error;

	auto path_dup11a = entry11_;
	auto path_dup12a = entry12_;
	auto path_dup12aa = entry12_;
	auto path_dup12aaa = entry12_;
	auto path_dup13a = entry13_;
	auto path_dup31b = entry31_;
	auto path_dup31bb = entry31_;
	auto path_dup31bbb = entry31_;
	auto path_dup32b = entry32_;
	auto path_dup33b = entry33_;

	path_dup11a += L"_a";
	path_dup12a += L"_a";
	path_dup12aa += L"_aa";
	path_dup12aaa += L"_aaa";
	path_dup13a += L"_a";
	path_dup31b += L"_b";
	path_dup31bb += L"_bb";
	path_dup31bbb += L"_bbb";
	path_dup32b += L"_b";
	path_dup33b += L"_b";

	std::filesystem::remove(path_dup11a, error);
	std::filesystem::remove(path_dup12a, error);
	std::filesystem::remove(path_dup12aa, error);
	std::filesystem::remove(path_dup12aaa, error);
	std::filesystem::remove(path_dup13a, error);
	std::filesystem::remove(path_dup31b, error);
	std::filesystem::remove(path_dup31bb, error);
	std::filesystem::remove(path_dup31bbb, error);
	std::filesystem::remove(path_dup32b, error);
	std::filesystem::remove(path_dup33b, error);

	Dataset dataset1(dir1_);
	Dataset dataset2(dir2_);
	Dataset dataset3(dir3_);

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::filesystem::copy_file(entry11_, path_dup11a, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(entry12_, path_dup12a, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(entry12_, path_dup12aa, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(entry12_, path_dup12aaa, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(entry13_, path_dup13a, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(entry31_, path_dup31b, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(entry31_, path_dup31bb, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(entry31_, path_dup31bbb, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(entry32_, path_dup32b, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(entry33_, path_dup33b, std::filesystem::copy_options::update_existing, error);

		{
			auto update = dataset1.Process(dataset1.Build());

			std::size_t created = 0;
			std::size_t modified = 0;
			std::size_t valid = 0;

			for (const auto& entry : update)
			{
				switch (entry.second.GetStatus())
				{
				case Entry::Created:
					created++;
					break;
				case Entry::Modified:
					modified++;
					break;
				case Entry::Valid:
					valid++;
					break;
				default:
					break;
				}
			}

			ASSERT_EQ(created, 5);
			ASSERT_EQ(modified, 0);
			ASSERT_EQ(valid, 3);
		}

		{
			auto update = dataset2.Process(dataset2.Build());

			std::size_t created = 0;
			std::size_t modified = 0;
			std::size_t valid = 0;

			for (const auto& entry : update)
			{
				switch (entry.second.GetStatus())
				{
				case Entry::Created:
					created++;
					break;
				case Entry::Modified:
					modified++;
					break;
				case Entry::Valid:
					valid++;
					break;
				default:
					break;
				}
			}

			ASSERT_EQ(created, 0);
			ASSERT_EQ(modified, 0);
			ASSERT_EQ(valid, 3);
		}

		{
			auto update = dataset3.Process(dataset3.Build());

			std::size_t created = 0;
			std::size_t modified = 0;
			std::size_t valid = 0;

			for (const auto& entry : update)
			{
				switch (entry.second.GetStatus())
				{
				case Entry::Created:
					created++;
					break;
				case Entry::Modified:
					modified++;
					break;
				case Entry::Valid:
					valid++;
					break;
				default:
					break;
				}
			}

			ASSERT_EQ(created, 5);
			ASSERT_EQ(modified, 0);
			ASSERT_EQ(valid, 3);
		}

	}

	////////////////////////////////////////////////////////////////////////////////

	{	
		std::filesystem::remove(path_dup11a, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::remove(path_dup12a, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::remove(path_dup12aa, error);
		std::this_thread::sleep_for(3ms);
//		std::filesystem::remove(path_dup12aaa, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::remove(path_dup13a, error);
		std::this_thread::sleep_for(3ms);

		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		{
			auto update = dataset1.Process(dataset1.Build());

			std::size_t created = 0;
			std::size_t modified = 0;
			std::size_t valid = 0;
			std::size_t removed = 0;

			for (const auto& entry : update)
			{
				switch (entry.second.GetStatus())
				{
				case Entry::Created:
					created++;
					break;
				case Entry::Modified:
					modified++;
					break;
				case Entry::Valid:
					valid++;
					break;
				case Entry::Removed:
					removed++;
					break;
				default:
					break;
				}
			}

			ASSERT_EQ(created, 0);
			ASSERT_EQ(modified, 0);
			ASSERT_EQ(valid, 4);
			ASSERT_EQ(removed, 4);
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::filesystem::remove(path_dup31b, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::remove(path_dup31bb, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::remove(path_dup31bbb, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::remove(path_dup32b, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::remove(path_dup33b, error);
		std::this_thread::sleep_for(3ms);

		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		std::size_t removed3 = 0;

		for (const auto& entry : update3)
		{
			if (entry.second.GetStatus() == Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
			}
			else
			{
				ASSERT_EQ(Entry::Status::Removed, entry.second.GetStatus());
				removed3++;
			}
		}

		ASSERT_EQ(removed3, 5);
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}
}

TEST_F(Filesystem, Dataset_RenamedRemoved)
{
	using namespace std::chrono_literals;

	std::error_code error;

	auto path_created21 = entry21_;
	auto path_created22 = entry22_;
	auto path_created23 = entry23_;
	auto path_copied21 = entry21_;
	auto path_copied22 = entry22_;
	auto path_copied23 = entry23_;

	path_created21 += L"_new";
	path_created22 += L"_new";
	path_created23 += L"_new";
	path_copied21 += L"_copy";
	path_copied22 += L"_copy";
	path_copied23 += L"_copy";

	std::filesystem::remove(path_created21, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_created22, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_created23, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_copied21, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_copied22, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_copied23, error);
	std::this_thread::sleep_for(10ms);

	auto path_renamed21a = entry21_;
	auto path_renamed22a = entry22_;
	auto path_renamed23a = entry23_;
	auto path_renamed21b = entry21_;
	auto path_renamed22b = entry22_;
	auto path_renamed23b = entry23_;

	path_renamed21a += L"_a_ren";
	path_renamed22a += L"_a_ren";
	path_renamed23a += L"_a_ren";
	path_renamed21b += L"_b_ren";
	path_renamed22b += L"_b_ren";
	path_renamed23b += L"_b_ren";

	std::filesystem::remove(path_renamed21a, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_renamed22a, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_renamed23a, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_renamed21b, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_renamed22b, error);
	std::this_thread::sleep_for(10ms);
	std::filesystem::remove(path_renamed23b, error);
	std::this_thread::sleep_for(10ms);

	Dataset dataset1(dir1_);
	Dataset dataset2(dir2_);
	Dataset dataset3(dir3_);

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		GenerateContent(path_created21, size1_);
		GenerateContent(path_created22, size2_);
		GenerateContent(path_created23, size3_);

		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		std::size_t created2 = 0;

		for (const auto& entry : update2)
		{
			if (entry.second.GetStatus() == Entry::Status::Created)
			{
				created2++;
			}
		}

		ASSERT_EQ(created2, 3);

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::filesystem::rename(path_created21, path_renamed21a, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::rename(path_created22, path_renamed22a, error);
		std::this_thread::sleep_for(3ms);
		std::filesystem::rename(path_created23, path_renamed23a, error);
		std::this_thread::sleep_for(3ms);

		auto update1 = dataset1.Process(dataset1.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		{
			auto update = dataset2.Process(dataset2.Build());

			std::size_t created = 0;
			std::size_t modified = 0;
			std::size_t valid = 0;
			std::size_t removed = 0;

			for (const auto& entry : update)
			{
				switch (entry.second.GetStatus())
				{
				case Entry::Created:
					created++;
					break;
				case Entry::Modified:
					modified++;
					break;
				case Entry::Valid:
					valid++;
					break;
				case Entry::Removed:
					removed++;
					break;
				default:
					break;
				}
			}

			ASSERT_EQ(created, 3);
			ASSERT_EQ(modified, 0);
			ASSERT_EQ(valid, 3);
			ASSERT_EQ(removed, 3);
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::filesystem::copy_file(path_renamed21a, path_copied21, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(path_renamed22a, path_copied22, std::filesystem::copy_options::update_existing, error);
		std::filesystem::copy_file(path_renamed23a, path_copied23, std::filesystem::copy_options::update_existing, error);

		std::filesystem::rename(path_copied21, path_renamed21b, error);
		std::filesystem::rename(path_copied22, path_renamed22b, error);
		std::filesystem::rename(path_copied23, path_renamed23b, error);

		std::this_thread::sleep_for(3ms);

		auto update1 = dataset1.Process(dataset1.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		{
			auto update = dataset2.Process(dataset2.Build());

			std::size_t created = 0;
			std::size_t modified = 0;
			std::size_t valid = 0;
			std::size_t removed = 0;

			for (const auto& entry : update)
			{
				switch (entry.second.GetStatus())
				{
				case Entry::Created:
					created++;
					break;
				case Entry::Modified:
					modified++;
					break;
				case Entry::Valid:
					valid++;
					break;
				case Entry::Removed:
					removed++;
					break;
				default:
					break;
				}
			}

			ASSERT_EQ(created, 3);
			ASSERT_EQ(modified, 0);
			ASSERT_EQ(valid, 6);
			ASSERT_EQ(removed, 0);
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////


	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}
}

TEST_F(Filesystem, Dataset_EmptyAsRemoved)
{
	Dataset dataset1(dir1_);
	Dataset dataset2(dir2_);
	Dataset dataset3(dir3_);

	auto size2 = dataset2.GetSize();

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process({});
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		std::size_t removed2 = 0;

		for (const auto& entry : update2)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Removed, entry.second.GetStatus());
				removed2++;
			}
		}

		ASSERT_EQ(size2, removed2);

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		std::size_t created2 = 0;
	
		for (const auto& entry : update2)
		{
			if (entry.second.GetStatus() == Entry::Created)
			{
				ASSERT_EQ(Entry::Status::Created, entry.second.GetStatus());
				created2++;
			}
		}

		ASSERT_EQ(size2, created2);

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}
}
	
TEST_F(Filesystem, Dataset_FullRemove)
{
	std::error_code error;

	Dataset dataset1(dir1_);
	Dataset dataset2(dir2_);
	Dataset dataset3(dir3_);

	auto size1 = dataset1.GetSize();
	auto size2 = dataset2.GetSize();
	auto size3 = dataset3.GetSize();

	std::filesystem::remove_all(dir1_, error);
	std::filesystem::remove_all(dir2_, error);
	std::filesystem::remove_all(dir3_, error);

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process({});
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		std::size_t removed1 = 0;
		std::size_t removed2 = 0;
		std::size_t removed3 = 0;

		for (const auto& entry : update1)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Removed, entry.second.GetStatus());
				removed1++;
			}
		}

		for (const auto& entry : update2)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Removed, entry.second.GetStatus());
				removed2++;
			}
		}

		for (const auto& entry : update3)
		{
			if (entry.second.GetStatus() != Entry::Status::Valid)
			{
				ASSERT_EQ(Entry::Status::Removed, entry.second.GetStatus());
				removed3++;
			}
		}

		ASSERT_EQ(size1, removed1);
		ASSERT_EQ(size2, removed2);
		ASSERT_EQ(size3, removed3);
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		ASSERT_EQ(update1.empty(), true);
		ASSERT_EQ(update2.empty(), true);
		ASSERT_EQ(update3.empty(), true);
	}

	////////////////////////////////////////////////////////////////////////////////

	std::filesystem::create_directories(dir1_, error);

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		ASSERT_EQ(update1.empty(), true);
		ASSERT_EQ(update2.empty(), true);
		ASSERT_EQ(update3.empty(), true);
	}

	std::filesystem::create_directories(dir2_, error);

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		ASSERT_EQ(update1.empty(), true);
		ASSERT_EQ(update2.empty(), true);
		ASSERT_EQ(update3.empty(), true);
	}

	std::filesystem::create_directories(dir3_, error);

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		ASSERT_EQ(update1.empty(), true);
		ASSERT_EQ(update2.empty(), true);
		ASSERT_EQ(update3.empty(), true);
	}
}

TEST_F(Filesystem, Dataset_Complex)
{
	using namespace std::chrono_literals;

	std::error_code error;

	Dataset dataset1(dir1_);
	Dataset dataset2(dir2_);
	Dataset dataset3(dir3_);

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update1 = dataset1.Process(dataset1.Build());
		auto update2 = dataset2.Process(dataset2.Build());
		auto update3 = dataset3.Process(dataset3.Build());

		for (const auto& entry : update1)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update2)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}

		for (const auto& entry : update3)
		{
			ASSERT_EQ(Entry::Status::Valid, entry.second.GetStatus());
		}
	}

	////////////////////////////////////////////////////////////////////////////////

	auto dir12 = dir1_;
	auto dir13 = dir1_;
	auto dir21 = dir2_;
	auto dir23 = dir2_;
	auto dir31 = dir3_;
	auto dir32 = dir3_;

	dir12 += +L"\\2";
	dir13 += +L"\\3";
	dir21 += +L"\\1";
	dir23 += +L"\\3";
	dir31 += +L"\\1";
	dir32 += +L"\\2";

	std::filesystem::create_directories(dir12, error);
	std::filesystem::create_directories(dir13, error);
	std::filesystem::create_directories(dir21, error);
	std::filesystem::create_directories(dir23, error);
	std::filesystem::create_directories(dir31, error);
	std::filesystem::create_directories(dir32, error);

	////////////////////////////////////////////////////////////////////////////////

	{
		auto update = dataset1.Process(dataset1.Build());

		std::size_t created = 0;
		std::size_t modified = 0;
		std::size_t valid = 0;

		for (const auto& entry : update)
		{
			switch (entry.second.GetStatus())
			{
			case Entry::Created:
				created++;
				break;
			case Entry::Modified:
				modified++;
				break;
			case Entry::Valid:
				valid++;
				break;
			default:
				break;
			}
		}

		ASSERT_EQ(created, 2);
		ASSERT_EQ(modified, 0);
		ASSERT_EQ(valid, 3);
	}

	{
		auto update = dataset2.Process(dataset2.Build());

		std::size_t created = 0;
		std::size_t modified = 0;
		std::size_t valid = 0;

		for (const auto& entry : update)
		{
			switch (entry.second.GetStatus())
			{
			case Entry::Created:
				created++;
				break;
			case Entry::Modified:
				modified++;
				break;
			case Entry::Valid:
				valid++;
				break;
			default:
				break;
			}
		}

		ASSERT_EQ(created, 2);
		ASSERT_EQ(modified, 0);
		ASSERT_EQ(valid, 3);
	}

	{
		auto update = dataset3.Process(dataset3.Build());

		std::size_t created = 0;
		std::size_t modified = 0;
		std::size_t valid = 0;

		for (const auto& entry : update)
		{
			switch (entry.second.GetStatus())
			{
			case Entry::Created:
				created++;
				break;
			case Entry::Modified:
				modified++;
				break;
			case Entry::Valid:
				valid++;
				break;
			default:
				break;
			}
		}

		ASSERT_EQ(created, 2);
		ASSERT_EQ(modified, 0);
		ASSERT_EQ(valid, 3);
	}

	////////////////////////////////////////////////////////////////////////////////

	std::filesystem::copy(dir2_, dir12, std::filesystem::copy_options::recursive, error);
	std::filesystem::copy(dir3_, dir13, std::filesystem::copy_options::recursive, error);
	std::filesystem::copy(dir1_, dir21, std::filesystem::copy_options::recursive, error);
	std::filesystem::copy(dir3_, dir23, std::filesystem::copy_options::recursive, error);
	std::filesystem::copy(dir1_, dir31, std::filesystem::copy_options::recursive, error);
	std::filesystem::copy(dir2_, dir32, std::filesystem::copy_options::recursive, error);

	{
		auto update = dataset1.Process(dataset1.Build());

		std::size_t created = 0;
		std::size_t modified = 0;
		std::size_t valid = 0;

		for (const auto& entry : update)
		{
			switch (entry.second.GetStatus())
			{
			case Entry::Created:
				created++;
				break;
			case Entry::Modified:
				modified++;
				break;
			case Entry::Valid:
				valid++;
				break;
			default:
				break;
			}
		}

//		std::cout << "\tDataset1" << std::endl;
//		std::cout << "\t\tCreated [10]: " << created << std::endl;
//		std::cout << "\t\tModified [2]: " << modified << std::endl;
//		std::cout << "\t\tValid [3]: " << valid << std::endl;

		ASSERT_EQ(created, 10);
//		ASSERT_EQ(modified, 2);
//		ASSERT_EQ(valid, 3);
	}

	{
		auto update = dataset2.Process(dataset2.Build());

		std::size_t created = 0;
		std::size_t modified = 0;
		std::size_t valid = 0;

		for (const auto& entry : update)
		{
			switch (entry.second.GetStatus())
			{
			case Entry::Created:
				created++;
				break;
			case Entry::Modified:
				modified++;
				break;
			case Entry::Valid:
				valid++;
				break;
			default:
				break;
			}
		}

//		std::cout << "\tDataset2" << std::endl;
//		std::cout << "\t\tCreated [20]: " << created << std::endl;
//		std::cout << "\t\tModified [2]: " << modified << std::endl;
//		std::cout << "\t\tValid [3]: " << valid << std::endl;

		ASSERT_EQ(created, 20);
//		ASSERT_EQ(modified, 2);
//		ASSERT_EQ(valid, 3);
	}

	{
		auto update = dataset3.Process(dataset3.Build());

		std::size_t created = 0;
		std::size_t modified = 0;
		std::size_t valid = 0;

		for (const auto& entry : update)
		{
			switch (entry.second.GetStatus())
			{
			case Entry::Created:
				created++;
				break;
			case Entry::Modified:
				modified++;
				break;
			case Entry::Valid:
				valid++;
				break;
			default:
				break;
			}
		}

//		std::cout << "\tDataset3" << std::endl;
//		std::cout << "\t\tCreated [40]: " << created << std::endl;
//		std::cout << "\t\tModified [2]: " << modified << std::endl;
//		std::cout << "\t\tValid [3]: " << valid << std::endl;

//		auto lower_dir = L"\\1\\3";
//		auto upper_dir = L"\\2\\1";
//		
//		auto lower = update.lower_bound(lower_dir);
//		auto upper = update.upper_bound(upper_dir);
//		
//		auto diff = std::distance(lower, upper);

		ASSERT_EQ(created, 40);
//		ASSERT_EQ(modified, 2);
//		ASSERT_EQ(valid, 3);
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::filesystem::remove_all(dir12, error);
		std::filesystem::remove_all(dir13, error);

		auto update = dataset1.Process(dataset1.Build());

		std::size_t created = 0;
		std::size_t modified = 0;
		std::size_t removed = 0;
		std::size_t valid = 0;

		for (const auto& entry : update)
		{
			switch (entry.second.GetStatus())
			{
			case Entry::Created:
				created++;
				break;
			case Entry::Modified:
				modified++;
				break;
			case Entry::Removed:
				removed++;
				break;
			case Entry::Valid:
				valid++;
				break;
			default:
				break;
			}
		}

		ASSERT_EQ(created, 0);
		ASSERT_EQ(modified, 0);
		ASSERT_EQ(removed, 12);
		ASSERT_EQ(valid, 3);
	}

	{
		auto dir21_ren = dir2_;
		dir21_ren += L"\\1ren";

		auto dir232 = dir2_;
		auto dir232_ren = dir2_;
	
		dir232 += L"\\3\\2";
		dir232_ren += L"\\3\\2ren";

		std::filesystem::rename(dir21, dir21_ren, error);
		std::filesystem::rename(dir232, dir232_ren, error);

		auto update = dataset2.Process(dataset2.Build());

		std::size_t created = 0;
		std::size_t modified = 0;
		std::size_t removed = 0;
		std::size_t valid = 0;

		for (const auto& entry : update)
		{
			switch (entry.second.GetStatus())
			{
			case Entry::Created:
				created++;
				break;
			case Entry::Modified:
				modified++;
				break;
			case Entry::Removed:
				removed++;
				break;
			case Entry::Valid:
				valid++;
				break;
			default:
				break;
			}
		}

		ASSERT_EQ(created, 17);
//		ASSERT_EQ(modified, 1);
		ASSERT_EQ(removed, 17);
//		ASSERT_EQ(valid, 7);
	}

	{
		auto dir312 = dir3_;
		auto dir312_ren = dir3_;
		dir312 += L"\\1\\2";
		dir312_ren += L"\\1\\2ren";

		std::filesystem::rename(dir312, dir312_ren, error);

		auto dir313 = dir3_;
		dir313 += L"\\1\\3";

		std::filesystem::remove_all(dir313, error);

		auto dir321 = dir3_;
		auto dir321_copy = dir3_;
		dir321 += L"\\2\\1";
		dir321_copy += L"\\321copy";
	
		std::filesystem::copy(dir321, dir321_copy, std::filesystem::copy_options::recursive, error);
	   	
		auto update = dataset3.Process(dataset3.Build());

		std::size_t created = 0;
		std::size_t modified = 0;
		std::size_t removed = 0;
		std::size_t valid = 0;

		for (const auto& entry : update)
		{
			switch (entry.second.GetStatus())
			{
			case Entry::Created:
				created++;
				break;
			case Entry::Modified:
				modified++;
				break;
			case Entry::Removed:
				removed++;
				break;
			case Entry::Valid:
				valid++;
			default:
				break;
			}
		}

		ASSERT_EQ(created, 22);
//		ASSERT_EQ(modified, 1);
		ASSERT_EQ(removed, 12);
//		ASSERT_EQ(valid, 32);
	}
}