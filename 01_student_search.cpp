#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

struct Student {
    int id;
    char name[50];
    float cgpa;
};

void sortById(Student *list, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (list[j].id > list[j + 1].id) {
                Student temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

int linearSearch(Student *list, int count, int id) {
    for (int i = 0; i < count; i++) {
        if (list[i].id == id) {
            return i;
        }
    }
    return -1;
}

int binarySearch(Student *list, int count, int id) {
    int low = 0, high = count - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        if (list[mid].id == id) {
            return mid;
        } else if (list[mid].id < id) {
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }
    return -1;
}

void display(Student *list, int count) {
    if (count == 0) {
        cout << "No records found\n";
        return;
    }
    cout << "ID\tName\t\tCGPA\n";
    for (int i = 0; i < count; i++) {
        cout << list[i].id << "\t" << list[i].name << "\t\t" << list[i].cgpa << "\n";
    }
}

int main() {
    int capacity = 2, count = 0, choice;
    Student *list = (Student *)malloc(capacity * sizeof(Student));

    do {
        cout << "\n1. Add Student\n2. Display\n3. Linear Search by ID\n4. Binary Search by ID\n5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            if (count == capacity) {
                capacity = capacity * 2;
                list = (Student *)realloc(list, capacity * sizeof(Student));
                cout << "List expanded to capacity " << capacity << "\n";
            }
            cout << "Enter ID: ";
            cin >> list[count].id;
            cout << "Enter Name: ";
            cin >> list[count].name;
            cout << "Enter CGPA: ";
            cin >> list[count].cgpa;
            count++;
        } else if (choice == 2) {
            display(list, count);
        } else if (choice == 3) {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            int pos = linearSearch(list, count, id);
            if (pos == -1) {
                cout << "Student not found\n";
            } else {
                cout << "Found: " << list[pos].id << " " << list[pos].name << " " << list[pos].cgpa << "\n";
            }
        } else if (choice == 4) {
            int id;
            cout << "Enter ID to search: ";
            cin >> id;
            sortById(list, count);
            int pos = binarySearch(list, count, id);
            if (pos == -1) {
                cout << "Student not found\n";
            } else {
                cout << "Found: " << list[pos].id << " " << list[pos].name << " " << list[pos].cgpa << "\n";
            }
        }
    } while (choice != 5);

    free(list);
    return 0;
}
