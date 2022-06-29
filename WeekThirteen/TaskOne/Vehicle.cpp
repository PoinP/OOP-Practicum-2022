#include "Vehicle.h"

Vehicle::Vehicle(unsigned speed, unsigned price, unsigned weight)
    : m_Speed(speed), m_Price(price), m_Weight(weight)
{
}

unsigned Vehicle::getSpeed() const
{
    return m_Speed;
}

unsigned Vehicle::getPrice() const
{
    return m_Price;
}

unsigned Vehicle::getWeight() const
{
    return m_Weight;
}

void Vehicle::setSpeed(unsigned speed)
{
    m_Speed = speed;
}

void Vehicle::setPrice(unsigned price)
{
    m_Price = price;
}

void Vehicle::setWeight(unsigned weight)
{
    m_Weight = weight;
}
