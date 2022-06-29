#include <iostream>
#include "Point.h"

template<typename Type>
void swap(Type& x, Type& y)
{
	Type temp = x;
	x = y;
	y = temp;
}

template<typename Type, unsigned size>
unsigned indexMax(const Type* arr)
{
	Type max = arr[0];
	unsigned index = 0;

	for (int i = 1; i < size; i++)
	{
		if (arr[i] > max)
		{
			max = arr[i];
			index = i;
		}
	}

	return index;
}

template<typename Type, unsigned size>
unsigned indexMin(const Type* arr)
{
	Type min = arr[0];
	unsigned index = 0;

	for (int i = 1; i < size; i++)
	{
		if (arr[i] < min)
		{
			min = arr[i];
			index = i;
		}
	}

	return index;
}

template<typename Type, unsigned size>
Type* getSwapped(const Type* arr)
{
	unsigned maxIndex = indexMax<Type, size>(arr);
	unsigned minIndex = indexMin<Type, size>(arr);
	
	Type* swappedArray = new Type[size];

	for (int i = 0; i < size; i++)
	{
		if (i == maxIndex)
			swappedArray[i] = arr[minIndex];
		else if (i == minIndex)
			swappedArray[i] = arr[maxIndex];
		else
			swappedArray[i] = arr[i];
	}

	return swappedArray;
}

int main()
{
	// Part 1

	int myArray[10] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };

	int* swappedArray = getSwapped<int, 10>(myArray);

	for (int i = 0; i < 10; i++)
	{
		std::cout << swappedArray[i] << " ";
	}

	std::cout << std::endl;

	delete[] swappedArray;

	// Part 2
	Point<int> point(2, 3);
	std::cout << point;
}