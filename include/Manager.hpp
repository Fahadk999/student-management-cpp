#include "Student.hpp"
#include <iomanip>
#include <cstdio>

class Manager {
private:
    Student studentList[30];
    short int studentCount{0}, maxCount{30};

    void AddStudent ();
    void RemoveStudent ();
    void ShowList ();
public:
    Manager () = default;

    void Run ();
};