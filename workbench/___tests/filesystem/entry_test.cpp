#include "entry_test.hpp"

using namespace Primitives;

//	TEST_F(Filesystem, Entry_BasicEquality)
//	{
//		Entry entry11(entry11_);
//		Entry entry12(entry12_);
//		Entry entry13(entry13_);
//	
//		Entry entry_error1;
//		Entry entry_error2(L"x.x");
//	
//		Entry entry_move11(entry11);
//		Entry entry_move12(entry12);
//		Entry entry_move13(entry13);
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			auto result11_11 = entry11 == entry11;
//			auto result11_12 = entry11 == entry12;
//			auto result11_13 = entry11 == entry13;
//			auto result12_11 = entry12 == entry11;
//			auto result12_12 = entry12 == entry12;
//			auto result12_13 = entry12 == entry13;
//			auto result13_11 = entry13 == entry11;
//			auto result13_12 = entry13 == entry12;
//			auto result13_13 = entry13 == entry13;
//	
//			ASSERT_TRUE(result11_11);
//			ASSERT_FALSE(result11_12);
//			ASSERT_FALSE(result11_13);
//			ASSERT_FALSE(result12_11);
//			ASSERT_TRUE(result12_12);
//			ASSERT_FALSE(result12_13);
//			ASSERT_FALSE(result13_11);
//			ASSERT_FALSE(result13_12);
//			ASSERT_TRUE(result13_13);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			auto result11_error1 = entry11 == entry_error1;
//			auto result12_error1 = entry12 == entry_error1;
//			auto result13_error1 = entry13 == entry_error1;
//			auto result11_error2 = entry11 == entry_error2;
//			auto result12_error2 = entry12 == entry_error2;
//			auto result13_error2 = entry13 == entry_error2;
//	
//			ASSERT_FALSE(result11_error1);
//			ASSERT_FALSE(result12_error1);
//			ASSERT_FALSE(result13_error1);
//			ASSERT_FALSE(result11_error2);
//			ASSERT_FALSE(result12_error2);
//			ASSERT_FALSE(result13_error2);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			auto result11_move11 = entry11 == entry_move11;
//			auto result12_move11 = entry12 == entry_move11;
//			auto result13_move11 = entry13 == entry_move11;
//			auto result11_move12 = entry11 == entry_move12;
//			auto result12_move12 = entry12 == entry_move12;
//			auto result13_move12 = entry13 == entry_move12;
//			auto result11_move13 = entry11 == entry_move13;
//			auto result12_move13 = entry12 == entry_move13;
//			auto result13_move13 = entry13 == entry_move13;
//	
//			ASSERT_TRUE(result11_move11);
//			ASSERT_FALSE(result12_move11);
//			ASSERT_FALSE(result13_move11);
//			ASSERT_FALSE(result11_move12);
//			ASSERT_TRUE(result12_move12);
//			ASSERT_FALSE(result13_move12);
//			ASSERT_FALSE(result11_move13);
//			ASSERT_FALSE(result12_move13);
//			ASSERT_TRUE(result13_move13);
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			auto path_copy11 = entry11_;
//			auto path_copy12 = entry12_;
//			auto path_copy13 = entry13_;
//	
//			path_copy11 += L"_copy";
//			path_copy12 += L"_copy";
//			path_copy13 += L"_copy";
//	
//			std::error_code error;
//	
//			std::filesystem::copy_file(entry11_, path_copy11, std::filesystem::copy_options::update_existing, error);
//			std::filesystem::copy_file(entry12_, path_copy12, std::filesystem::copy_options::update_existing, error);
//			std::filesystem::copy_file(entry13_, path_copy13, std::filesystem::copy_options::update_existing, error);
//	
//			Entry entry_copy11(path_copy11);
//			Entry entry_copy12(path_copy12);
//			Entry entry_copy13(path_copy13);
//	
//			auto result11_copy11 = entry11 == entry_copy11;
//			auto result12_copy11 = entry12 == entry_copy11;
//			auto result13_copy11 = entry13 == entry_copy11;
//			auto result11_copy12 = entry11 == entry_copy12;
//			auto result12_copy12 = entry12 == entry_copy12;
//			auto result13_copy12 = entry13 == entry_copy12;
//			auto result11_copy13 = entry11 == entry_copy13;
//			auto result12_copy13 = entry12 == entry_copy13;
//			auto result13_copy13 = entry13 == entry_copy13;
//	
//			ASSERT_TRUE(result11_copy11);
//			ASSERT_FALSE(result12_copy11);
//			ASSERT_FALSE(result13_copy11);
//			ASSERT_FALSE(result11_copy12);
//			ASSERT_TRUE(result12_copy12);
//			ASSERT_FALSE(result13_copy12);
//			ASSERT_FALSE(result11_copy13);
//			ASSERT_FALSE(result12_copy13);
//			ASSERT_TRUE(result13_copy13);
//		}
//	}
//	
//	TEST_F(Filesystem, Entry_Equality)
//	{
//		std::error_code error;
//	
//		Entry entry11(entry11_);
//		Entry entry12(entry12_);
//		Entry entry13(entry13_);
//	
//		auto path_copy11 = entry11_;
//		auto path_copy12 = entry12_;
//		auto path_copy13 = entry13_;
//	
//		path_copy11 += L"_copy";
//		path_copy12 += L"_copy";
//		path_copy13 += L"_copy";
//	
//		std::filesystem::copy_file(entry11_, path_copy11, std::filesystem::copy_options::update_existing, error);
//		std::filesystem::copy_file(entry12_, path_copy12, std::filesystem::copy_options::update_existing, error);
//		std::filesystem::copy_file(entry13_, path_copy13, std::filesystem::copy_options::update_existing, error);
//	
//		Entry entry_copy11(path_copy11);
//		Entry entry_copy12(path_copy12);
//		Entry entry_copy13(path_copy13);
//	
//		auto path_mod11 = entry11_;
//		auto path_mod12 = entry12_;
//		auto path_mod13 = entry13_;
//	
//		path_mod11 += L"_mod";
//		path_mod12 += L"_mod";
//		path_mod13 += L"_mod";
//	
//		GenerateContent(path_mod11, size1_);
//		GenerateContent(path_mod12, size2_);
//		GenerateContent(path_mod13, size3_);
//	
//		Entry entry_mod11(path_mod11);
//		Entry entry_mod12(path_mod12);
//		Entry entry_mod13(path_mod13);
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		Entry entry_error1;
//		Entry entry_error2(L"x.x");
//	
//		ASSERT_EQ(Entry::Status::Unknown, entry_error1.GetStatus());
//		ASSERT_EQ(Entry::Status::Unknown, entry_error2.GetStatus());
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			auto result11_mod11 = entry11 == entry_mod11;
//			auto result12_mod11 = entry12 == entry_mod11;
//			auto result13_mod11 = entry13 == entry_mod11;
//			auto result11_mod12 = entry11 == entry_mod12;
//			auto result12_mod12 = entry12 == entry_mod12;
//			auto result13_mod12 = entry13 == entry_mod12;
//			auto result11_mod13 = entry11 == entry_mod13;
//			auto result12_mod13 = entry12 == entry_mod13;
//			auto result13_mod13 = entry13 == entry_mod13;
//	
//			ASSERT_FALSE(result11_mod11);
//			ASSERT_FALSE(result12_mod11);
//			ASSERT_FALSE(result13_mod11);
//			ASSERT_FALSE(result11_mod12);
//			ASSERT_FALSE(result12_mod12);
//			ASSERT_FALSE(result13_mod12);
//			ASSERT_FALSE(result11_mod13);
//			ASSERT_FALSE(result12_mod13);
//			ASSERT_FALSE(result13_mod13);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry13.GetStatus());
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_copy11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_copy12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_copy13.GetStatus());
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_mod11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod13.GetStatus());
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			auto time = std::filesystem::file_time_type::clock::now();
//	
//			std::filesystem::last_write_time(entry11_, time, error);
//			std::filesystem::last_write_time(entry12_, time, error);
//			std::filesystem::last_write_time(entry13_, time, error);
//	
//			auto result11_check11 = entry11 == entry_copy11;
//			auto result12_check12 = entry12 == entry_copy12;
//			auto result13_check13 = entry13 == entry_copy13;
//	
//			ASSERT_TRUE(result11_check11);
//			ASSERT_TRUE(result12_check12);
//			ASSERT_TRUE(result13_check13);
//	
//			Entry entry_time11(entry11_);
//			Entry entry_time12(entry12_);
//			Entry entry_time13(entry13_);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry13.GetStatus());
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_time11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_time12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_time13.GetStatus());
//	
//			auto result11_time11 = entry11 == entry_time11;
//			auto result12_time11 = entry12 == entry_time11;
//			auto result13_time11 = entry13 == entry_time11;
//			auto result11_time12 = entry11 == entry_time12;
//			auto result12_time12 = entry12 == entry_time12;
//			auto result13_time12 = entry13 == entry_time12;
//			auto result11_time13 = entry11 == entry_time13;
//			auto result12_time13 = entry12 == entry_time13;
//			auto result13_time13 = entry13 == entry_time13;
//	
//			ASSERT_FALSE(result11_time11);
//			ASSERT_FALSE(result12_time11);
//			ASSERT_FALSE(result13_time11);
//			ASSERT_FALSE(result11_time12);
//			ASSERT_FALSE(result12_time12);
//			ASSERT_FALSE(result13_time12);
//			ASSERT_FALSE(result11_time13);
//			ASSERT_FALSE(result12_time13);
//			ASSERT_FALSE(result13_time13);
//		}
//	}
//	
//	TEST_F(Filesystem, Entry_BasicStatus)
//	{
//		std::error_code error;
//	
//		Entry entry11(entry11_);
//		Entry entry12(entry12_);
//		Entry entry13(entry13_);
//	
//		auto path_copy11 = entry11_;
//		auto path_copy12 = entry12_;
//		auto path_copy13 = entry13_;
//	
//		path_copy11 += L"_copy";
//		path_copy12 += L"_copy";
//		path_copy13 += L"_copy";
//	
//		std::filesystem::copy_file(entry11_, path_copy11, std::filesystem::copy_options::update_existing, error);
//		std::filesystem::copy_file(entry12_, path_copy12, std::filesystem::copy_options::update_existing, error);
//		std::filesystem::copy_file(entry13_, path_copy13, std::filesystem::copy_options::update_existing, error);
//	
//		Entry entry_copy11(path_copy11);
//		Entry entry_copy12(path_copy12);
//		Entry entry_copy13(path_copy13);
//	
//		auto path_mod11 = entry11_;
//		auto path_mod12 = entry12_;
//		auto path_mod13 = entry13_;
//	
//		path_mod11 += L"_mod";
//		path_mod12 += L"_mod";
//		path_mod13 += L"_mod";
//	
//		GenerateContent(path_mod11, size1_);
//		GenerateContent(path_mod12, size2_);
//		GenerateContent(path_mod13, size3_);
//	
//		Entry entry_mod11(path_mod11);
//		Entry entry_mod12(path_mod12);
//		Entry entry_mod13(path_mod13);
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		Entry entry_error1;
//		Entry entry_error2(L"x.x");
//	
//		ASSERT_EQ(Entry::Status::Unknown, entry_error1.GetStatus());
//		ASSERT_EQ(Entry::Status::Unknown, entry_error2.GetStatus());
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			Entry entry_status11(entry11_);
//			Entry entry_status12(entry12_);
//			Entry entry_status13(entry13_);
//	
//			entry_status11.UpdateStatus(entry11);
//			entry_status12.UpdateStatus(entry12);
//			entry_status13.UpdateStatus(entry13);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_status11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_status12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_status13.GetStatus());
//	
//			entry_status11.UpdateStatus(entry11);
//			entry_status12.UpdateStatus(entry11);
//			entry_status13.UpdateStatus(entry11);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_status11.GetStatus());
//			ASSERT_EQ(Entry::Status::Error, entry_status12.GetStatus());
//			ASSERT_EQ(Entry::Status::Error, entry_status13.GetStatus());
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			Entry entry_status11(entry11_);
//			Entry entry_status12(entry12_);
//			Entry entry_status13(entry13_);
//	
//			entry_status11.UpdateStatus(entry_copy11);
//			entry_status12.UpdateStatus(entry_copy12);
//			entry_status13.UpdateStatus(entry_copy13);
//	
//			ASSERT_EQ(Entry::Status::Duplicated, entry_status11.GetStatus());
//			ASSERT_EQ(Entry::Status::Duplicated, entry_status12.GetStatus());
//			ASSERT_EQ(Entry::Status::Duplicated, entry_status13.GetStatus());
//	
//			entry_status11.UpdateStatus(entry11);
//			entry_status12.UpdateStatus(entry12);
//			entry_status13.UpdateStatus(entry13);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_status11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_status12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_status13.GetStatus());
//	
//			entry_status11.UpdateStatus(entry_copy11);
//			entry_status12.UpdateStatus(entry_copy12);
//			entry_status13.UpdateStatus(entry_copy13);
//	
//			ASSERT_EQ(Entry::Status::Duplicated, entry_status11.GetStatus());
//			ASSERT_EQ(Entry::Status::Duplicated, entry_status12.GetStatus());
//			ASSERT_EQ(Entry::Status::Duplicated, entry_status13.GetStatus());
//	
//			entry_status11.UpdateStatus(entry_copy11);
//			entry_status12.UpdateStatus(entry_copy12);
//			entry_status13.UpdateStatus(entry_copy13);
//	
//			ASSERT_EQ(Entry::Status::Duplicated, entry_status11.GetStatus());
//			ASSERT_EQ(Entry::Status::Duplicated, entry_status12.GetStatus());
//			ASSERT_EQ(Entry::Status::Duplicated, entry_status13.GetStatus());
//	
//			entry_status11.UpdateStatus(entry_status11);
//			entry_status12.UpdateStatus(entry_status12);
//			entry_status13.UpdateStatus(entry_status13);
//	
//			ASSERT_EQ(Entry::Status::Error, entry_status11.GetStatus());
//			ASSERT_EQ(Entry::Status::Error, entry_status12.GetStatus());
//			ASSERT_EQ(Entry::Status::Error, entry_status13.GetStatus());
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			ASSERT_EQ(Entry::Status::Valid, entry_copy11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_copy12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_copy13.GetStatus());
//	
//			entry_copy11.UpdateStatus(entry_copy11);
//			entry_copy12.UpdateStatus(entry_copy12);
//			entry_copy13.UpdateStatus(entry_copy13);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_copy11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_copy12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_copy13.GetStatus());
//	
//			auto path_ren11 = path_copy11;
//			auto path_ren12 = path_copy12;
//			auto path_ren13 = path_copy13;
//	
//			path_ren11 += L"_ren";
//			path_ren12 += L"_ren";
//			path_ren13 += L"_ren";
//	
//			std::filesystem::rename(path_copy11, path_ren11, error);
//			std::filesystem::rename(path_copy12, path_ren12, error);
//			std::filesystem::rename(path_copy13, path_ren13, error);
//	
//			entry_copy11.UpdateStatus(entry_copy11);
//			entry_copy12.UpdateStatus(entry_copy12);
//			entry_copy13.UpdateStatus(entry_copy13);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_copy11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_copy12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_copy13.GetStatus());
//	
//			Entry entry_status11(path_ren11);
//			Entry entry_status12(path_ren12);
//			Entry entry_status13(path_ren13);
//	
//			entry_copy11.UpdateStatus(entry_status11);
//			entry_copy12.UpdateStatus(entry_status12);
//			entry_copy13.UpdateStatus(entry_status13);
//	
//			ASSERT_EQ(Entry::Status::Renamed, entry_copy11.GetStatus());
//			ASSERT_EQ(Entry::Status::Renamed, entry_copy12.GetStatus());
//			ASSERT_EQ(Entry::Status::Renamed, entry_copy13.GetStatus());
//	
//			entry_copy11.UpdateStatus(entry_status11);
//			entry_copy12.UpdateStatus(entry_status12);
//			entry_copy13.UpdateStatus(entry_status13);
//	
//			ASSERT_EQ(Entry::Status::Renamed, entry_copy11.GetStatus());
//			ASSERT_EQ(Entry::Status::Renamed, entry_copy12.GetStatus());
//			ASSERT_EQ(Entry::Status::Renamed, entry_copy13.GetStatus());
//	
//			entry_copy11.UpdateStatus(entry_copy11);
//			entry_copy12.UpdateStatus(entry_copy12);
//			entry_copy13.UpdateStatus(entry_copy13);
//	
//			ASSERT_EQ(Entry::Status::Error, entry_copy11.GetStatus());
//			ASSERT_EQ(Entry::Status::Error, entry_copy12.GetStatus());
//			ASSERT_EQ(Entry::Status::Error, entry_copy13.GetStatus());
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			auto time = std::filesystem::file_time_type::clock::now();
//	
//			std::filesystem::last_write_time(path_mod11, time, error);
//			std::filesystem::last_write_time(path_mod12, time, error);
//			std::filesystem::last_write_time(path_mod13, time, error);
//		
//			Entry entry_status11(path_mod11);
//			Entry entry_status12(path_mod12);
//			Entry entry_status13(path_mod13);
//		
//			entry_mod11.UpdateStatus(entry_status11);
//			entry_mod12.UpdateStatus(entry_status12);
//			entry_mod13.UpdateStatus(entry_status13);
//		
//			ASSERT_EQ(Entry::Status::Modified, entry_mod11.GetStatus());
//			ASSERT_EQ(Entry::Status::Modified, entry_mod12.GetStatus());
//			ASSERT_EQ(Entry::Status::Modified, entry_mod13.GetStatus());
//	
//			entry_mod11.UpdateStatus(entry_status11);
//			entry_mod12.UpdateStatus(entry_status12);
//			entry_mod13.UpdateStatus(entry_status13);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_mod11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod13.GetStatus());
//	
//			entry_mod11.UpdateStatus(entry_status11);
//			entry_mod12.UpdateStatus(entry_status12);
//			entry_mod13.UpdateStatus(entry_status13);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_mod11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod12.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod13.GetStatus());
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	
//		{
//			std::filesystem::remove(path_mod11, error);
//			std::filesystem::remove(path_mod12, error);
//			std::filesystem::remove(path_mod13, error);
//	
//			Entry entry_status11(path_mod11);
//			Entry entry_status12(path_mod12);
//			Entry entry_status13(path_mod13);
//	
//			entry_mod11.UpdateStatus(entry_status11);
//			entry_mod12.UpdateStatus(entry_status12);
//			entry_mod13.UpdateStatus(entry_status13);
//	
//			ASSERT_EQ(Entry::Status::Removed, entry_mod11.GetStatus());
//			ASSERT_EQ(Entry::Status::Removed, entry_mod12.GetStatus());
//			ASSERT_EQ(Entry::Status::Removed, entry_mod13.GetStatus());
//	
//			GenerateContent(path_mod11, size1_);
//			GenerateContent(path_mod12, size2_);
//			GenerateContent(path_mod13, size3_);
//	
//			ASSERT_EQ(Entry::Status::Unknown, entry_status11.GetStatus());
//			ASSERT_EQ(Entry::Status::Unknown, entry_status12.GetStatus());
//			ASSERT_EQ(Entry::Status::Unknown, entry_status13.GetStatus());
//	
//			Entry entry_mod11post(path_mod11);
//			Entry entry_mod12post(path_mod12);
//			Entry entry_mod13post(path_mod13);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_mod11post.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod12post.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod13post.GetStatus());
//	
//			entry_mod11.UpdateStatus(entry_mod11post);
//			entry_mod12.UpdateStatus(entry_mod12post);
//			entry_mod13.UpdateStatus(entry_mod13post);
//	
//			ASSERT_EQ(Entry::Status::Error, entry_mod11.GetStatus());
//			ASSERT_EQ(Entry::Status::Error, entry_mod12.GetStatus());
//			ASSERT_EQ(Entry::Status::Error, entry_mod13.GetStatus());
//	
//			entry_mod11.UpdateStatus(entry_mod11post);
//			entry_mod12.UpdateStatus(entry_mod12post);
//			entry_mod13.UpdateStatus(entry_mod13post);
//	
//			ASSERT_EQ(Entry::Status::Valid, entry_mod11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod11.GetStatus());
//			ASSERT_EQ(Entry::Status::Valid, entry_mod11.GetStatus());
//		}
//	
//		////////////////////////////////////////////////////////////////////////////////
//	}