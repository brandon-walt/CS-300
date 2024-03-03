#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <algorithm>

using namespace std;

struct Course { 
    string number;
    string title;
    vector<string> prerequisites;
};

// Partition for quicksorting 
int partition (vector<Course> & courses, int low, int high) {
    string pivot = courses[(low + high ) / 2].number;
    while (low <= high) {
        while (courses[low].number < pivot) {
            low++;
        } 
        while (courses[high].number > pivot) {
            high--;
        }
        if (low <= high) {
            swap(courses[low], courses[high]);
            low++;
            high--;
        }
    }
    return low;
}

// Quicksort
void quickSort(vector<Course>& courses, int low, int high) {
    if (low < high) {
        int midpoint = partition(courses, low, high);
        quickSort(courses, low, midpoint -1);
        quickSort(courses, midpoint, high);
    }
}

// Function to read course data from file and load into vector of Course objects
void loadDataStructure(vector<Course>& courses, const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error"<< endl;
        return;
    }

    Course course;
    while (file >> course.number >> course.title) {
        string prerequisite;
        while (file >> prerequisite && prerequisite != "END") {
            course.prerequisites.push_back(prerequisite);
        }
        courses.push_back(course);
    }
    file.close();
}

// Print a list of all courses 
void printCourseList(const vector<Course>& courses) {
    cout << "Course List:\n";
    for (size_t i = 0; i < courses.size(); i++) {
        const Course& course = courses[i];
        cout << course.number << endl;
    }
}

// Binary search used to sort list of courses before printing
int binarySearch( const vector<Course>& courses, const string& courseNumber) {
    int low = 0;
    int high = courses.size() -1;

    while (low <= high) {
        int mid = low + (high - low) /2;
        const Course& course = courses[mid];

        if (course.number == courseNumber) {
            return mid;
        }
        else if (course.number < courseNumber) {
            low = mid + 1;
        }
        else {
            high = mid -1;
        }
    }

    return -1;
}

// Print course information
void printCourseInfo(const vector<Course>& courses, const string& courseNumber) {
    int index = binarySearch(courses, courseNumber);
    if (index != -1) {
        const Course& course = courses[index];
        cout << "Course Number: " << course.number << endl;
        cout << "Course Title: " << course.title << endl;
        cout << "Prerequisites:\n";
        for (size_t i = 0; i < course.prerequisites.size(); i++) {
            const string& prereq = course.prerequisites[i];
            cout << prereq << endl;
        }
    }
}

int main() {
    vector<Course> courses;
    string filename;

    // Menu
    while (true) {
        cout << "\nWelcome to the course planner.\n";
        cout << "1. Load Data Structure.\n";
        cout << "2. Print Course List.\n";
        cout << "3. Print Course.\n";
        cout << "4. Exit\n";
        cout << "What would you like to do? ";
        int choice;
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter file name: ";
                cin >> filename;
                loadDataStructure(courses, filename);
                break;
            case 2:
                if (courses.empty()) {
                    cout << "Error\n";
                } else {
                    // Sort courses before printing
                    quickSort(courses, 0, courses.size() - 1);
                    cout << "Here is a sample schedule: \n";
                    printCourseList(courses);
                }
                break;
            case 3:
                if (courses.empty()) {
                    cout << "Error\n";
                } else {
                    cout << "What course do you want to know about?";
                    string courseNumber;
                    cin >> courseNumber;
                    printCourseInfo(courses, courseNumber);
                }
                break;
            case 4:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << choice << " is not a valid option\n";
        }
    }

    return 0;
}