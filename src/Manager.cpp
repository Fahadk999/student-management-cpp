#include "Manager.hpp"

Manager::Manager () {
    studentDB.InitDB();
    // for deleting cascade
    studentDB.Execute("PRAGMA foregin_key = ON;");

    const char* queryOne =
        "CREATE TABLE IF NOT EXISTS students ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "FirstName TEXT NOT NULL,"
        "LastName TEXT NOT NULL,"
        "Age INTEGER NOT NULL);";
    const char* queryTwo =
        "CREATE TABLE IF NOT EXISTS marks ("
        "ID INTEGER PRIMARY KEY AUTOINCREMENT,"
        "StudentId INTEGER,"
        "Biology INTEGER,"
        "Chemistry INTEGER,"
        "Physics INTEGER,"
        "Percentage REAL,"
        "FOREIGN KEY (StudentId) REFERENCES students(ID)"
        " ON DELETE CASCADE);";
    studentDB.Execute(queryOne);
    studentDB.Execute(queryTwo);
}

void Manager::AddStudent () {
    Student newStudent;
    newStudent.SetInfo();
    Info info = newStudent.GetInfo();
    char query[500];

    std::snprintf(query, sizeof(query), 
        "INSERT INTO students (FirstName, LastName, Age) "
        "VALUES ('%s', '%s', %d);",
        info.fnameBuffer, 
        info.lnameBuffer,
        info.age
    );
    studentDB.Execute(query);
    int studentId = studentDB.GetLastId();
    std::snprintf(query, sizeof(query),
        "INSERT INTO marks (StudentId, Biology, Chemistry, Physics, Percentage) "
        "VALUES (%d, %d, %d, %d, %.2f);",
        studentId,
        info.marks.bio,
        info.marks.chem,
        info.marks.phy,
        info.percentage
    );
    studentDB.Execute(query);

    studentList[studentCount] = newStudent;
    studentCount++;
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
    char query[200] =
        "SELECT * FROM ";
    auto len = std::strlen(query);
    std::snprintf(query + len, sizeof(query) - len , "%s;", "students");
    studentDB.ReadData(query);
}

void Manager::SearchStudent () {
    char query[700];
    int choice;
    std::cout << "Search by"
        << "\n1. ID\n2. First Name\n3. Last Name\n4. Full Name\n";
    setUint(choice, "Choice: "); 
    const char* selectList =
        "students.ID, students.FirstName, students.LastName,"
        "students.Age, marks.Biology, marks.Chemistry, marks.Physics,"
        "marks.Percentage";
    switch (choice)
    {
        case 1: {
            int id;
            setUint(id, "Enter student ID: "); 
            std::snprintf(query, sizeof(query),
                "SELECT %s FROM students JOIN marks ON students.ID = marks.StudentId WHERE students.ID = %d", selectList, id);
            break;
                }
        case 2: {
            char fnameBuffer[nameLen];
            std::cout << "Enter Student First Name: ";
            std::cin.ignore();
            std::cin.getline(fnameBuffer, nameLen);
            std::snprintf(query, sizeof(query),
                "SELECT %s FROM students JOIN marks ON "
                "students.ID = marks.StudentId WHERE students.FirstName='%s';"
                , selectList, fnameBuffer);
            break;
            }
        case 3: {
            char lnameBuffer[nameLen];
            std::cout << "Enter Student Last Name: ";
            std::cin.ignore();
            std::cin.getline(lnameBuffer, nameLen);
            std::snprintf(query, sizeof(query),
                "SELECT %s FROM students JOIN marks ON "
                "students.ID = marks.StudentId WHERE students.LastName='%s';"
                , selectList, lnameBuffer);
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
                "SELECT %s FROM students JOIN marks ON "
                "students.ID = marks.StudentId WHERE students.FirstName='%s' "
                "AND students.LastName='%s';"
                , selectList, fnameBuffer, lnameBuffer);
            break;
            }
        default:
            std::cerr << "Wrong choice!\n";
            return;
    }
    studentDB.ReadData(query);
}

