#include <iostream>
#include <fstream>

void writeNumber(const char* path, const int& number);
int readNumber(const char* path);

void writeCharacter(const char* path, const char& character);
char readCharacter(const char* path);

int main()
{
    int number;
    char character;

    std::cout << "Please enter a number: ";
    std::cin >> number;

    std::cout << "Please enter a character: ";
    std::cin >> character;

    writeNumber("Number.bin", number);
    writeCharacter("Character.bin", character);

    number = character = 0;

    number = readNumber("Number.bin");
    character = readCharacter("Character.bin");

    std::cout << "Num: " << number << ", Character: " << character << std::endl;

    number = readCharacter("Num.bin");     // Error (Doesn't exist)
    character = readCharacter("Char.bin"); // Error (Doesn't exist)
}

void writeNumber(const char* path, const int& number)
{
    std::ofstream outStream(path, std::ios::binary);

    if (outStream.is_open())
    {
        outStream.write(reinterpret_cast<const char*>(&number), sizeof(number));
        outStream.close();
    }
    else
    {
        std::cout << "Error opening " << path << "!" << std::endl;
    }
}

int readNumber(const char* path)
{
    int number = 0;
    std::ifstream inStream(path, std::ios::binary);

    if (inStream.is_open())
    {
        inStream.read(reinterpret_cast<char*>(&number), sizeof(number));
        inStream.close();
    }
    else if (!inStream.good())
    {
        std::cout << "The file " << path << " does not exist!" << std::endl;
    }

    return number;
}

void writeCharacter(const char* path, const char& character)
{
    std::ofstream outStream(path, std::ios::binary);

    if (outStream.is_open())
    {
        outStream.write(reinterpret_cast<const char*>(&character), sizeof(character));
        outStream.close();
    }
    else
    {
        std::cout << "Error opening " << path << "!" << std::endl;
    }
}

char readCharacter(const char* path)
{
    char character = 0;
    std::ifstream inStream(path, std::ios::binary);

    if (inStream.is_open())
    {
        inStream.read(reinterpret_cast<char*>(&character), sizeof(character));
        inStream.close();
    }
    else if (!inStream.good())
    {
        std::cout << "The file " << path << " does not exist!" << std::endl;
    }

    return character;
}