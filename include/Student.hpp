#include <iostream>
#include <string.h>

struct MarkList {
    unsigned short int bio, chem, phy;

    double GetPercentage (unsigned short int);
};

struct Info {
    unsigned int id;
    char fnameBuffer[10], lnameBuffer[10];
    unsigned short int age;
    MarkList marks; 
    double percentage;
    bool passStatus{false};
    Info (
        unsigned int _id,
        const char* fname,
        const char* lname,
        const unsigned short int& _age,
        MarkList _marks,
        double _percentage
    );
};

// remove id when database
static unsigned int studentId = 0;
class Student {
private:
    unsigned int id = 0;
    char fnameBuffer[10], lnameBuffer[10];
    unsigned short int age;
    MarkList marks; 
    double percentage;
    bool passStatus{false};
    // date to get date student was added
public:
    Student () {
        id = studentId++;
    };

    void SetInfo ();
    Info GetInfo () const;
};
