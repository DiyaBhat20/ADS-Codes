#include <iostream>
#include <fstream>

using namespace std;

// Structure to represent student information
class Student 
{
	public:
	    int rollNumber;
	    char name[50];
	    char division;
	    char address[100];
};

// Function to add student information to the file
void addStudent() {
    ofstream outFile("D:\\Sem4\\ADS Assignments\\student.txt", ios::binary | ios::app);
    if (outFile.fail()==1) {
        cout << "Error opening file for writing!" << endl;
        return;
    }

    Student student;
    cout << "Enter Roll Number: ";
    cin >> student.rollNumber;
    cin.ignore(); // Ignore newline character
    cout << "Enter Name: ";
    cin.getline(student.name, 50);
    cout << "Enter Division: ";
    cin >> student.division;
    cout << "Enter Address: ";
    cin.ignore(); // Ignore newline character
    cin.getline(student.address, 100);

    outFile.write((char*)(&student), sizeof(student));

    outFile.close();
}

// Function to display information of a particular student
void displayStudent(int rollNumber) {
    ifstream inFile("D:\\Sem4\\ADS Assignments\\student.txt", ios::binary);
    if (inFile.fail()==1) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    Student student;
    bool found = false;
    while (inFile.read((char*)(&student), sizeof(student))) {
        if (student.rollNumber == rollNumber) {
            cout << "Roll Number: " << student.rollNumber << endl;
            cout << "Name: " << student.name << endl;
            cout << "Division: " << student.division << endl;
            cout << "Address: " << student.address << endl;
            found = true;
            break;
        }
    }

    if (!found) {
        cout << "Student with Roll Number " << rollNumber << " not found." << endl;
    }

    inFile.close();
}

// Function to delete information of a particular student
void deleteStudent(int rollNumber) {
    ifstream inFile("D:\\Sem4\\ADS Assignments\\student.txt", ios::binary);
    if (inFile.fail()==1) {
        cout << "Error opening file for reading!" << endl;
        return;
    }

    ofstream tempFile("D:\\Sem4\\ADS Assignments\\temp.txt", ios::binary);
    if (tempFile.fail()) {
        cout << "Error creating temporary file!" << endl;
        inFile.close();
        return;
    }

    Student student;
    bool found = false;
    while (inFile.read((char*)(&student), sizeof(student))) {
        if (student.rollNumber == rollNumber) {
            found = true;
            continue; // Skip writing this student to temp file (effectively deleting)
        }
        tempFile.write((char*)(&student), sizeof(student));
    }

    inFile.close();
    tempFile.close();

    // Remove the original file
    remove("D:\\Sem4\\ADS Assignments\\student.txt");
    // Rename temp file to original file name
    rename("D:\\Sem4\\ADS Assignments\\temp.txt", "D:\\Sem4\\ADS Assignments\\student.txt");

    if (found) {
        cout << "Student with Roll Number " << rollNumber << " deleted successfully." << endl;
    } else {
        cout << "Student with Roll Number " << rollNumber << " not found." << endl;
    }
}

int main() {
    int choice;
    do {
        cout << "\n1. Add Student\n2. Display Student\n3. Delete Student\n4. Exit\nEnter your choice: ";
        cin >> choice;
        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2: {
                int rollNumber;
                cout << "Enter Roll Number: ";
                cin >> rollNumber;
                displayStudent(rollNumber);
                break;
            }
            case 3: {
                int rollNumber;
                cout << "Enter Roll Number to delete: ";
                cin >> rollNumber;
                deleteStudent(rollNumber);
                break;
            }
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

