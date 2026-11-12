#include "Student.hpp"
#include "Database.hpp"
#include <iomanip>

class Manager {
private:
    Database studentDB{"students.db"};
    Student studentList[30];
    short int studentCount{0}, maxCount{30};

    void AddStudent ();
    void RemoveStudent ();
    void ShowList ();
    void SearchStudent ();
public:
    Manager ();

    void Run ();
};
