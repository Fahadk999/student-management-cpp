#include "Manager.hpp"

void Manager::AddStudent () {
    Student newStudent;
    newStudent.SetInfo();
    if (studentCount <= maxCount) {
        studentList[studentCount] = newStudent;
        studentCount++;
    } else {
        std::cout << "List max capacity reached, empty it somehow\n";
    }
}

void Manager::RemoveStudent () {
    std::cout << "Enter id to remove\n";
}

void Manager::ShowList () {
    if (studentCount > 0) {
        for (int i = 0; i < studentCount; i++) {
            std::cout << studentList[i].GetInfo().fnameBuffer << std::endl;
        }
    } else {
        std::cout << "List is empty";
    }
}

void Manager::Run () {
    bool running = true;
    short int choice;
    do {
        std::cout << "--- Student Manager ---\n"
            << "1. Add Student\n"
            << "2. Remove Student\n"
            << "3. Show List\n"
            << "4. Exit\n"
            << "Your choice: ";
        std::cin >> choice;
        switch (choice) {
            case 1:
                AddStudent();
                break;
            case 2:
                RemoveStudent();
                break;
            case 3:
                ShowList();
                break;
            case 4:
                std::cout << "Exited successfully\n";
                running = false;
                break;
            default:
                std::cerr << "Wring choice!!";
        }
    } while (running);
}
