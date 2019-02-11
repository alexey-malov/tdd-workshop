#include "pch.h"
#include "binary-search.h"

using namespace std;

Range BinarySearch(const vector<int>& items, int value)
{
	size_t first = 0;
	size_t last = items.size();
	ptrdiff_t count = last - first;

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

	return { first, last };
}
