#include "library.h"
int main() {
    University::decrypt("data.enc", "data.txt");

    University uni;
    uni.loadStudents("data.txt");

    std::ofstream outputFile("result.txt");
    if (!outputFile) {
        std::cerr << "Unable to open result file." << std::endl;
        return 1;
    }

    int option;
    std::cout << "Enter an option (1-5): ";
    std::cin >> option;

    uni.printFilteredStudents(std::cout, outputFile, option);

    University::encrypt("data.txt", "data.enc");

    outputFile.close();
    return 0;
}
