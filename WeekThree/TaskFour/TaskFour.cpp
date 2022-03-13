#include <iostream>
#include <fstream>

const char* studentPath = "Students.bin";

struct Student
{
    int facultyNumber;
    int passedExams;
    int failedExams;
    double averageGrade;
};

const Student sampleData[20] = {
    { 45355265, 9, 0, 5.32 },
    { 76362737, 5, 4, 4.32 },
    { 66237289, 3, 6, 3.35 },
    { 26636278, 2, 7, 2.81 },
    { 77263677, 9, 0, 5.56 },
    { 66255516, 1, 8, 3.11 },
    { 66273778, 5, 4, 4.17 },
    { 66255517, 3, 6, 3.12 },
    { 66365518, 6, 3, 5.17 },
    { 88231788, 8, 1, 5.71 },
    { 66266377, 0, 9, 2.00 },
    { 77188283, 7, 2, 4.52 },
    { 66277812, 3, 6, 4.92 },
    { 77281872, 4, 5, 3.32 },
    { 88172772, 7, 2, 5.39 },
    { 66362667, 9, 0, 5.93 },
    { 66255517, 7, 2, 5.02 },
    { 27782137, 3, 6, 3.89 },
    { 62777367, 5, 4, 4.82 },
    { 77271882, 3, 6, 3.52 },
};

// Task Four
void writeStudentData(const char* path, const Student* students, const int& studentsAmount);
Student* loadStudentData(const char* path, int& studentsAmount);
void printStudents(const Student* students, const int& studentsAmount);
void swapStudents(Student& firstStudent, Student& secondStudent);
int* sortStudents(Student* students, const int& studentsAmount);
int getStudentsAmount(std::ifstream& input);
void printIntArray(const int* arr, const int& size);

// Task Six
void writeIndexesToFile(const char* path, const int* indexes, const int& indexCount);
int* getIndexes(const int& minGrade, const Student* students, const int studentsAmount, int& outSize);
int countStudents(const int& minGrade, const Student* students, const int studentsAmount);

int main()
{
    // Task Four
    writeStudentData(studentPath, sampleData, 20);

    int studentsAmount;
    Student* students = loadStudentData(studentPath, studentsAmount);

    if (!students)
    {
        std::cout << "No students have been read!" << std::endl;
        return -1;
    }

    // Task Six
    int minGrade = 4;
    int indexesSize;

    int* goodStudentsIndexes = getIndexes(minGrade, students, studentsAmount, indexesSize);

    std::cout << "Indexes: \n";
    printIntArray(goodStudentsIndexes, indexesSize);
    printStudents(students, studentsAmount);

    writeIndexesToFile("Indexes.bin", goodStudentsIndexes, indexesSize);

    delete[] goodStudentsIndexes;

    std::cout << std::endl;

    // Task Four
    int* sortedFacultyNumbers = sortStudents(students, studentsAmount);

    std::cout << "Sorted Faculty Numbers: \n";
    printIntArray(sortedFacultyNumbers, studentsAmount);
    printStudents(students, studentsAmount);

    delete[] students;
}

#pragma region Task Four

int* sortStudents(Student* students, const int& studentsAmount)
{
    int* facultyNumbers = new int[studentsAmount];

    for (int i = 0; i < studentsAmount; i++)
    {
        for (int j = i; j < studentsAmount; j++)
        {
            if (students[j].averageGrade > students[i].averageGrade)
                swapStudents(students[i], students[j]);
        }

        facultyNumbers[i] = students[i].facultyNumber;
    }

    return facultyNumbers;
}

void swapStudents(Student& firstStudent, Student& secondStudent)
{
    Student temp = firstStudent;
    firstStudent = secondStudent;
    secondStudent = temp;
}

void printStudents(const Student* students, const int& studentsAmount)
{
    for (int i = 0; i < studentsAmount; i++)
    {
        std::cout << students[i].averageGrade << " "
            << students[i].failedExams << " "
            << students[i].passedExams << " "
            << students[i].facultyNumber << "\n";
    }

    std::cout << std::endl;
}

void writeStudentData(const char* path, const Student* students, const int& studentsAmount)
{
    std::ofstream output(studentPath, std::ios::binary);

    if (!output.is_open())
    {
        std::cout << "An error occured opening the file! No information has been written!" << std::endl;
        return;
    }

    for (int i = 0; i < studentsAmount; i++)
    {
        output.write(reinterpret_cast<const char*>(&students[i]), sizeof(students[i]));
    }

    output.close();
}

Student* loadStudentData(const char* path, int& studentsAmount)
{
    std::ifstream input(studentPath, std::ios::binary | std::ios::ate);

    if (!input.is_open())
    {
        std::cout << "An error occured opening the file! No information has been read!" << std::endl;
        return nullptr;
    }

    studentsAmount = getStudentsAmount(input);

    if (studentsAmount == 0)
    {
        input.close();
        return nullptr;
    }

    Student* students = new Student[studentsAmount];

    for (int i = 0; i < studentsAmount; i++)
    {
        input.read(reinterpret_cast<char*>(&students[i]), sizeof(students[i]));
    }

    input.close();

    return students;
}

void printIntArray(const int * arr, const int& size)
{
    for (int i = 0; i < size; i++)
    {
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;
}

int getStudentsAmount(std::ifstream& input)
{
    int studentsAmount = 0;

    input.seekg(0, input.end);
    studentsAmount = input.tellg() / sizeof(Student);
    input.seekg(0, input.beg);

    return studentsAmount;
}

#pragma endregion

#pragma region Task Six

void writeIndexesToFile(const char* path, const int* indexes, const int& indexCount)
{
    std::ofstream output(path, std::ios::binary);

    if (!output.is_open())
    {
        std::cout << "Error opening file! No indexes have been saved!" << std::endl;
        return;
    }

    for (int i = 0; i < indexCount; i++)
    {
        output.write(reinterpret_cast<const char*>(&indexes[i]), sizeof(indexes[i]));
    }

    output.close();

    std::cout << "Indexes written to " << path << "!" << std::endl;
}

int* getIndexes(const int& minGrade, const Student* students, const int studentsAmount, int& outSize)
{
    outSize = countStudents(minGrade, students, studentsAmount);

    if (outSize == 0)
        return nullptr;

    int* indexes = new int[outSize];
    int currIndex = 0;

    for (int i = 0; i < studentsAmount && currIndex < outSize; i++)
    {
        if (students[i].averageGrade >= minGrade)
            indexes[currIndex++] = i;
    }

    return indexes;
}

int countStudents(const int& minGrade, const Student* students, const int studentsAmount)
{
    int studentsCount = 0;

    for (int i = 0; i < studentsAmount; i++)
    {
        if (students[i].averageGrade >= minGrade)
            studentsCount++;
    }

    return studentsCount;
}


#pragma endregion