void Manager::Run () {
    //for linux only
    bool running = true;
    short int choice;
    do {
        std::system("clear");
        std::cout << "--- Student Manager ---\n"
            << "1. Add Student\n"
            << "2. Remove Student\n"
            << "3. Show List\n"
            << "4. Search Student\n"
            << "5. Filter\n"
            << "6. Update Student\n"
            << "7. Exit\n";
        setUint(choice, "Your choice: ");
        switch (choice) {
            case 1: AddStudent(); break;
            case 2: RemoveStudent(); break;
            case 3: ShowList(); break;
            case 4: SearchStudent(); break;
            case 5: ShowFiltered(); break;
            case 6: UpdateInfo(); break;
            case 7:
                std::cout << "Exited successfully\n";
                running = false;
                break;
            default: std::cerr << "Wring choice!!\n";
        }
        std::cin.ignore();
        std::cin.get();
    } while (running);
}

void Manager::ShowFiltered () {
    char query[300];
    int choice;
    std::cout <<
        "Filter what?: \n1. Passed\n2.Failed\n";
    setUint(choice, "Choice: ");
    if (choice == 1) {
        std::snprintf(query, sizeof(query), "SELECT students.* FROM students %s", "WHERE percentage >= 50.00;");
    } else if (choice == 2) {
        std::snprintf(query, sizeof(query), "SELECT students.* FROM students %s", "WHERE percentage < 50.00;");
    } else {
        std::cerr << "Wrong choice!\n";
        return;
    }
    studentDB.ReadData(query);
}

void Manager::UpdateInfo () {
    int choice;
    int id;
    setUint(id, "Enter student ID to update: ");
    std::cout << "Update what?:\n"
        << "1. Name\n"
        << "2. Age\n"
        << "3. Marks\n";
    setUint(choice, "Choice: ");
    char query[500] = "UPDATE students SET ";
    const size_t qLen = std::strlen(query);
    switch (choice) {
        case 1: {
            std::cin.ignore();
            // flag for sucess or not
            char fnameBuffer[nameLen], lnameBuffer[nameLen];
            setString(fnameBuffer, nameLen,"Enter First Name: ");
            setString(lnameBuffer, nameLen, "Enter Last Name: ");

            std::snprintf(query + qLen, sizeof(query) - qLen, 
                    "FirstName = '%s', LastName = '%s' WHERE ID = %d;", fnameBuffer, lnameBuffer, id);
            break;
                }
        case 2: {
            int age;
            setUint(age, 150, "Enter new age: ");
            std::snprintf(query, sizeof(query), "%s Age = %d WHERE ID = %d;", query, age, id);
            break;
                }
        case 3: {
            const char* subject[] = {"Biology", "Chemistry", "Physics"};
            std::cout << "How Many\n1. One\n2. All";
            setUint(choice, "Choice: ");
            switch (choice) {
                case 1: {
                    int i = 1;
                    for (const char** p = subject; p < subject + 3; p++) {
                        std::cout << i++ << ". " << *p << '\n';
                    }
                    setUint(choice, "Pick a subject: ");
                    std::sprintf(query, "%s", "UPDATE marks SET ");
                    const size_t len = std::strlen(query); 
                    switch (choice) {
                        case 1: {
                            int marks;
                            setUint(marks, 101, "Enter updated marks: ");
                            std::snprintf(query + len, sizeof(query) - len, 
                            "%s = %d WHERE StudentId = %d;"
                            , *subject + choice-1, marks, id); 
                            break;
                                }
                        case 2: {
                            int marks[3]; 
                            for (int* p = marks; p < marks+3; p++) {
                                std::cout << "hell"; 
                            }
                                }
                        default: std::cout << "Enter a vaild subject number!\n";
                            return;
                    }
                    break;
                        }
                default: std::cout << "Wrong choice!\n"; return;
                }
            break;
                }
        default:
            std::cerr << "Wrong Choice\n";
    }
    studentDB.Execute(query);
}
