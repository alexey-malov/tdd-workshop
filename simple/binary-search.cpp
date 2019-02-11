#include "pch.h"

#include "binary-search.h"

using namespace std;

size_t FindLowerBound(const vector<int>& items, size_t first, size_t last, int value)
{
	ptrdiff_t count = last - first;

	while (count > 0) // ���� ���� �������� �� ����
	{
		auto step = count / 2;
		auto mid = first + step;

		if (items[mid] < value) // ������� ������� ������ �� mid?
		{
			// ����������� ����� ��������
			first = mid + 1;
			count -= step + 1;
		}
		else // ������� ������� � ������� mid ��� ������
		{
			// ����������� ������ ��������
			count = step;
		}
	}
	return first;
}

Range BinarySearch(const vector<int>& items, int value)
{
	size_t last = items.size();
	size_t first = FindLowerBound(items, 0, last, value);

	return { first, last };
}
