#include <iostream>
#include <fstream>

bool doesFileExist(const char* path);
void copyFileContents(const char* inputPath, const char* outputPath);

int main()
{
    char inputFile[128];
    char outputFile[128];

    std::cout << "Which file do you want to copy: ";

    do
    {
        std::cin >> inputFile;

        if (!doesFileExist(inputFile))
            std::cout << "This file does not exist! Please try again: ";

    } while (!doesFileExist(inputFile));

    std::cout << "What should we call the output file: ";
    std::cin >> outputFile;

    copyFileContents(inputFile, outputFile);
}

bool doesFileExist(const char* path)
{
    std::ifstream stream(path);
    bool status = stream.good();
    stream.close();

    return status;
}

void copyFileContents(const char* inputPath, const char* outputPath)
{
    std::fstream input(inputPath, std::ios::in | std::ios::app);
    std::fstream output(outputPath, std::ios::out | std::ios::trunc);

    if (!input.is_open() || !output.is_open())
    {
        std::cout << "Error opening a file! Please check if the files are in use and try again!" << std::endl;
        return;
    }

    char buff[256];

    while (!input.eof())
    {
        input.getline(buff, 256);
        output << buff;
        output.put('\n');
    }

    std::cout << "Done! Contents of " << inputPath << " are saved into " << outputPath << "!" << std::endl;

    input.close();
    output.close();
}