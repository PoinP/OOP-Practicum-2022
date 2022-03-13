#include <iostream>
#include <fstream>

struct Person
{
    char name[32];
    char phoneNumber[16];
    char address[64];
};

struct Phonebook
{
    Person people[20];
};

void writePersonData(const char* path, const Person& person);
Person readPersonData(const char* path, const int& index);
void writePhonebookData(const char* path, const Phonebook& phonebook);
Phonebook readPhonebookData(const char* path);
Person deletePerson(const char* path, const int& index);

void printPhonebook(const Phonebook& phonebook);
void printPerson(const Person& person);

void printMenu();
void addPersonMenu(const char* path, Phonebook& phonebook);
void deletePersonMenu(const char* path, const Phonebook& phonebook);

int main()
{
    const char* phonebookPath = "Phonebook.bin";
    Phonebook phonebook = readPhonebookData(phonebookPath);
    int userInput;

    do
    {
        printMenu();
        std::cin >> userInput;

        switch (userInput)
        {
        case 1:
            addPersonMenu(phonebookPath, phonebook);
            phonebook = readPhonebookData(phonebookPath);
            break;
        case 2:
            deletePersonMenu(phonebookPath, phonebook);
            phonebook = readPhonebookData(phonebookPath);
            break;
        case 3:
            printPhonebook(phonebook);
            break;
        default:
            std::cout << "Invalid option! Please try again!\n";
            break;
        }
    } while (userInput != 9);
}

#pragma region Menu

void printMenu()
{
    std::cout << "What would you like to do: "
        << "\n1. Add a person"
        << "\n2. Delete a person"
        << "\n3. Print phonebook"
        << "\n9. Exit"
        << std::endl;
}

void addPersonMenu(const char* path, Phonebook& phonebook)
{
    Person person;

    std::cout << "\nPlease enter a name: \n";
    std::cin.ignore();
    std::cin.getline(person.name, sizeof(person.name));

    std::cout << "Please enter a phone number: \n";
    std::cin.getline(person.phoneNumber, sizeof(person.phoneNumber));

    std::cout << "Please enter an address: \n";
    std::cin.getline(person.address, sizeof(person.address));

    int index = 0;
    for (int i = 0; i < sizeof(phonebook.people) / sizeof(Person); i++)
    {
        if (phonebook.people[i].name[0] == '\0')
        {
            index = i;
            break;
        }
    }

    phonebook.people[index] = person;
    writePhonebookData(path, phonebook);
}

void deletePersonMenu(const char* path, const Phonebook& phonebook)
{
    int index;
    std::cout << "\nWhich person would you like to delete: \n";
    printPhonebook(phonebook);

    std::cin >> index;

    Person deletedPerson = deletePerson(path, index);

    std::cout << "Successfully deleted " << deletedPerson.name << "!\n" << std::endl;
}

#pragma endregion


void writePersonData(const char* path, const Person& person)
{
    std::ofstream outStream(path, std::ios::binary | std::ios::app);

    if (outStream.is_open())
    {
        outStream.write(reinterpret_cast<const char*>(&person), sizeof(person));
        std::cout << "Successfully written a person's information to " << path << "!" << std::endl;
        outStream.close();
    }
    else
    {
        std::cout << "An error has occured while opening the file! No information has been written!" << std::endl;
    }
}

Person readPersonData(const char* path, const int& index)
{
    Person person = {};

    std::ifstream inStream(path, std::ios::binary);

    if (inStream.is_open())
    {
        inStream.seekg(index, inStream.beg);

        if (!inStream.read(reinterpret_cast<char*>(&person), sizeof(person)))
            std::cout << "Error reading the person's data from " << path << "!" << std::endl;

        inStream.close();
    }
    else
    {
        std::cout << "An error has occured while opening the file! No information has been written!" << std::endl;
    }

    return person;
}

void writePhonebookData(const char* path, const Phonebook& phonebook)
{
    std::ofstream outStream(path, std::ios::binary);

    if (outStream.is_open())
    {
        outStream.write(reinterpret_cast<const char*>(&phonebook), sizeof(phonebook));
        std::cout << "Successfully written the phonebook data to " << path << "!\n" << std::endl;
        outStream.close();
    }
    else
    {
        std::cout << "An error has occured while opening the file! No information has been written!" << std::endl;
    }
}

Phonebook readPhonebookData(const char* path)
{
    Phonebook phonebook = {};

    std::ifstream inStream(path, std::ios::binary);

    if (inStream.is_open())
    {
        inStream.read(reinterpret_cast<char*>(&phonebook), sizeof(phonebook));
        inStream.close();
    }
    else
    {
        std::cout << "An error has occured while opening the file! No information has been read!" << std::endl;
    }

    return phonebook;
}

void printPhonebook(const Phonebook& phonebook)
{
    std::cout << std::endl;
    for (int i = 0; i < (sizeof(phonebook.people) / sizeof(Person)); i++)
    {
        if (phonebook.people[i].name[0] != '\0')
        {
            std::cout << i << ". ";
            printPerson(phonebook.people[i]);
        }
    }
    std::cout << std::endl;
}

void printPerson(const Person& person)
{
    std::cout << person.name << "  " << person.phoneNumber << "  " << person.address << "\n";
}

Person deletePerson(const char* path, const int& index)
{
    std::ofstream newFile("temp.bin", std::ios::binary);
    std::ifstream oldFile(path);

    Person person = {};

    if (newFile.is_open() && oldFile.is_open())
    {
        int i = 0;
        Person tempPerson;
        while (!oldFile.eof() && oldFile.good() && newFile.good())
        {
            oldFile.read(reinterpret_cast<char*>(&tempPerson), sizeof(tempPerson));

            if (i != index)
                newFile.write(reinterpret_cast<const char*>(&tempPerson), sizeof(tempPerson));
            else
                person = tempPerson;

            i++;
        }

        oldFile.close();
        newFile.close();

        remove(path);

        if (rename("temp.bin", path) == -1)
        {
            std::cout << "An unexpected error has occured!" << std::endl;
        }
    }
    else
    {
        std::cout << "An error has occured! No information has been deleted!" << std::endl;
        newFile.close();
        oldFile.close();
    }

    return person;
}
