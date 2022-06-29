#define _CRT_SECURE_NO_WARNINGS

#include "Car.h"

#include <cstring>
#include <iostream>

static const char* CAR_TYPE_STRING[] = { "Pickup", "Luxurious", "Normal" };

Car::Car(unsigned speed, unsigned price, unsigned weight, const char* brand, const char* model, CarType type)
    : Vehicle(speed, price, weight), m_Type(type),
      m_Brand(strcpy(new char[strlen(brand) + 1], brand)),
      m_Model(strcpy(new char[strlen(model) + 1], model))
{
}

Car::Car(const Car& other)
    : Vehicle(other), m_Type(other.m_Type),
    m_Brand(strcpy(new char[strlen(other.m_Brand) + 1], other.m_Brand)),
    m_Model(strcpy(new char[strlen(other.m_Model) + 1], other.m_Model))
{}

Car::~Car()
{
    delete[] m_Brand;
    delete[] m_Model;
}

const char* Car::getBrand() const
{
    return m_Brand;
}

const char* Car::getModel() const
{
    return m_Model;
}

CarType Car::getType() const
{
    return m_Type;
}

const char* Car::getTypeString() const
{
    return CAR_TYPE_STRING[(int)m_Type];
}

void Car::print() const
{
    std::cout << m_Brand << " " << m_Model << " [Car]: \n"
        << "Speed: " << getSpeed() << "km/h\n"
        << "Weight: " << getWeight() << "kg\n"
        << "Type: " << getTypeString() << "\n"
        << "Price: " << getPrice() << "BGN" << std::endl;
}
