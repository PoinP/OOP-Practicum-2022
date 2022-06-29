#ifndef VEHICLE_H_INCLUDED

#define VEHICLE_H_INCLUDED

class Vehicle
{
public:
	Vehicle(unsigned speed, unsigned price, unsigned weight);

	unsigned getSpeed() const;
	unsigned getPrice() const;
	unsigned getWeight() const;

	virtual void print() const = 0;

protected:
	void setSpeed(unsigned speed);
	void setPrice(unsigned price);
	void setWeight(unsigned weight);

private:
	unsigned m_Speed;
	unsigned m_Price;
	unsigned m_Weight;
};

#endif // !VEHICLE_H_INCLUDED