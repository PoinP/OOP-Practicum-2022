#ifndef INTERVAL_H

#define INTERVAL_H

class Interval
{
public:
	Interval();
	Interval(const int& a, const int& b);
	~Interval();

	int Start() const;
	int End() const;

	void Print() const;

	int Length() const;
	bool IsPartOf(const int num) const;
	int PrimeCount() const;
	int PalindromeCount() const;
	int NonRepeatingCount() const;
	bool AreStartAndEndPowersOfTwo() const;
	Interval GetIntersection(const Interval& interval) const;
	bool IsSubInterval(const Interval& interval) const;

private:
	int _a;
	int _b;
};

#endif
