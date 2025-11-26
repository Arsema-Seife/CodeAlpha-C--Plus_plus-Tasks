#include <iostream>
using namespace std;

struct Course {
    string coursename;
    double credithr;
    double grade;
};

int main() {
    int semesters;
    cout << "Enter number of semesters: ";
    cin >> semesters;

    double totalCredits = 0;
    double totalGradePoints = 0;

    for(int s = 1; s <= semesters; s++) {
        int n;
        cout << "\nSemester " << s << " - Enter number of courses: ";
        cin >> n;
        cin.ignore(); // clear newline

        Course courses[10]; // max 10 courses per semester

        for(int i = 0; i < n; i++) {
            cout << "Course " << i+1 << " name: ";
            getline(cin, courses[i].coursename);

            cout << "Credit hour: ";
            cin >> courses[i].credithr;

            // grade input with validation
            double g;
            cout << "Enter grade (4.0, 3.75, 3.5, 3.0, 2.75, 2.5, 2.0, 1.75, 1.5, 1.0, 0.0): ";
            cin >> g;
            while(!(g==4.0 || g==3.75 || g==3.5 || g==3.0 || g==2.75 || g==2.5 || g==2.0 || g==1.75 || g==1.5 || g==1.0 || g==0.0)) {
                cout << "Invalid grade. Enter again: ";
                cin >> g;
            }
            courses[i].grade = g;
            cin.ignore(); // clear newline
        }

        // calculate semester GPA
        double semCredits = 0;
        double semGradePoints = 0;
        for(int i = 0; i < n; i++) {
            semCredits += courses[i].credithr;
            semGradePoints += courses[i].grade * courses[i].credithr;
        }

        double semGPA = semGradePoints / semCredits;
        totalCredits += semCredits;
        totalGradePoints += semGradePoints;
        double CGPA = totalGradePoints / totalCredits;

        cout << "Semester " << s << " GPA: " << semGPA << endl;
        cout << "Current CGPA: " << CGPA << endl;


    cout << "\nFinal CGPA after " << semesters << " semesters: " << CGPA << endl;
    }
    return 0;
}
