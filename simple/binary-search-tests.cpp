#include "pch.h"
#include "binary-search.h"

using namespace std;

TEST_CASE("Searching in an empty array returns an empty range")
{
	CHECK(BinarySearch({}, 0) == Range(0, 0));
	CHECK(BinarySearch({}, 42) == Range(0, 0));
}