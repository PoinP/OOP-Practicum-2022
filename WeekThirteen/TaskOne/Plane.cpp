#define _CRT_SECURE_NO_WARNINGS

#include "Plane.h"

#include <iostream>
#include <cstring>

Plane::Plane(unsigned speed, unsigned price, unsigned weight, const char* brand, const char* model, unsigned maxAltitude)
	: Vehicle(speed, price, weight), m_MaxAlt(maxAltitude),
	m_Brand(strcpy(new char[strlen(brand) + 1], brand)),
	m_Model(strcpy(new char[strlen(model) + 1], model))
{
}

Plane::Plane(const Plane& other)
	: Vehicle(other), m_MaxAlt(other.m_MaxAlt),
	  m_Brand(strcpy(new char[strlen(other.m_Brand) + 1], other.m_Brand)),
	  m_Model(strcpy(new char[strlen(other.m_Model) + 1], other.m_Model))
{}

Plane::~Plane()
{
	delete[] m_Brand;
	delete[] m_Model;
}

Plane& Plane::operator=(const Plane& other)
{
	if (this != &other)
	{
		delete[] m_Brand;
		delete[] m_Model;

		this->Vehicle::operator=(other);
		m_MaxAlt = other.m_MaxAlt;
		m_Brand = strcpy(new char[strlen(other.m_Brand) + 1], other.m_Brand);
		m_Model = strcpy(new char[strlen(other.m_Model) + 1], other.m_Model);
	}

	return *this;
}

unsigned Plane::getMaxAltitude() const
{
	return m_MaxAlt;
}

const char* Plane::getBrand() const
{
	return m_Brand;
}

const char* Plane::getModel() const
{
	return m_Model;
}

void Plane::print() const
{
	std::cout << m_Brand << " " << m_Model << " [Plane]: \n"
		<< "Speed: " << getSpeed() << "km/h\n"
		<< "Weight: " << getWeight() << "kg\n"
		<< "Max Altitude: " << m_MaxAlt << "m\n"
		<< "Price: " << getPrice() << "BGN" << std::endl;
}