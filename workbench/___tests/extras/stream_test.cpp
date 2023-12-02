#include "stream_test.hpp"

#include <array>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <limits>
#include <random>
#include <sstream>
#include <string>
#include <utility>

using namespace Primitives;

TEST_F(Extras, Stream_Simple)
{
	std::string simple_file = "simple.test";
	std::string empty_file = "empty.test";

	std::size_t size = 1 << 10;

	////////////////////////////////////////////////////////////////////////////////

	std::mt19937 generator;
	std::uniform_int_distribution<> distribution('A', 'Z');

	std::string output;
	output.resize(size);

	std::generate(output.begin(), output.end(), [&]() { return (char)(distribution(generator)); });

	if (!std::filesystem::exists(simple_file))
	{
		std::ofstream file(simple_file, std::ios::out | std::ios::binary);
		file.write(output.c_str(), output.size());
	}

	if (!std::filesystem::exists(empty_file))
	{
		std::ofstream file(empty_file, std::ios::out | std::ios::binary);
	}

	////////////////////////////////////////////////////////////////////////////////

	{
		std::ifstream file(simple_file, std::ios::in | std::ios::binary);
		auto result = ReadStream<std::string>(file);

		ASSERT_EQ(size, result.size());
		ASSERT_TRUE(result == output);
	}

	{
		std::ifstream file(empty_file, std::ios::in | std::ios::binary);
		auto result = ReadStream<std::string>(file);

		ASSERT_TRUE(result.empty());
	}

	{
		std::ifstream file("failure", std::ios::in | std::ios::binary);
		auto result = ReadStream<std::string>(file);

		ASSERT_TRUE(result.empty());
	}

	{
		std::ifstream file(simple_file, std::ios::in | std::ios::binary);
		file.seekg(size >> 1);

		auto result = ReadStream<std::string>(file);

		ASSERT_EQ(size >> 1, result.size());
		ASSERT_EQ(result, output.substr(size >> 1, size >> 1));
	}

	{
		std::ifstream file(simple_file, std::ios::in | std::ios::binary);
		file.seekg(size);

		auto result = ReadStream<std::string>(file);

		ASSERT_TRUE(result.empty());
	}
}

////////////////////////////////////////////////////////////////////////////////

TEST_F(Extras, Stream_Allocators)
{
	std::string simple_file = "simple.test";
	ASSERT_TRUE(std::filesystem::exists(simple_file));

	const std::size_t size = 1 << 10;

	////////////////////////////////////////////////////////////////////////////////

	std::mt19937 generator;
	std::uniform_int_distribution<> distribution('A', 'Z');

	std::string output;
	output.resize(size);

	std::generate(output.begin(), output.end(), [&]() { return (char)(distribution(generator)); });

	////////////////////////////////////////////////////////////////////////////////

	{
		std::ifstream file(simple_file, std::ios::in | std::ios::binary);
		auto result = ReadStream<std::vector<char>>(file);

		ASSERT_EQ(size, result.size());
		ASSERT_TRUE(output.compare(0, size, result.data()));
	}
}