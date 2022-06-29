#include <iostream>

template<typename Type>
bool ordered(const Type* arr, int n)
{
	for (int i = 1; i < n; i++)
	{
		if (arr[i - 1] >= arr[i])
			return false;
	}

	return true;
}

struct MyStruct
{
	int x = 0, y = 0;
};

int main()
{
	int orderedArr[] = { 1, 3, 4, 18, 29, 289 };
	int unorderedArr[] = { 3, 2, 1, 45, 23, 43 };
	MyStruct invalid[] = { {}, {}, {} };

	std::cout << std::boolalpha << ordered(orderedArr, sizeof(orderedArr) / sizeof(int)) << "\n";
	std::cout << std::boolalpha << ordered(unorderedArr, sizeof(orderedArr) / sizeof(int)) << std::endl;

	// std::cout << std::boolalpha << ordered(invalid, 3);	// Invalid because, it doesn't define a >= operator!
}