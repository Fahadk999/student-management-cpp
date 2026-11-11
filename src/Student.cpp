#include "Student.hpp"

Info::Info (
    unsigned int _id,
    const char* fname,
    const char* lname,
    const unsigned short int& _age,
    MarkList _marks,
    double _percentage
        )
    :   
    id(_id),
    age(_age),
    percentage(_percentage)
{
    marks = _marks;
    strcpy(fnameBuffer, fname);
    strcpy(lnameBuffer, lname);
}

void Student::SetInfo () {
    auto setString = [] (char* buffer, const int& len, const char* msg) {
        std::cout << msg;
        std::cin.getline(buffer, len);
    };
    auto setUint = [] (unsigned short int& buffer, const short int& range, const char* msg) {
        do {
            std::cout << msg;
            std::cin >> buffer;
        } while (buffer > range);
    };

    const short int maxMarks = 100;
    std::cin.ignore();
    setString(this->fnameBuffer, 10, "Enter Student First Name: ");
    setString(this->lnameBuffer, 10, "Enter Student Last Name: ");
    setUint(this->age, 150, "Enter Student Age (0-150): ");
    setUint(this->marks.bio, maxMarks, "Enter Marks in Biology: ");
    setUint(this->marks.chem, maxMarks, "Enter Marks in Chemistry: ");
    setUint(this->marks.phy, maxMarks, "Enter Marks in Physics: ");
    this->percentage = this->marks.GetPercentage(300);
}

Info Student::GetInfo () const {
    Info info{
            this->id,
            this->fnameBuffer,
            this->lnameBuffer,
            this->age,
            this->marks,
            this->percentage
            };
    return info;
}

double MarkList::GetPercentage (unsigned short int total) {
    const unsigned short int obtained = this->bio + this->chem + this->phy;
    return (static_cast<double>(obtained)/total)*100.0;
}
