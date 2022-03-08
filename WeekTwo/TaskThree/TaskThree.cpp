#include <iostream>
#include <fstream>
#include <string>

struct Student
{
	char firstName[32];
	char lastName[32];
	char email[32];
	char facultyNumber[16];
};

void printStudent(const Student* students, const int& studentAmount, const char* facultyNumber);

void addNewStudent(const char* path, const Student& student);
int getStudentAmount(const char* path);
Student loadStudent(const char* string);
Student* loadStudentData(const char* path, int& studentAmount);

bool doesFileExist(const char* path);
void createFile(const char* path);
void saveFile(const char* path, const Student* students, const int& studentAmount);

Student* getStudent(Student* students, const int& studentAmount, const char* facultyNumber);
void editStudentEmail(Student* students, const int& studentAmount, const char* facultyNumber, const char* newEmail);
void editStudentFacultyNumber(Student* students, const int& studentAmount, const char* facultyNumber, const char* newFN);
void editStudentFirstName(Student* students, const int& studentAmount, const char* facultyNumber, const char* newName);
void editStudentLastName(Student* students, const int& studentAmount, const char* facultyNumber, const char* newName);

Student* setup(const char* path, int& studentAmount);
void printMenu();
void printStudentMenu(const Student* students, const int& studentAmount);
void editEmailMenu(Student* students, const int& studentAmount);
void editNameMenu(Student* students, const int& studentAmount);
void editFacultyNumberMenu(Student* students, const int& studentAmount);
void saveToNewFileMenu(Student* students, const int& studentAmount);
void addStudentMenu(const char* path);

char* strcpy_safe(char* destination, const char* source, const int& length);

int main()
{
	char filePath[64];
	std::cout << "Which file do you want to open: ";
	std::cin >> filePath;

	int studentAmount;
	Student* allStudents = setup(filePath, studentAmount);

	if (!allStudents)
		return -1;

	int userInput;

	do
	{
		printMenu();
		std::cin >> userInput;

		switch (userInput)
		{
		case 1:
			printStudentMenu(allStudents, studentAmount);
			break;
		case 2:
			editEmailMenu(allStudents, studentAmount);
			break;
		case 3:
			editNameMenu(allStudents, studentAmount);
			break;
		case 4:
			editFacultyNumberMenu(allStudents, studentAmount);
			break;
		case 5:
			saveFile(filePath, allStudents, studentAmount);
			break;
		case 6:
			allStudents = loadStudentData(filePath, studentAmount);
			std::cout << "Successfully reloaded the file " << filePath << std::endl;
			break;
		case 7:
			saveToNewFileMenu(allStudents, studentAmount);
			break;
		case 8:
			addStudentMenu(filePath);
			allStudents = loadStudentData(filePath, studentAmount);
		default:
			break;
		}
	} while (userInput != 9);

	delete[] allStudents;
}

#pragma region Menus

Student* setup(const char* path, int& studentAmount)
{
	char userInput;
	Student* students;

	if (!doesFileExist(path))
	{
		std::cout << "This file doesn't exist! Do you want to create it Y/N: ";
		std::cin >> userInput;

		if (userInput == 'y' || userInput == 'Y')
		{
			createFile(path);
			addStudentMenu(path);
		}
		else
		{
			return nullptr;
		}
	}

	do
	{
		students = loadStudentData(path, studentAmount);
		userInput = 'n';

		if (!students)
		{
			std::cout << "The file is empty or there was a problem opening the file! Do you want to try again? Y/N\n";
			std::cin >> userInput;
		}
	} while (!students && (userInput == 'y' || userInput == 'Y'));

	return students;
}

void printMenu()
{
	std::cout << std::endl;
	std::cout << "What would you like to do: \n";
	std::cout << "1. Show student info by faculty number\n"
		<< "2. Edit a student's email address\n"
		<< "3. Edit a student's name\n"
		<< "4. Edit a student's faculty number\n"
		<< "5. Save the file\n"
		<< "6. Reload the file\n"
		<< "7. Save information to a new file\n"
		<< "8. Add new student\n"
		<< "9. Exit"
		<< std::endl;
}

void printStudentMenu(const Student* students, const int& studentAmount)
{
	char facultyNumber[16];

	std::cout << "Plese enter a faculty number: ";
	std::cin >> facultyNumber;

	printStudent(students, studentAmount, facultyNumber);
}

