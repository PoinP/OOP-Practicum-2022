#include <iostream>

const int SUBJECTS_COUNT = 7;
const char SUBJECTS[SUBJECTS_COUNT][32]
{
    "Geometry",
    "Object Oriented Programming",
    "Functional Programming",
    "Calculus 2",
    "Algebra",
    "Calculus",
    "Managing Information Systems"
};

enum Subjects : int
{
    GEOMETRY,
    OOP,
    FUNCTIONAL_POGRAMMING,
    CALCULUS_2,
    ALGEBRA,
    CALCULUS,
    MIS,

    UNKNOWN
};

struct Subject
{
    const char* name;
    double grade;
};

struct Student
{
    char name[64];
    char facultyNumber[16];
    Subject subjects[SUBJECTS_COUNT];
    int grades;
};

Student initStudent();
void addGrade(Student& student, Subjects subject, const double& grade);
void sortGrades(Student& student);

double calculateAvarage(const Student& student, const bool& includeFailedExams);

int getFailedExams(const Student& student);

bool canStudentAdvance(const Student& student);
bool canGetScholarship(const Student& student);

void printMenu();
void printStudentInfo(const Student& student);
void printGrades(const Student& student);
void addGradeMenu(Student& student);

int main()
{
    Student myStudent = initStudent();

    int userInput;
    do
    {
        printMenu();
        std::cin >> userInput;

        switch (userInput)
        {
        case 1:
            printStudentInfo(myStudent);
            break;
        case 2:
            printGrades(myStudent);
            break;
        case 3:
            addGradeMenu(myStudent);
            break;
        case 4:
            sortGrades(myStudent);
            std::cout << "Grades are sorted!" << std::endl;
            break;
        case 5:
            bool includeFailedExams;
            std::cout << "Do you want to include the failed exams[1(Yes) or 0(No)]: ";
            std::cin >> includeFailedExams;
            std::cout << "Average grade: " << calculateAvarage(myStudent, includeFailedExams) << std::endl;
            break;
        case 6:
            std::cout << "Can student advance: " << std::boolalpha << canStudentAdvance(myStudent) << std::endl;
            break;
        case 7:
            std::cout << "Can student recieve scholarship: " << std::boolalpha << canGetScholarship(myStudent) << std::endl;
            break;
        case 9:
            return 0;
        default:
            std::cout << "Invalid input!" << std::endl;
            break;
        }
    } while (userInput != 9);

    sortGrades(myStudent);
}

Student initStudent()
{
    Student student;

    std::cout << "Please enter the student's name: ";
    std::cin.getline(student.name, 64);
    //std::cin.ignore();

    std::cout << "Please enter the student's faculty number: ";
    std::cin >> student.facultyNumber;

    for (int i = 0; i < SUBJECTS_COUNT; i++)
    {
        Subject subject = { SUBJECTS[i], 0 };
        student.subjects[i] = subject;
    }

    student.grades = 0;

    return student;
}

void addGrade(Student& student, Subjects subject, const double& grade)
{
    if (subject < 0 || subject >= Subjects::UNKNOWN)
    {
        std::cout << "Unknown subject!" << std::endl;
        return;
    }

    if (grade < 2 || grade > 6)
    {
        std::cout << "Invalid grade!" << std::endl;
        return;
    }

    if(student.subjects[subject].grade == 0)
        student.grades++;

    student.subjects[subject].grade = grade;
}

void sortGrades(Student& student)
{
    for (int i = 0; i < SUBJECTS_COUNT; i++)
    {
        for (int j = 1; j < SUBJECTS_COUNT; j++)
        {
            if (student.subjects[j - 1].grade < student.subjects[j].grade)
            {
                Subject tempSubject = student.subjects[j - 1];
                student.subjects[j - 1] = student.subjects[j];
                student.subjects[j] = tempSubject;
            }
        }
    }
}

double calculateAvarage(const Student& student, const bool& includeFailedExams)
{
    double averageGrade = 0;
    double currentGrade = 0;
    int gradeCount = student.grades;

    for (int i = 0; i < SUBJECTS_COUNT; i++)
    {
        currentGrade = student.subjects[i].grade;

        if (currentGrade != 0)
        {
            if (currentGrade < 3 && !includeFailedExams)
            {
                gradeCount--;
                continue;
            }

            averageGrade += currentGrade;
        }
    }

    return averageGrade / gradeCount;
}

int getFailedExams(const Student& student)
{
    int failedExams = 0;

    for (int i = 0; i < SUBJECTS_COUNT; i++)
    {
        if (student.subjects[i].grade < 3)
            failedExams++;
    }

    return failedExams;
}

bool canStudentAdvance(const Student& student)
{
    int failedExams = getFailedExams(student);

    if (failedExams > 4)
        return false;

    bool includeFailedExams = true;
    if (failedExams < 4 || (failedExams == 4 && calculateAvarage(student, includeFailedExams) >= 4))
        return true;

    return false;
}

bool canGetScholarship(const Student& student)
{
    bool includeFailedExams = true;
    double averageGrades = calculateAvarage(student, includeFailedExams);
    int failedExams = getFailedExams(student);

    return averageGrades > 5 && failedExams == 0;
}

void printMenu()
{
    std::cout << std::endl;
    std::cout << "What would you like to do: \n";
    std::cout << "1. Show student info\n"
        << "2. Print grades\n"
        << "3. Add a grade\n"
        << "4. Sort grades\n"
        << "5. Calculate average\n"
        << "6. Check if student can advance\n"
        << "7. Check if a student is eligeble for a scholarship\n"
        << "9. Exit"
        << std::endl;
}

void printStudentInfo(const Student& student)
{
    std::cout << "Name: " << student.name << "\n" << "Faculty number: " << student.facultyNumber << std::endl;
}

void printGrades(const Student& student)
{
    for (int i = 0; i < SUBJECTS_COUNT; i++)
    {
        std::cout << student.subjects[i].name << " - " << student.subjects[i].grade << std::endl;
    }
}

void addGradeMenu(Student& student)
{
    std::cout << std::endl;
    std::cout << "What subject do you want to add the grade for: \n";

    for (int i = 0; i < SUBJECTS_COUNT; i++)
    {
        std::cout << i << ". " << student.subjects[i].name << "\n";
    }

    int subject;
    do
    {
        std::cin >> subject;
        if (subject < 0 || subject > SUBJECTS_COUNT - 1)
            std::cout << "Invalid subject! Please try again: ";
    } while (subject < 0 || subject > SUBJECTS_COUNT - 1);

    double grade;
    std::cout << "What grade do you want to enter: ";
    do
    {
        std::cin >> grade;
        if(grade < 2 || grade > 6)
            std::cout << "Invalid grade! Please try again: ";
    } while (grade < 2 || grade > 6);

    addGrade(student, Subjects(subject), grade);

    std::cout << "Grade added!" << std::endl;
}

