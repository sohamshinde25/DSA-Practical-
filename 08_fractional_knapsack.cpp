#include <iostream>
using namespace std;

struct Parcel {
    int id;
    float weight;
    float profit;
    float ratio;
};

int main() {
    int n;
    float capacity;
    Parcel parcels[100];

    cout << "Enter number of parcels: ";
    cin >> n;

    for (int i = 0; i < n; i++) {
        parcels[i].id = i + 1;
        cout << "Enter weight and profit of parcel " << i + 1 << ": ";
        cin >> parcels[i].weight >> parcels[i].profit;
        parcels[i].ratio = parcels[i].profit / parcels[i].weight;
    }

    cout << "Enter truck capacity: ";
    cin >> capacity;

    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (parcels[j].ratio < parcels[j + 1].ratio) {
                Parcel temp = parcels[j];
                parcels[j] = parcels[j + 1];
                parcels[j + 1] = temp;
            }
        }
    }

    float totalProfit = 0;
    float remaining = capacity;

    cout << "\nParcels loaded:\n";
    for (int i = 0; i < n && remaining > 0; i++) {
        if (parcels[i].weight <= remaining) {
            cout << "Parcel " << parcels[i].id << ": full\n";
            remaining -= parcels[i].weight;
            totalProfit += parcels[i].profit;
        } else {
            float fraction = remaining / parcels[i].weight;
            cout << "Parcel " << parcels[i].id << ": " << fraction * 100 << "% loaded\n";
            totalProfit += parcels[i].profit * fraction;
            remaining = 0;
        }
    }

    cout << "Maximum profit: " << totalProfit << "\n";

    return 0;
}
