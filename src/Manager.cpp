#include "Manager.hpp"

// add student search on id and name
Manager::Manager () {
    studentDB.InitDB();
    const char* createTable =
        "CREATE TABLE IF NOT EXISTS students ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "FirstName TEXT NOT NULL,"
        "LastName TEXT NOT NULL,"
        "Biology INTEGER,"
        "Chemistry INTEGER,"
        "Physics INTEGER,"
        "Percentage REAL"
        ");";
    studentDB.Execute(createTable);
}

void Manager::AddStudent () {
    Student newStudent;
    newStudent.SetInfo();
    if (studentCount < maxCount) {
        Info info = newStudent.GetInfo();
        char query[500];

        std::snprintf(query, sizeof(query), 
            "INSERT INTO students (FirstName, LastName, Biology, Chemistry, Physics, Percentage) "
            "VALUES ('%s', '%s', %d, %d, %d, %.2f);",
            info.fnameBuffer, 
            info.lnameBuffer,
            info.marks.bio, 
            info.marks.chem, 
            info.marks.phy, 
            info.percentage
        );
        studentDB.Execute(query);

        studentList[studentCount] = newStudent;
        studentCount++;
    } else {
        std::cout << "List max capacity reached, empty it somehow\n";
    }
}

void Manager::RemoveStudent () {
    int choice;
    std::cout << 
        "Removing by:\n1. ID\n2. Name\n";
    setUint(choice, "Choice: "); 

    char query[200];
    switch (choice) {
        case 1: {
            int id;
            setUint(id, "Enter student ID: "); 
            std::snprintf(query, sizeof(query),
                "DELETE FROM students WHERE ID=%d", id);
            break;
                }
        case 2: {
            char fnameBuffer[nameLen], lnameBuffer[nameLen];
            std::cout << "Enter Student First Name: ";
            std::cin.ignore();
            std::cin.getline(fnameBuffer, nameLen);
            std::cout << "Enter Student Last Name: ";
            std::cin.getline(lnameBuffer, nameLen);
            std::snprintf(query, sizeof(query),
                "DELETE FROM students WHERE FirstName='%s' AND LastName='%s'"
                , fnameBuffer, lnameBuffer);
            break;
            }
        default:
            std::cerr << "Wrong choice!";
            return;
    }
    studentDB.Execute(query);
}

void Manager::ShowList () {
    const char* query =
        "SELECT * FROM students;";
    studentDB.ReadData(query);
}

void Manager::SearchStudent () {
    char query[200];
    int choice;
    std::cout << "Search by"
        << "\n1. ID\n2. First Name\n3. Last Name\n4. Full Name\n";
    setUint(choice, "Choice: "); 
    switch (choice)
    {
        case 1: {
            int id;
            setUint(id, "Enter student ID: "); 
            std::snprintf(query, sizeof(query),
                "SELECT * FROM students WHERE ID=%d", id);
            break;
                }
        case 2: {
            char fnameBuffer[nameLen];
            std::cout << "Enter Student First Name: ";
            std::cin.ignore();
            std::cin.getline(fnameBuffer, nameLen);
            std::snprintf(query, sizeof(query),
                "SELECT * FROM students WHERE FirstName='%s';"
                , fnameBuffer);
            break;
            }
        case 3: {
            char lnameBuffer[nameLen];
            std::cout << "Enter Student Last Name: ";
            std::cin.ignore();
            std::cin.getline(lnameBuffer, nameLen);
            std::snprintf(query, sizeof(query),
                "SELECT * FROM students WHERE LastName='%s';"
                , lnameBuffer);
            break;
            }
        case 4: {
            char fnameBuffer[nameLen], lnameBuffer[nameLen];
            std::cout << "Enter Student First Name: ";
            std::cin.ignore();
            std::cin.getline(fnameBuffer, nameLen);
            std::cout << "Enter Student Last Name: ";
            std::cin.getline(lnameBuffer, nameLen);
            std::snprintf(query, sizeof(query),
                "SELECT * FROM students WHERE FirstName='%s' AND LastName='%s';"
                , fnameBuffer, lnameBuffer);
            break;
            }
        default:
            std::cerr << "Wrong choice!\n";
            return;
    }
    studentDB.ReadData(query);
}

void Manager::Run () {
    bool running = true;
    short int choice;
    do {
        std::cout << "--- Student Manager ---\n"
            << "1. Add Student\n"
            << "2. Remove Student\n"
            << "3. Show List\n"
            << "4. Search Student\n"
            << "5. Exit\n";
        setUint(choice, "Your choice: ");
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
                SearchStudent();
                break;
            case 5:
                std::cout << "Exited successfully\n";
                running = false;
                break;
            default:
                std::cerr << "Wring choice!!";
        }
    } while (running);
}
