#ifndef BOAT_H_INCLUDED

#define BOAT_H_INCLUDED

#include "Vehicle.h"

class Boat : public Vehicle
{
public:
	Boat(unsigned speed, unsigned price, unsigned weight, const char* brand, const char* model, unsigned waterDispl);
	Boat(const Boat& other);
	~Boat();

	const char* getBrand() const;
	const char* getModel() const;
	unsigned getWaterDisplacement() const;

	void print() const override;

private:
	char* m_Brand;
	char* m_Model;
	unsigned m_WaterDispl; // Water Displacement
};

#endif // !BOAT_H_INCLUDED