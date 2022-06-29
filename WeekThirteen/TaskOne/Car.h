#ifndef CAR_H_INCLUDED

#define CAR_H_INCLUDED

#include "Vehicle.h"

enum class CarType
{
	Unknown = -1,
	Pickup,
	Luxurious,
	Normal
};

class Car : public Vehicle
{
public:
	Car(unsigned speed, unsigned price, unsigned weight, const char* brand, const char* model, CarType type);
	Car(const Car& other);
	~Car();

	const char* getBrand() const;
	const char* getModel() const;
	CarType getType() const;
	const char* getTypeString() const;

	void print() const override;

private:
	char* m_Brand;
	char* m_Model;
	CarType m_Type;
};

#endif // !CAR_H_INCLUDED