#include <iostream>
#include "Line.h"

template<typename Type>
bool member(const Type* arr, int n, const Type& x)
{
	for (int i = 0; i < n; i++)
	{
		if (arr[i] == x)
			return true;
	}

	return false;
}

int main()
{
	int arr[] = { 1, 2, 3, 4, 5, 6, 78, 8, 9, 10 };
	
	std::cout << std::boolalpha << member(arr, sizeof(arr) / sizeof(int), 78) << "\n";
	std::cout << std::boolalpha << member(arr, sizeof(arr) / sizeof(int), 129) << std::endl;

	Point<int> pt1(3, 4);
	Point<int> pt2(9, 2);
	Line<int> line(pt1, pt2);

	std::cout << line;
}