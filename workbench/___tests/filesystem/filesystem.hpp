#pragma once

#include "filesystem/dataset.hpp"

#include <algorithm>
#include <chrono>
#include <iterator>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <limits>
#include <random>
#include <thread>
#include <utility>

#include <gtest/gtest.h>

using namespace Mockup;
using namespace Mockup::Filesystem;

class Filesystem : public ::testing::Test
{
protected:
	void GenerateContent(const std::filesystem::path& path, std::uintmax_t size)
	{
		if (std::filesystem::exists(path) && std::filesystem::file_size(path) == size)
		{
			return;
		}

		std::mt19937 generator;
		std::uniform_int_distribution<> distribution('A', 'Z');

		std::string output;
		output.resize(size);

		std::generate(output.begin(), output.end(), [&]() { return (char)(distribution(generator)); });

		std::ofstream file(path.wstring(), std::ios::out | std::ios::binary);
		file.write(output.c_str(), output.size());
	}

	////////////////////////////////////////////////////////////////////////////////

	const std::filesystem::path path_ = std::filesystem::current_path() / L"test_bench";
	
	const std::filesystem::path dir1_ = path_ / L"test1";
	const std::filesystem::path dir2_ = path_ / L"test2";
	const std::filesystem::path dir3_ = path_ / L"test3";
	
	const std::filesystem::path entry11_ = dir1_ / L"sample11.bin";
	const std::filesystem::path entry12_ = dir1_ / L"sample12.bin";
	const std::filesystem::path entry13_ = dir1_ / L"sample13.bin";

	const std::filesystem::path entry21_ = dir2_ / L"sample21.bin";
	const std::filesystem::path entry22_ = dir2_ / L"sample22.bin";
	const std::filesystem::path entry23_ = dir2_ / L"sample23.bin";

	const std::filesystem::path entry31_ = dir3_ / L"sample31.bin";
	const std::filesystem::path entry32_ = dir3_ / L"sample32.bin";
	const std::filesystem::path entry33_ = dir3_ / L"sample33.bin";

	const std::uintmax_t size1_ = 100;
	const std::uintmax_t size2_ = 200;
	const std::uintmax_t size3_ = 300;

	const std::uintmax_t sizemod1_ = 100;
	const std::uintmax_t sizemod2_ = 200;
	const std::uintmax_t sizemod3_ = 300;


	Filesystem()
	{
#if defined(_DEBUG)  
		{
			auto flag = _CrtSetDbgFlag(_CRTDBG_REPORT_FLAG);

			flag |= _CRTDBG_ALLOC_MEM_DF;
			flag |= _CRTDBG_CHECK_ALWAYS_DF;
			flag |= _CRTDBG_LEAK_CHECK_DF;

			_CrtSetDbgFlag(flag);

			_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_DEBUG);
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
			_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_DEBUG);
		}
#endif
//		Windows::Foundation::Initialize(RO_INIT_MULTITHREADED);

		////////////////////////////////////////////////////////////////////////////////

		std::error_code error;

		std::filesystem::remove_all(dir1_, error);
		std::filesystem::remove_all(dir2_, error);
		std::filesystem::remove_all(dir3_, error);

		std::filesystem::create_directories(dir1_, error);
		std::filesystem::create_directories(dir2_, error);
		std::filesystem::create_directories(dir3_, error);

		GenerateContent(entry11_, (size1_ * size1_) + sizemod1_);
		GenerateContent(entry12_, (size1_ * size2_) + sizemod2_);
		GenerateContent(entry13_, (size1_ * size3_) + sizemod3_);
							
		GenerateContent(entry21_, (size2_ * size1_) + sizemod1_);
		GenerateContent(entry22_, (size2_ * size2_) + sizemod2_);
		GenerateContent(entry23_, (size2_ * size3_) + sizemod3_);
							
		GenerateContent(entry31_, (size3_ * size1_) + sizemod1_);
		GenerateContent(entry32_, (size3_ * size2_) + sizemod2_);
		GenerateContent(entry33_, (size3_ * size3_) + sizemod3_);

		////////////////////////////////////////////////////////////////////////////////
	}

	~Filesystem()
	{
//		Windows::Foundation::Uninitialize();
//		std::filesystem::remove_all(path_, error_);
	}

	void SetUp() override
	{	

	}

	void TearDown() override
	{

	}
};

