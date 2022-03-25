#include "Interval.h"

#include <iostream>

int main()
{
	Interval myInterval;
	myInterval.Print();

	myInterval = Interval(3, 1);
	myInterval.Print();

	myInterval = Interval(2, 16);
	myInterval.Print();

	std::cout << myInterval.Length() << std::endl;

	std::cout << std::boolalpha << myInterval.IsPartOf(3) << std::endl;

	std::cout << std::boolalpha << myInterval.IsPartOf(17) << std::endl;

	std::cout << myInterval.PrimeCount() << std::endl;

	std::cout << myInterval.PalindromeCount() << std::endl;

	std::cout << myInterval.NonRepeatingCount() << std::endl;

	std::cout << std::boolalpha << myInterval.AreStartAndEndPowersOfTwo() << std::endl;

	myInterval = Interval(1, 5);
	Interval intersection = myInterval.GetIntersection(Interval(3, 7));

	intersection.Print();

	std::cout << std::boolalpha << myInterval.IsSubInterval(Interval(2, 4)) << std::endl;
	std::cout << std::boolalpha << myInterval.IsSubInterval(Interval(2, 7)) << std::endl;
}