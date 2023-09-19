#include <bits/stdc++.h>
using namespace std;

// Hoare partition scheme
int partition2(vector<int> &arr, int low, int high) {
    int pivot = arr[low];
    int i = low - 1, j = high + 1;
    while (true) {
        do {
            ++i;
        } while (arr[i] < pivot);
        do {
            --j;
        } while (arr[j] > pivot);
        if (i >= j) {
            return j;
        }
        swap(arr[i], arr[j]);
    }
}

void quickSort(vector<int> &arr, int low, int high) {
    if (low < high) {
        int pivot = partition2(arr, low, high);
        quickSort(arr, low, pivot);
        quickSort(arr, pivot + 1, high);
    }
}

int main() {
    int n;
    cin >> n;
    vector<int> arr(n);
    for (auto &i : arr) {
        cin >> i;
    }
    quickSort(arr, 0, n - 1);
    for (auto &i : arr) {
        cout << i << " ";
    }
    cout << endl;
    return 0;
}
