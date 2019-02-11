#include "pch.h"

#include "binary-search.h"

using namespace std;

template <typename Predicate>
size_t FindBound(const vector<int>& items, size_t first, size_t last, Predicate isLess)
{
	size_t count = last - first;
	while (count > 0) // Ищем пока диапазон не пуст
	{
		auto step = count / 2;
		auto mid = first + step;

		if (isLess(items[mid])) // Искомый элемент справа от mid?
		{
			// отбрасываем левую половину
			first = mid + 1;
			count -= step + 1;
		}
		else // Искомый элемент в позиции mid или левее
		{
			// отбрасываем правую половину
			count = step;
		}
	}
	return first;
}

Range BinarySearch(const vector<int>& items, int value)
{
	size_t first = FindBound(items, 0, items.size(), [value](int current) {
		return current < value;
	});
	size_t last = FindBound(items, first, items.size(), [value](int current) {
		return current <= value;
	});
	return { first, last };
}