void editEmailMenu(Student* students, const int& studentAmount)
{
	char facultyNumber[16];

	std::cout << "Plese enter a faculty number: ";
	std::cin >> facultyNumber;

	char emailAddress[32];

	std::cout << "Please enter the new email address: ";
	std::cin >> emailAddress;

	editStudentEmail(students, studentAmount, facultyNumber, emailAddress);
}

void editNameMenu(Student* students, const int& studentAmount)
{
	int userInput;
	char name[32];

	do
	{
		std::cout << "Which name do you want to change:\n"
			<< "1. First name\n"
			<< "2. Last name\n"
			<< std::endl;

		std::cin >> userInput;
	} while (userInput != 1 && userInput != 2);

	char facultyNumber[16];

	std::cout << "Plese enter a faculty number: ";
	std::cin >> facultyNumber;

	std::cout << "Please enter a new name: ";
	std::cin >> name;

	if (userInput == 1)
		editStudentFirstName(students, studentAmount, facultyNumber, name);
	else
		editStudentLastName(students, studentAmount, facultyNumber, name);
}

void editFacultyNumberMenu(Student* students, const int& studentAmount)
{
	char facultyNumber[16];

	std::cout << "Plese enter a faculty number: ";
	std::cin >> facultyNumber;

	char newFacultyNumber[16];

	std::cout << "Please enter a new faculty number: ";
	std::cin >> newFacultyNumber;

	editStudentFacultyNumber(students, studentAmount, facultyNumber, newFacultyNumber);
}

void saveToNewFileMenu(Student* students, const int& studentAmount)
{
	char path[32];

	std::cout << "Please enter a new file name/directory: ";
	std::cin >> path;

	saveFile(path, students, studentAmount);
}

void addStudentMenu(const char* path)
{
	Student newStudent;

	std::cout << "Please enter the students's first name: ";
	std::cin >> newStudent.firstName;

	std::cout << "Please enter the student's last name: ";
	std::cin >> newStudent.lastName;

	std::cout << "Please enter the students's email: ";
	std::cin >> newStudent.email;

	std::cout << "Please enter the students's faculty number: ";
	std::cin >> newStudent.facultyNumber;

	addNewStudent(path, newStudent);
}

#pragma endregion

#pragma region Get

Student* getStudent(Student* students, const int& studentAmount, const char* facultyNumber)
{
	for (int i = 0; i < studentAmount; i++)
	{
		if (!strcmp(students[i].facultyNumber, facultyNumber))
		{
			return &students[i];
		}
	}

	return nullptr;
}

int getStudentAmount(const char* path)
{
	std::fstream stream(path, std::ios::in | std::ios::app);

	if (!stream.is_open())
	{
		std::cout << "Error oppening file! No data has been read!" << std::endl;
		return 0;
	}

	char buffer[256];
	int studentAmount = 0;

	while (stream.getline(buffer, 256))
	{
		studentAmount++;
	}

	return studentAmount;

	stream.close();
}

char** getLineEntries(std::fstream& stream, const int& studentAmount)
{
	char** lineEntries = new char* [studentAmount];
	char buffer[256];

	int index = 0;
	while (stream.getline(buffer, 256) && index < studentAmount)
	{
		int lineLength = std::strlen(buffer);
		lineEntries[index] = new char[lineLength + 1];
		strcpy_safe(lineEntries[index], buffer, lineLength + 1);
		index++;
	}

	return lineEntries;
}

#pragma endregion

#pragma region Update

void addNewStudent(const char* path, const Student& student)
{
	std::fstream stream(path, std::ios::out | std::ios::app);

	if (!stream.is_open())
	{
		std::cout << "Error oppening file! No data has been written!" << std::endl;
		return;
	}

	stream << student.firstName << "," << student.lastName << "," << student.email << "," << student.facultyNumber << "\n";

	std::cout << "Successufly added a new student with faculty number " << student.facultyNumber << "!" << std::endl;

	stream.close();
}

void editStudentEmail(Student* students, const int& studentAmount, const char* facultyNumber, const char* newEmail)
{
	Student* student = getStudent(students, studentAmount, facultyNumber);

	if (!student)
	{
		std::cout << "This student does not exist!" << std::endl;
		return;
	}

	strcpy_safe(student->email, newEmail, sizeof(student->email));

	std::cout << "Done! Successfully changed " << student->firstName << "'s email to " << student->email << std::endl;
}

