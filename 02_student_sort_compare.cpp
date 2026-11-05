#include <iostream>
#include <cstdlib>
#include <cstring>
using namespace std;

struct Student {
    int id;
    char name[50];
    float cgpa;
};

void sortByName(Student *list, int count) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (strcmp(list[j].name, list[j + 1].name) > 0) {
                Student temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

void sortByCgpa(Student *list, int count, bool ascending) {
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            bool swapNeeded;
            if (ascending) {
                swapNeeded = list[j].cgpa > list[j + 1].cgpa;
            } else {
                swapNeeded = list[j].cgpa < list[j + 1].cgpa;
            }
            if (swapNeeded) {
                Student temp = list[j];
                list[j] = list[j + 1];
                list[j + 1] = temp;
            }
        }
    }
}

int linearSearchByName(Student *list, int count, char *name, int &comparisons) {
    comparisons = 0;
    for (int i = 0; i < count; i++) {
        comparisons++;
        if (strcmp(list[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

int binarySearchByName(Student *list, int count, char *name, int &comparisons) {
    comparisons = 0;
    int low = 0, high = count - 1;
    while (low <= high) {
        int mid = (low + high) / 2;
        comparisons++;
        int result = strcmp(list[mid].name, name);
        if (result == 0) {
            return mid;
        } else if (result < 0) {
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
        cout << "\n1. Add Student\n2. Display\n3. Sort by Name\n4. Sort by CGPA Ascending\n";
        cout << "5. Sort by CGPA Descending\n6. Compare Search Performance (by Name)\n7. Exit\n";
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
            sortByName(list, count);
            cout << "Sorted by name\n";
            display(list, count);
        } else if (choice == 4) {
            sortByCgpa(list, count, true);
            cout << "Sorted by CGPA ascending\n";
            display(list, count);
        } else if (choice == 5) {
            sortByCgpa(list, count, false);
            cout << "Sorted by CGPA descending\n";
            display(list, count);
        } else if (choice == 6) {
            char name[50];
            int linearComparisons, binaryComparisons;
            cout << "Enter name to search: ";
            cin >> name;

            int pos1 = linearSearchByName(list, count, name, linearComparisons);
            cout << "Before sorting (Linear Search): ";
            if (pos1 == -1) cout << "Not found";
            else cout << "Found";
            cout << ", comparisons = " << linearComparisons << "\n";

            sortByName(list, count);

            int pos2 = binarySearchByName(list, count, name, binaryComparisons);
            cout << "After sorting (Binary Search): ";
            if (pos2 == -1) cout << "Not found";
            else cout << "Found";
            cout << ", comparisons = " << binaryComparisons << "\n";

            if (binaryComparisons < linearComparisons) {
                cout << "Binary search after sorting was faster\n";
            } else if (binaryComparisons == linearComparisons) {
                cout << "Both took the same number of comparisons\n";
            } else {
                cout << "Linear search was faster for this input\n";
            }
        }
    } while (choice != 7);

    free(list);
    return 0;
}
