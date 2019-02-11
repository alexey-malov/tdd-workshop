#pragma once
#include <vector>
#include <utility>

using Range = std::pair<size_t, size_t>;
Range BinarySearch(const std::vector<int>& items, int value);