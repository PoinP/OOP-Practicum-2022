#include <iostream>
#include <fstream>

// Task Three
void formatString(char* string);
void writeString(const char* path, const char* string);

// Task Five
char* readString(const char* path);
int getStringLength(const char* string);

void writeDigitsPos(const char* path, const char* sourceString);
int getLastDigitPos(const char* path);

bool isDigit(char symbol);
void strcpy_safe(char* destination, const char* source, const int& size);

int main()
{
	// Task Three
	char userInput[128];

	std::cout << "Please enter a string: ";
	std::cin.getline(userInput, 128);

	formatString(userInput);

	writeString("String.bin", userInput);

	// Task Five

	char* newString = readString("String.bin");
	
	writeDigitsPos("DigitPos.bin", newString);
	int pos = getLastDigitPos("DigitPos.bin");

	std::cout << "The last position of a digit is " << pos << std::endl;

	delete[] newString;
}

#pragma region Task Three

void formatString(char* string)
{
	while (*string != '\0')
	{
		if (*string >= 'a' && *string <= 'z')
			*string -= 'a' - 'A';

		string++;
	}
}

void writeString(const char* path, const char* string)
{
	int strLen = getStringLength(string) + 1;

	std::ofstream outStream(path, std::ios::binary);

	if (outStream.is_open())
	{
		outStream.write(string, strLen);
		std::cout << "String successfully written to " << path << "!" << std::endl;
		outStream.close();
	}
}

#pragma endregion

#pragma region Task Five

char* readString(const char* path)
{
	char* string = nullptr;
	std::ifstream inStream(path, std::ios::binary);

	if (inStream.is_open())
	{
		char buffer[256];

		inStream.getline(buffer, 256, '\0');
		int buffLen = getStringLength(buffer) + 1;

		string = new char[buffLen];

		strcpy_safe(string, buffer, buffLen);

		inStream.close();
	}
	else
	{
		std::cout << "The file " << path << " does not exist!" << std::endl;
	}

	return string;
}

int getStringLength(const char* string)
{
	int length = 0;

	while (*string != '\0')
	{
		length++;
		string++;
	}

	return length;
}

void writeDigitsPos(const char* path, const char* sourceString)
{
	std::ofstream outStream(path, std::ios::binary);

	if (outStream.is_open())
	{
		for (int i = 0; sourceString[i] != '\0'; i++)
		{
			if (isDigit(sourceString[i]))
				outStream.write(reinterpret_cast<const char*>(&i), sizeof(i));
		}

		std::cout << "Digits' postions saved to " << path << "!" << std::endl;
		outStream.close();
	}
}

int getLastDigitPos(const char* path)
{
	std::ifstream inStream(path, std::ios::binary);

	int pos = -1;

	if (inStream.is_open())
	{
		inStream.seekg(-(int)(sizeof(pos)), inStream.end);
		inStream.read(reinterpret_cast<char*>(&pos), sizeof(pos));
		inStream.close();
	}
	else
	{
		std::cout << "The file " << path << " does not exist!" << std::endl;
	}

	return pos;
}

void strcpy_safe(char* destination, const char* source, const int& size)
{
	int i;
	for (i = 0; source[i] != '\0' && i < size - 1; i++)
	{
		destination[i] = source[i];
	}

	destination[i] = '\0';
}

bool isDigit(char symbol)
{
	return symbol >= '0' && symbol <= '9';
}

#pragma endregion
