#ifndef LIBRARY_H
#define LIBRARY_H
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include <vector>
#include <string>
#include <iomanip>
class Date {
public:
    int day, month, year;
    friend std::istream& operator>>(std::istream& is, Date& date);
};

class Student {
private:
    std::string fullName;
    Date birthDate;
    int enrollmentYear;
    std::string faculty, department, group, recordBookNumber, gender;
    std::map<int, std::map<std::string, int>> grades;

public:
    bool percentageOfGrades(const std::vector<int> &gradesList, double maxPercentage) const;


    friend std::istream& operator>>(std::istream& is, Student& student);
    friend std::ostream& operator<<(std::ostream& os, const Student& student);
};

std::istream& operator>>(std::istream& is, Student& student);
std::ostream& operator<<(std::ostream& os, const Student& student);

class University {
private:
    std::vector<Student> students;

public:
    void loadStudents(const std::string &filename);

    void printFilteredStudents(std::ostream &console, std::ostream &file, int option);

    static void encrypt (const std::string filenameIn, const std::string filenameOut);

    static void decrypt (const std::string filenameIn, const std::string filenameOut);
};
#endif