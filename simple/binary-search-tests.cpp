#include "pch.h"
#include "binary-search.h"

using namespace std;

TEST_CASE("Searching in an empty array returns an empty range")
{
	CHECK(BinarySearch({}, 0) == Range(0, 0));
	CHECK(BinarySearch({}, 42) == Range(0, 0));
}

TEST_CASE("Lower bound is an index of an item that is not less than searched")
{
	CHECK(BinarySearch({ 1, 3, 3, 3, 3 }, 3) == Range(1, 5));
	CHECK(BinarySearch({ 3, 3, 3, 3, 3, 3 }, 3) == Range(0, 6));
	CHECK(BinarySearch({ 1, 2, 3, 4, 4 }, 4) == Range(3, 5));
	CHECK(BinarySearch({ 1, 2, 3, 4, 5, 6 }, 6) == Range(5, 6));

	CHECK(BinarySearch({ 1, 2, 3, 4, 5, 6 }, 7) == Range(6, 6));
	CHECK(BinarySearch({ 1, 2, 3, 4, 5, 6 }, 10) == Range(6, 6));
}

TEST_CASE("Upper bound is an index of an item that is greater than the searched")
{
	CHECK(BinarySearch({ 1, 3, 3, 3, 3 }, 1) == Range(0, 1));
	CHECK(BinarySearch({ 1, 3, 3, 5, 8, 8 }, 8) == Range(4, 6));
	CHECK(BinarySearch({ 1, 3, 3, 5, 8, 8 }, 9) == Range(6, 6));
	CHECK(BinarySearch({ 1, 3, 4, 5, 8, 8 }, 5) == Range(3, 4));
	CHECK(BinarySearch({ 1, 3, 3, 5, 8, 8 }, 4) == Range(3, 3));
	CHECK(BinarySearch({ 1, 3, 3, 5, 8, 8 }, 0) == Range(0, 0));
}
