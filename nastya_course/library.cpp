#include "library.h"

std::istream& operator>>(std::istream& is, Date& date) {
    char delim1, delim2;
    is >> date.day >> delim1 >> date.month >> delim2 >> date.year;
    return is;
}

bool Student::percentageOfGrades(const std::vector<int>& gradesList, double maxPercentage) const {
    int count = 0;
    int total = 0;
    for (const auto& session : grades) {
        for (const auto& subjectGrade : session.second) {
            total++;
            if (std::find(gradesList.begin(), gradesList.end(), subjectGrade.second) != gradesList.end()) {
                count++;
            }
        }
    }
    std::cout << "Student " << fullName << ": " << count << " out of " << total << " are in the list, which is "
              << static_cast<double>(count) / total * 100.0 << "%\n";
    return total > 0 && (static_cast<double>(count) / total * 100.0) <= maxPercentage;
}

std::istream& operator>>(std::istream& is, Student& student) {
    std::string line;
    std::getline(is, line);
    std::istringstream lineStream(line);
    lineStream >> std::quoted(student.fullName);
    lineStream.ignore(1, ';');
    lineStream >> student.birthDate;
    lineStream.ignore(1, ';');
    lineStream >> student.enrollmentYear;
    lineStream.ignore(1, ';');
    lineStream >> std::quoted(student.faculty);
    lineStream.ignore(1, ';');
    lineStream >> std::quoted(student.department);
    lineStream.ignore(1, ';');
    lineStream >> std::quoted(student.group);
    lineStream.ignore(1, ';');
    lineStream >> std::quoted(student.recordBookNumber);
    lineStream.ignore(1, ';');
    lineStream >> std::quoted(student.gender);
    lineStream.ignore(1, ';');

    int session;
    std::string subject;
    int grade;
    while (lineStream >> session) {
        lineStream.ignore();
        while (std::getline(lineStream, subject, '=')) {
            lineStream >> grade;
            student.grades[session][subject] = grade;
            if (lineStream.peek() == ';') {
                lineStream.ignore();
                break;
            }
        }
    }
    return is;
}

std::ostream& operator<<(std::ostream& os, const Student& student) {
    os << "Student Name: " << student.fullName << "\n"
       << "Birthdate: " << student.birthDate.day << "/" << student.birthDate.month << "/" << student.birthDate.year << "\n"
       << "Enrollment Year: " << student.enrollmentYear << "\n"
       << "Faculty: " << student.faculty << "\n"
       << "Department: " << student.department << "\n"
       << "Group: " << student.group << "\n"
       << "Record Book Number: " << student.recordBookNumber << "\n"
       << "Gender: " << student.gender << "\n";
    for (const auto& session : student.grades) {
        os << "Session " << session.first << ":\n";
        for (const auto& grade : session.second) {
            os << "  " << grade.first << ": " << grade.second << "\n";
        }
    }
    return os;
}

void University::loadStudents(const std::string& filename) {
    std::ifstream inputFile(filename);
    if (!inputFile) {
        std::cerr << "Unable to open file: " << filename << std::endl;
        return;
    }
    Student student;
    while (inputFile >> student) {
        students.push_back(student);
    }
}


void University::printFilteredStudents(std::ostream& console, std::ostream& file, int option) {
    std::vector<int> gradesToCheck;
    double maxPercentage = 25.0;

    switch (option) {
        case 1: gradesToCheck = {3}; break;
        case 2: gradesToCheck = {3, 4}; break;
        case 3: gradesToCheck = {5}; break;
        case 4: gradesToCheck = {3, 5}; break;
        case 5: gradesToCheck = {4, 5}; break;
        default:
            console << "Invalid option selected." << std::endl;
            file << "Invalid option selected." << std::endl;
            return;
    }

    for (const auto& student : students) {
        if (student.percentageOfGrades(gradesToCheck, maxPercentage)) {
            console << student << std::endl;
            file << student << std::endl;
        }
    }
}

