#include <iostream>
#include <fstream>

struct Point
{
    int x, y;
};

Point readPoint(const char* path);
void writePoint(const char* path, const Point& coords);

int main()
{
    Point point;
    char filePath[32];

    std::cout << "Please enter coordinates x and y: ";
    std::cin >> point.x >> point.y;

    std::cout << "Please enter a path to save the coordinates: ";
    std::cin >> filePath;

    writePoint(filePath, point);

    point.x = point.y = 0;

    point = readPoint(filePath);

    std::cout << "X: " << point.x << ", Y: " << point.y << std::endl;
}

void writePoint(const char* path, const Point& coords)
{
    std::ofstream outStream(path, std::ios::binary);

    if (outStream.is_open())
    {
        outStream.write(reinterpret_cast<const char*>(&coords), sizeof(coords));
        std::cout << "Coordinates successfully written to " << path << "!" << std::endl;
        outStream.close();
    }
    else
    {
        std::cout << "Error opening " << path << "!" << std::endl;
    }
}

Point readPoint(const char* path)
{
    Point coords = { 0, 0 };
    std::ifstream inStream(path, std::ios::binary);

    if (inStream.is_open())
    {
        inStream.read(reinterpret_cast<char*>(&coords), sizeof(coords));
        inStream.close();
    }
    else if (!inStream.good())
    {
        std::cout << "The file " << path << " does not exist!" << std::endl;
    }

    return coords;
}