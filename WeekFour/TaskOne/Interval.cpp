#include "Interval.h"
#include "Utility.h"

#include <iostream>

using namespace Utility;

Interval::Interval()
	:_a(0), _b(0)
{}

Interval::Interval(const int& a, const int& b)
{
	if (a > b)
	{
		_a = 0;
		_b = 0;
	}
	else
	{
		_a = a;
		_b = b;
	}
}

Interval::~Interval() = default;

int Interval::Start() const
{
	return _a;
}

int Interval::End() const
{
	return _b;
}

void Interval::Print() const
{
	std::cout << "[" << _a << ", " << _b << "]" << std::endl;
}

int Interval::Length() const
{
	return _b - _a + 1;
}

bool Interval::IsPartOf(const int num) const
{
	return num >= _a && num <= _b;
}


int Interval::PrimeCount() const
{
	int count = 0;
	for (int i = _a; i <= _b; i++)
	{
		if (isPrime(i))
			count++;
	}

	return count;
}

int Interval::PalindromeCount() const
{
	int count = 0;
	for (int i = _a; i <= _b; i++)
	{
		if (reverseNum(i) == i)
			count++;
	}

	return count;
}

int Interval::NonRepeatingCount() const
{
	int count = 0;
	for (int i = _a; i <= _b; i++)
	{
		if (!hasRepeatingDigits(i))
			count++;
	}

	return count;
}

bool Interval::AreStartAndEndPowersOfTwo() const
{
	return isPowerOfTwo(_a) && isPowerOfTwo(_b);
}

Interval Interval::GetIntersection(const Interval& interval) const
{
	if (_b < interval.Start() || interval.End() < _a)
		return {};

	return Interval(max(_a, interval.Start()), min(_b, interval.End()));
}

bool Interval::IsSubInterval(const Interval& interval) const
{
	return _a <= interval.Start() && _b >= interval.End();
}