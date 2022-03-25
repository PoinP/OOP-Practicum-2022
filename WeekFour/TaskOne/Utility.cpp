#include "Utility.h"

bool Utility::isPrime(int num)
{
	for (int i = 2; i <= num / 2; i++)
	{
		if (num % i == 0)
			return false;
	}

	return true;
}

int Utility::reverseNum(int num)
{
	int newNum = 0;
	while (num != 0)
	{
		newNum = (newNum * 10) + (num % 10);
		num /= 10;
	}

	return newNum;
}

bool Utility::hasRepeatingDigits(int num)
{
	int digit = 0;
	int numCopy = 0;

	while (num != 0)
	{
		digit = num % 10;
		num /= 10;
		numCopy = num;
		while (numCopy != 0)
		{
			if (digit == numCopy % 10)
				return true;

			numCopy /= 10;
		}
	}

	return false;
}

bool Utility::isPowerOfTwo(const int& n)
{
	if (n <= 0)
		return false;

	if (n == 2)
		return true;

	if (n % 2 != 0)
		return false;

	return isPowerOfTwo(n / 2);
}

int Utility::max(const int& num1, const int& num2)
{
	return num1 >= num2 ? num1 : num2;
}

int Utility::min(const int& num1, const int& num2)
{
	return num1 <= num2 ? num1 : num2;
}
