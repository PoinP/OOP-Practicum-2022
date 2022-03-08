#include <iostream>

const int DIVISIONS_COUNT = 4;
const char DIVISIONS[DIVISIONS_COUNT][10] =
{
	"Assassin",
	"Medic",
	"Mage",
	"Tank"
};

enum Division
{
	ASSASSIN,
	MEDIC,
	MAGE,
	TANK
};

const int COMBAT_TYPES_COUNT = 3;
const char COMBAT_TYPES[COMBAT_TYPES_COUNT][10] =
{
	"Range",
	"Melee",
	"Both"
};

enum Combat
{
	UNKNOWN = -1,
	RANGE,
	MELEE,
	BOTH,
};

struct Hero
{
	char name[32];
	Division division;
	Combat combat;
};

Hero initHero();
void printInfo(const Hero& hero);
void printSelector(const char types[][10], const int& amount);

int main()
{
	Hero myHero = initHero();
	printInfo(myHero);
	
	// Memory living in the stack gets disposed by itself when it gets out of scope
}

Hero initHero()
{
	Hero hero;

	std::cout << "Please enter your hero's name[max 32 chars.]: ";
	std::cin.getline(hero.name, 32);

	std::cout << std::endl;

	std::cout << "Please enter your hero's division: " << std::endl;
	printSelector(DIVISIONS, DIVISIONS_COUNT);

	int userInput;

	do
	{
		std::cin >> userInput;
		if (userInput <= 0 || userInput >= DIVISIONS_COUNT)
			std::cout << "The divison you entered is invalid! Try again: ";
	} while (userInput <= 0 || userInput >= DIVISIONS_COUNT);

	hero.division = (Division)userInput;
	std::cout << std::endl;

	std::cout << "Please enter your hero's combat type: " << std::endl;
	printSelector(COMBAT_TYPES, COMBAT_TYPES_COUNT);

	do
	{
		std::cin >> userInput;
		if (userInput <= Combat::UNKNOWN || userInput > Combat::BOTH)
			std::cout << "The combat type you entered is invalid! Try again: ";
	} while (userInput <= Combat::UNKNOWN || userInput > Combat::BOTH);

	hero.combat = (Combat)userInput;
	std::cout << std::endl;

	return hero;
}

void printInfo(const Hero& hero)
{
	std::cout << "Name: " << hero.name
		<< "\nDivison: " << DIVISIONS[hero.division]
		<< "\nCombat Type: " << COMBAT_TYPES[hero.combat]
		<< std::endl;
}

void printSelector(const char types[][10], const int& amount)
{
	for (int i = 0; i < amount; i++)
	{
		std::cout << i << ". " << types[i] << std::endl;
	}
}