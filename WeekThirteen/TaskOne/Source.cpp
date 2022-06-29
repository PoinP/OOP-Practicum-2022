#include <iostream>

#include "Plane.h"
#include "Car.h"
#include "Boat.h"

void printSpeedyBois(const Vehicle* const* vehicles, unsigned count);

int main()
{
	Car car1(190, 8300, 1900, "Volkswagen", "Golf Mk.5", CarType::Normal);
	Car car2(280, 100300, 2400, "Audi", "Q8", CarType::Luxurious);
	Car car3(230, 65300, 2700, "Ford", "F-150", CarType::Pickup);
	Plane plane(500, 230000, 8200, "Boeing", "330", 5000);
	Boat boat(100, 7000, 1200, "SmartBoat", "S-540", 120);

	Vehicle** vehicles = new Vehicle* [5];
	vehicles[0] = &car1;
	vehicles[1] = &car2;
	vehicles[2] = &plane;
	vehicles[3] = &boat;
	vehicles[4] = &car3;

	printSpeedyBois(vehicles, 5);

	delete[] vehicles;
}

void printSpeedyBois(const Vehicle* const* vehicles, unsigned count)
{
	for (int i = 0; i < 5; i++)
	{
		if (vehicles[i]->getSpeed() <= 200)
			continue;

		vehicles[i]->print();
		std::cout << std::endl;
	}
}