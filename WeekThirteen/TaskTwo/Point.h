#ifndef POINT_H_INCLUDED

#define POINT_H_INCLUDED

#include <iostream>
#include <cmath>

template<typename Type>
class Point
{
public:
	Point();
	Point(Type x, Type y);

	bool operator< (const Point<Type>& other) const;
	bool operator> (const Point<Type>& other) const;
	bool operator== (const Point<Type>& other) const;

	const Type& getX() const;
	const Type& getY() const;

	void setX(const Type& x);
	void setY(const Type& y);

private:
	Type m_X{};
	Type m_Y{};
};

#endif // !POINT_H_INCLUDED

template<typename Type>
inline Point<Type>::Point()
{}

template<typename Type>
inline Point<Type>::Point(Type x, Type y)
	: m_X(x), m_Y(y)
{
}

template<typename Type>
inline bool Point<Type>::operator<(const Point<Type>& other) const
{
	return sqrt(m_X * m_X + m_Y * m_Y) < sqrt(other.m_X * other.m_X + other.m_Y * other.m_Y);
}

template<typename Type>
inline bool Point<Type>::operator>(const Point<Type>& other) const
{
	return other < *this;
}

template<typename Type>
inline bool Point<Type>::operator==(const Point<Type>& other) const
{
	return m_X == other.m_X && m_Y == other.m_Y;
}

template<typename Type>
inline const Type& Point<Type>::getX() const
{
	return m_X;
}

template<typename Type>
inline const Type& Point<Type>::getY() const
{
	return m_Y;
}

template<typename Type>
inline void Point<Type>::setX(const Type& x)
{
	m_X = x;
}

template<typename Type>
inline void Point<Type>::setY(const Type& y)
{
	m_Y = y;
}

template<typename Type>
inline std::ostream& operator<<(std::ostream& oStream, const Point<Type>& point)
{
	return oStream << "(" << point.getX() << ", " << point.getY() << ")";
}
