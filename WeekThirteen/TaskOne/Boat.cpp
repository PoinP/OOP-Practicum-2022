#define _CRT_SECURE_NO_WARNINGS

#include "Boat.h"

#include <cstring>
#include <iostream>

Boat::Boat(unsigned speed, unsigned price, unsigned weight, const char* brand, const char* model, unsigned waterDispl)
    : Vehicle(speed, price, weight), m_WaterDispl(waterDispl),
    m_Brand(strcpy(new char[strlen(brand) + 1], brand)),
    m_Model(strcpy(new char[strlen(model) + 1], model))
{
}

Boat::Boat(const Boat& other)
    : Vehicle(other), m_WaterDispl(other.m_WaterDispl),
    m_Brand(strcpy(new char[strlen(other.m_Brand) + 1], other.m_Brand)),
    m_Model(strcpy(new char[strlen(other.m_Model) + 1], other.m_Model))
{
}

Boat::~Boat()
{
    delete[] m_Brand;
    delete[] m_Model;
}

const char* Boat::getBrand() const
{
    return m_Brand;
}

const char* Boat::getModel() const
{
    return m_Model;
}

unsigned Boat::getWaterDisplacement() const
{
    return m_WaterDispl;
}

void Boat::print() const
{
    std::cout << m_Brand << " " << m_Model << " [Boat]: \n"
        << "Speed: " << getSpeed() << "km/h\n"
        << "Weight: " << getWeight() << "kg\n"
        << "Water Displacement: " << m_WaterDispl << "l\n"
        << "Price: " << getPrice() << "BGN" << std::endl;
}
