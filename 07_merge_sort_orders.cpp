#include <iostream>
using namespace std;

struct Order {
    int id;
    int time;
};

void merge(Order orders[], int left, int mid, int right) {
    Order temp[100];
    int i = left, j = mid + 1, k = left;

    while (i <= mid && j <= right) {
        if (orders[i].time <= orders[j].time) {
            temp[k++] = orders[i++];
        } else {
            temp[k++] = orders[j++];
        }
    }

    while (i <= mid) {
        temp[k++] = orders[i++];
    }

    while (j <= right) {
        temp[k++] = orders[j++];
    }

    for (int x = left; x <= right; x++) {
        orders[x] = temp[x];
    }
}

void mergeSort(Order orders[], int left, int right) {
    if (left < right) {
        int mid = (left + right) / 2;
        mergeSort(orders, left, mid);
        mergeSort(orders, mid + 1, right);
        merge(orders, left, mid, right);
    }
}

int main() {
    int n;
    Order orders[100];

    cout << "Enter number of orders: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        cout << "Enter order ID and delivery time (minutes): ";
        cin >> orders[i].id >> orders[i].time;
    }

    mergeSort(orders, 0, n - 1);

    cout << "\nOrders sorted by delivery time:\n";
    cout << "Order ID\tDelivery Time\n";
    for (int i = 0; i < n; i++) {
        cout << orders[i].id << "\t\t" << orders[i].time << "\n";
    }

    return 0;
}
