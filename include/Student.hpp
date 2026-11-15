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
    char fnameBuffer[nameLen], lnameBuffer[nameLen];
    unsigned short int age;
    MarkList marks;
    double percentage;
    bool passStatus{false};
    Info(
        const char* fname,
        const char* lname,
        const unsigned short int &_age,
        MarkList _marks,
        double _percentage);
};

class Student
{
private:
    char fnameBuffer[nameLen], lnameBuffer[nameLen];
    unsigned short int age;
    MarkList marks;
    double percentage;
    bool passStatus{false};
    // date to get date student was added
public:
    Student() = default;

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
    // overflow solution , temp big string store, if strlen <= nameLen valid
    std::cout << msg;
    std::cin.getline(buffer, len);
};
