#pragma once

#include "parallel.hpp"

#include <algorithm>
#include <deque>
#include <limits>
#include <numeric>
#include <random>
#include <vector>

namespace Primitives
{
	constexpr std::size_t count = 1024;

	std::random_device device;
	std::mt19937 generator(device());
	std::uniform_int_distribution<> distribution(10, 20);
}