#include <iostream>
#include <fstream>

const char PROGRAMS[4][32] =
{
    "Information Systems",
    "Software Engineering",
    "Informatics",
    "Computer Science"
};

enum Program
{
    INFORMATION_SYTEMS,
    SOFTWARE_ENGINEERING,
    INFORMATICS,
    COMPUTER_SCIENCE
};

struct Student
{
    char name[32];
    char facultyNumber[16];
    double averageGrade;
    Program program;
};

void writeStudentData(const char* path, const Student& student);
Student readStudentData(const char* path);
void printStudentInfo(const Student& student);

int main()
{
    const char* studentPath = "Student.bin";
    Student myStudent = { "Ivan Ivanov", "3MI0852635", 4.76, Program::INFORMATION_SYTEMS };

    writeStudentData(studentPath, myStudent);
    myStudent = {};
    myStudent = readStudentData(studentPath);

    printStudentInfo(myStudent);
}

void writeStudentData(const char* path, const Student& student)
{
    std::ofstream outStream(path, std::ios::binary);

    if (outStream.is_open())
    {
        outStream.write(reinterpret_cast<const char*>(&student), sizeof(student));
        std::cout << "Successfully written student's information to " << path << "!" << std::endl;
        outStream.close();
    }
    else
    {
        std::cout << "An error has occured while opening the file! No information has been written!" << std::endl;
    }
}

Student readStudentData(const char* path)
{
    Student student = {};

    std::ifstream inStream(path, std::ios::binary);

    if (inStream.is_open())
    {
        if (!inStream.read(reinterpret_cast<char*>(&student), sizeof(student)))
            std::cout << "Error reading student data from " << path << "!" << std::endl;

        inStream.close();
    }
    else
    {
        std::cout << "An error has occured while opening the file! No information has been written!" << std::endl;
    }

    return student;
}

void printStudentInfo(const Student& student)
{
    std::cout 
        << "\nName: " << student.name
        << "\nFaculty number: " << student.facultyNumber
        << "\nAverage grade: " << student.averageGrade
        << "\nProgram: " << PROGRAMS[student.program]
        << std::endl;
}