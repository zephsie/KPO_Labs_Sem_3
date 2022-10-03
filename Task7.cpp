#include <iostream>
#include <string>
#include <vector>
#include <fstream>

#define PASS_GRADE      8
#define ALL_STUDENTS    "students.txt"
#define BAD_STUDENTS    "bad_students.txt"
#define GOOD_STUDENTS   "good_students.txt"

using namespace std;

struct Student {
    string name;
    int group{};
    vector<int> marks;
};

vector<string> splitString(const string &str, const char delimiter) {
    vector<string> tokens;
    string token;

    for (char c: str) {
        if (c == delimiter) {
            tokens.push_back(token);
            token = "";
        } else {
            token += c;
        }
    }
    tokens.push_back(token);

    return tokens;
}

Student parseStudent(const string &line) {
    vector<string> tokens = splitString(line, ' ');
    Student student;

    student.name = tokens[0];
    student.group = stoi(tokens[1]);

    for (int i = 2; i < tokens.size(); i++) {
        student.marks.push_back(stoi(tokens[i]));
    }

    return student;
}

double getAverageMark(const vector<int> &marks) {
    double sum = 0;
    for (int mark: marks) {
        sum += mark;
    }
    return sum / marks.size();
}


void writeStudent(const Student &student, const string &filename) {
    ofstream file(filename, ios::app);

    file << student.name << " " << student.group << " ";

    for (int mark: student.marks) {
        file << mark << " ";
    }
    file << endl;
}

void sortStudents(const string &allStudentsFilename, const string &badStudentsFilename, const string &goodStudentsFilename, const int passGrade) {
    ifstream file(allStudentsFilename);

    string line;
    while (getline(file, line)) {
        vector<string> tokens = splitString(line, ' ');
        Student dummy = parseStudent(line);

        if (getAverageMark(dummy.marks) < passGrade) {
            writeStudent(dummy, badStudentsFilename);
        } else {
            writeStudent(dummy, goodStudentsFilename);
        }
    }
}

int main() {
    sortStudents(ALL_STUDENTS, BAD_STUDENTS, GOOD_STUDENTS, PASS_GRADE);
    return 0;
}