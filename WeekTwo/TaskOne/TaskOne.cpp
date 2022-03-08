#include <iostream>
#include <fstream>

int main()
{
    std::fstream stream("./TaskOne.cpp", std::ios::in | std::ios::app);

    if (!stream.is_open())
    {
        std::cout << "Error oppening source code!" << std::endl;
        return -1;
    }

    char buffer[256];

    while (!stream.eof())
    {
        stream.getline(buffer, 256);
        std::cout << buffer << std::endl;
    }

    stream.close();
}