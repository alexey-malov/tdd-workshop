#include "pch.h"

#include "binary-search.h"

using namespace std;

size_t FindLowerBound(const vector<int>& items, size_t first, size_t last, int value)
{
	size_t count = last - first;
	while (count > 0) // Ищем пока диапазон не пуст
	{
		auto step = count / 2;
		auto mid = first + step;

		if (items[mid] < value) // Искомый элемент справа от mid?
		{
			// отбрасываем левую половину
			first = mid + 1;
			count -= step + 1;
		}
		else // Искомый элемент в позиции mid или правее
		{
			// отбрасываем правую половину
			count = step;
		}
	}
	return first;
}

size_t FindUpperBound(const vector<int>& items, size_t first, size_t last, int value)
{
	size_t count = last - first;
	while (count > 0) // Ищем пока диапазон не пуст
	{
		auto step = count / 2;
		auto mid = first + step;
		if (value < items[mid]) // искомый элемент слева от mid?
		{	// Отбрасываем правую половину
			count = step;
		}
		else // Искомый элемент в позиции mid или правее
		{	// Отбрасываем левую половину
			first = mid + 1;
			count -= step + 1;
		}
	}
	return first;
}

Range BinarySearch(const vector<int>& items, int value)
{
	size_t first = FindLowerBound(items, 0, items.size(), value);
	size_t last = FindUpperBound(items, first, items.size(), value);
	return { first, last };
}
