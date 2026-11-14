#pragma once
#include <iostream>
#include <string.h>

constexpr size_t nameLen = 20;

struct MarkList
{
    unsigned short int bio, chem, phy;

    double GetPercentage(unsigned short int);
};

struct Info
{
    unsigned int id;
    char fnameBuffer[nameLen], lnameBuffer[nameLen];
    unsigned short int age;
    MarkList marks;
    double percentage;
    bool passStatus{false};
    Info(
        unsigned int _id,
        const char *fname,
        const char *lname,
        const unsigned short int &_age,
        MarkList _marks,
        double _percentage);
};

// remove id when database
class Student
{
private:
    unsigned int id = 0;
    char fnameBuffer[nameLen], lnameBuffer[nameLen];
    unsigned short int age;
    MarkList marks;
    double percentage;
    bool passStatus{false};
    static unsigned int studentId;
    // date to get date student was added
public:
    Student();

    void SetInfo();
    Info GetInfo() const;
};

template <typename T, typename U>
void setUint (
        T& buffer,
        const U& range,
        const char* msg = "") {
    bool valid = true;
    do {
        std::cout << msg;
        if(!(std::cin >> buffer)) {
            buffer = 0;
            std::cin.clear();
            std::cin.ignore();
            valid = false;
        } else { valid = true; }
    } while (buffer > range || buffer < 0 || !valid);
}
template <typename T>
void setUint (
        T& buffer,
        const char* msg = "") {
    bool valid = true;
    do {
        std::cout << msg;
        if(!(std::cin >> buffer)) {
            buffer = 0;
            std::cin.clear();
            std::cin.ignore();
            valid = false;
        } else { valid = true; }
    } while (buffer < 0 || !valid);
}

inline void setString (char* buffer, const int& len, const char* msg) {
    std::cout << msg;
    std::cin.getline(buffer, len);
};