void editStudentFacultyNumber(Student* students, const int& studentAmount, const char* facultyNumber, const char* newFN)
{
	Student* student = getStudent(students, studentAmount, facultyNumber);

	if (!student)
	{
		std::cout << "This student does not exist!" << std::endl;
		return;
	}

	strcpy_safe(student->facultyNumber, newFN, sizeof(student->facultyNumber));

	std::cout << "Done! Successfully changed " << student->firstName << "'s faculty number to " << student->facultyNumber << std::endl;
}

void editStudentFirstName(Student* students, const int& studentAmount, const char* facultyNumber, const char* newName)
{
	Student* student = getStudent(students, studentAmount, facultyNumber);

	if (!student)
	{
		std::cout << "This student does not exist!" << std::endl;
		return;
	}

	strcpy_safe(student->firstName, newName, sizeof(student->firstName));

	std::cout << "Done! Successfully changed " << student->lastName << "'s first name to " << student->firstName << std::endl;
}

void editStudentLastName(Student* students, const int& studentAmount, const char* facultyNumber, const char* newName)
{
	Student* student = getStudent(students, studentAmount, facultyNumber);

	if (!student)
	{
		std::cout << "This student does not exist!" << std::endl;
		return;
	}

	strcpy_safe(student->lastName, newName, sizeof(student->firstName));

	std::cout << "Done! Successfully changed " << student->firstName << "'s last name to " << student->lastName << std::endl;
}

void saveFile(const char* path, const Student* students, const int& studentAmount)
{
	std::fstream stream(path, std::ios::out | std::ios::trunc);

	if (stream.is_open())
		stream.close();

	for (int i = 0; i < studentAmount; i++)
	{
		addNewStudent(path, students[i]);
	}

	std::cout << "Successufully saved the information to " << path << std::endl;
}

#pragma endregion

bool doesFileExist(const char* path)
{
	std::ifstream stream(path);
	bool status = stream.good();
	stream.close();

	return status;
}

void createFile(const char* path)
{
	std::ofstream stream(path);
	stream.close();
}

void printStudent(const Student* students, const int& studentAmount, const char* facultyNumber)
{
	for (int i = 0; i < studentAmount; i++)
	{
		if (!strcmp(students[i].facultyNumber, facultyNumber))
		{
			std::cout << "Name = " << students[i].firstName << " " << students[i].lastName
				<< ", Email: " << students[i].email
				<< ", FN: " << students[i].facultyNumber
				<< std::endl;

			return;
		}
	}

	std::cout << "A student with this faculty number does not exist!";
}

Student loadStudent(const char* string)
{
	char studentInfo[4][32];

	int studentIndex = 0;
	int charIndex = 0;
	while (*string != '\0')
	{
		if (*string != ',')
		{
			studentInfo[studentIndex][charIndex] = *string;
			charIndex++;
		}
		else
		{
			studentInfo[studentIndex][charIndex] = '\0';
			charIndex = 0;
			studentIndex++;
		}

		string++;
	}

	studentInfo[studentIndex][charIndex] = '\0';

	Student newStudent;
	strcpy_safe(newStudent.firstName, studentInfo[0], sizeof(newStudent.firstName));
	strcpy_safe(newStudent.lastName, studentInfo[1], sizeof(newStudent.lastName));
	strcpy_safe(newStudent.email, studentInfo[2], sizeof(newStudent.email));
	strcpy_safe(newStudent.facultyNumber, studentInfo[3], sizeof(newStudent.facultyNumber));

	return newStudent;
}

Student* loadStudentData(const char* path, int& studentAmount)
{
	studentAmount = getStudentAmount(path);

	if (studentAmount == 0)
		return nullptr;

	std::fstream stream(path, std::ios::in | std::ios::app);

	if (!stream.is_open())
	{
		std::cout << "Error oppening file! No data has been loaded!" << std::endl;
		return nullptr;
	}

	Student* students = new Student[studentAmount];

	std::cout << "Students loaded into memory!" << std::endl;

	char** entries = getLineEntries(stream, studentAmount);

	for (int i = 0; i < studentAmount; i++)
	{
		students[i] = loadStudent(entries[i]);
		delete[] entries[i];
	}

	delete[] entries;

	return students;
}

char* strcpy_safe(char* destination, const char* source, const int& length)
{
	if (length > 0)
	{
		int i;
		for (i = 0; i < length - 1 && source[i] != '\0'; i++)
		{
			destination[i] = source[i];
		}

		destination[i] = '\0';
	}

	return destination;
}