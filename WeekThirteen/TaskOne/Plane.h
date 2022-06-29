#ifndef PLANE_H_INCLUDED

#define PLANE_H_INCLUDED

#include "Vehicle.h"

class Plane : public Vehicle
{
public:
	Plane(unsigned speed, unsigned price, unsigned weight, const char* brand, const char* model, unsigned maxAltitude);
	Plane(const Plane& other);
	~Plane();

	Plane& operator= (const Plane& other);

	unsigned getMaxAltitude() const;
	const char* getBrand() const;
	const char* getModel() const;

	void print() const override;

private:
	char* m_Brand;
	char* m_Model;
	unsigned m_MaxAlt; // Max Altitude
};

#endif // !PLANE_H_INCLUDED