#include <iostream>
#include <string.h>

struct MarkList {
    unsigned short int bio, chem, phy;

    double GetPercentage (const unsigned short int& totat);
};

struct Info {
    char fnameBuffer[21], lnameBuffer[21];
    unsigned short int age;
    MarkList marks; 
    double percentage;
    bool passStatus{false};
    Info (
        const char* fname,
        const char* lname,
        const unsigned short int& _age,
        MarkList _marks,
        double _percentage
    );
};


class Student {
private:
    char fnameBuffer[21], lnameBuffer[21];
    unsigned short int age;
    MarkList marks; 
    double percentage;
    bool passStatus{false};
    // date to get date student was added
public:
    Student () {};

    void SetInfo ();
    Info GetInfo () const;
};
