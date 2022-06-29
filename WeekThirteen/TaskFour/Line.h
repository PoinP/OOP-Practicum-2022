#ifndef LINE_H_INCLUDED

#define LINE_H_INCLUDED

#include "Point.h"
#include <cmath>

template<typename Type>
class Line
{
public:
	Line();
	Line(Point<Type> pt1, Point<Type> pt2);

	bool operator> (const Line<Type>& other) const;
	bool operator< (const Line<Type>& other) const;
	bool operator== (const Line<Type>& other) const;

	const Point<Type>& getFirstPoint() const;
	const Point<Type>& getSecondPoint() const;

	void setFirstPoint(Point<Type> pt);
	void setSecondPoint(Point<Type> pt);

	double getLength() const;

private:
	Point<Type> m_FstPoint;
	Point<Type> m_SndPoint;

	Point<Type> calculateLineCoords() const;
};

template<typename Type>
std::ostream& operator<< (std::ostream& oStream, const Line<Type>& line);

#endif // !LINE_H_INCLUDED

template<typename Type>
inline Line<Type>::Line()
{}

template<typename Type>
inline Line<Type>::Line(Point<Type> pt1, Point<Type> pt2)
	: m_FstPoint(pt1), m_SndPoint(pt2)
{}

template<typename Type>
inline bool Line<Type>::operator>(const Line<Type>& other) const
{
	return getLength() > other.getLength();
}

template<typename Type>
inline bool Line<Type>::operator<(const Line<Type>& other) const
{
	return other < *this;
}

template<typename Type>
inline bool Line<Type>::operator==(const Line<Type>& other) const
{
	return getLength() == other.getLength();
}

template<typename Type>
inline const Point<Type>& Line<Type>::getFirstPoint() const
{
	return m_FstPoint;
}

template<typename Type>
inline const Point<Type>& Line<Type>::getSecondPoint() const
{
	return m_SndPoint;
}

template<typename Type>
inline void Line<Type>::setFirstPoint(Point<Type> pt)
{
	m_FstPoint = pt;
}

template<typename Type>
inline void Line<Type>::setSecondPoint(Point<Type> pt)
{
	m_SndPoint = pt;
}

template<typename Type>
inline double Line<Type>::getLength() const
{
	Point<Type> coords = calculateLineCoords();
	return sqrt(coords.getX() * coords.getX() + coords.getY() * coords.getY());
}

template<typename Type>
inline Point<Type> Line<Type>::calculateLineCoords() const
{
	return Point<Type>(m_SndPoint.getX() - m_FstPoint.getX(), m_SndPoint.getY() - m_FstPoint.getY());
}

template<typename Type>
inline std::ostream& operator<<(std::ostream& oStream, const Line<Type>& line)
{
	return oStream << "[" << line.getFirstPoint() << ", " << line.getSecondPoint() << "] - " << line.getLength();
}
