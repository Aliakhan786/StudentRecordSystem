#include <iostream>   
#include <fstream>    
#include <iomanip>    
using namespace std;
struct Student {
    int rollNo;
    char name[50];
    float marks;
    char grade;
};
void addStudent();
void viewAllStudents();
void searchStudent();
void updateStudent();
void deleteStudent();
int main() {
    int choice;

    while (true) {
        cout << "\n===== Student Record Management System =====\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Update Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: addStudent(); break;
            case 2: viewAllStudents(); break;
            case 3: searchStudent(); break;
            case 4: updateStudent(); break;
            case 5: deleteStudent(); break;
            case 6: cout << "Exiting program...\n"; exit(0);
            default: cout << "Invalid choice! Try again.\n";
        }
    }
    cout << "\nDeveloped by: Aaliya Khan - C++ Intern at Pedestal Techno World\n";

    return 0;
}
void addStudent() {
    Student s;
    ofstream file("students.dat", ios::binary | ios::app);

    cout << "Enter Roll No: ";
    cin >> s.rollNo;
    cout << "Enter Name: ";
    cin.ignore();
    cin.getline(s.name, 50);
    cout << "Enter Marks: ";
    cin >> s.marks;
    cout << "Enter Grade: ";
    cin >> s.grade;

    file.write((char*)&s, sizeof(s));
    file.close();
    cout << "Student added successfully.\n";
}
void viewAllStudents() {
    Student s;
    ifstream file("students.dat", ios::binary);

    cout << "\n--- Student Records ---\n";
    while (file.read((char*)&s, sizeof(s))) {
        cout << "Roll No : " << s.rollNo << "\n";
        cout << "Name    : " << s.name << "\n";
        cout << "Marks   : " << s.marks << "\n";
        cout << "Grade   : " << s.grade << "\n";
        cout << "-----------------------\n";
    }

    file.close();
}
void searchStudent() {
    Student s;
    int roll;
    bool found = false;
    ifstream file("students.dat", ios::binary);

    cout << "Enter Roll No to search: ";
    cin >> roll;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "\n--- Record Found ---\n";
            cout << "Name  : " << s.name << "\n";
            cout << "Marks : " << s.marks << "\n";
            cout << "Grade : " << s.grade << "\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student not found.\n";
}
void updateStudent() {
    Student s;
    int roll;
    bool found = false;
    fstream file("students.dat", ios::binary | ios::in | ios::out);

    cout << "Enter Roll No to update: ";
    cin >> roll;

    while (file.read((char*)&s, sizeof(s))) {
        if (s.rollNo == roll) {
            cout << "Enter new Name: ";
            cin.ignore(); cin.getline(s.name, 50);
            cout << "Enter new Marks: ";
            cin >> s.marks;
            cout << "Enter new Grade: ";
            cin >> s.grade;

            int pos = -1 * sizeof(s);
            file.seekp(pos, ios::cur); 
            file.write((char*)&s, sizeof(s));

            cout << "Record updated.\n";
            found = true;
            break;
        }
    }

    file.close();

    if (!found)
        cout << "Student not found.\n";
}
void deleteStudent() {
    Student s;
    int roll;
    bool found = false;

    ifstream inFile("students.dat", ios::binary);
    ofstream outFile("temp.dat", ios::binary);

    cout << "Enter Roll No to delete: ";
    cin >> roll;

    while (inFile.read((char*)&s, sizeof(s))) {
        if (s.rollNo != roll)
            outFile.write((char*)&s, sizeof(s));
        else
            found = true;
    }

    inFile.close();
    outFile.close();

    remove("students.dat");
    rename("temp.dat", "students.dat");

    if (found)
        cout << "Record deleted successfully.\n";
    else
        cout << "Student not found.\n";
}
