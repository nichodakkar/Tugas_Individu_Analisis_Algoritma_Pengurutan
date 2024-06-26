#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm> 
using namespace std;
using namespace std::chrono;


void bubbleSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (arr[j] > arr[j+1]) {
                swap(arr[j], arr[j+1]);
            }
        }
    }
}

void insertionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; i++) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

void selectionSort(vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n-1; i++) {
        int minIdx = i;
        for (int j = i+1; j < n; j++) {
            if (arr[j] < arr[minIdx]) {
                minIdx = j;
            }
        }
        swap(arr[minIdx], arr[i]);
    }
}

void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;
    
    vector<int> L(n1), R(n2);
    for (int i = 0; i < n1; i++) {
        L[i] = arr[left + i];
    }
    for (int i = 0; i < n2; i++) {
        R[i] = arr[mid + 1 + i];
    }
    
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left >= right) {
        return;
    }
    int mid = left + (right - left) / 2;
    mergeSort(arr, left, mid);
    mergeSort(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high];
    int i = (low - 1);
    for (int j = low; j <= high - 1; j++) {
        if (arr[j] < pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return (i + 1);
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}


template <typename Func>
long long measureTime(Func sortFunc, vector<int>& arr) {
    auto start = high_resolution_clock::now();
    sortFunc(arr, 0, arr.size() - 1);
    auto stop = high_resolution_clock::now();
    auto duration = duration_cast<milliseconds>(stop - start);
    return duration.count();
}

int main() {
    vector<int> sizes = {10, 100, 500, 1000, 10000};
    for (int size : sizes) {
        vector<int> data(size);
        for (int i = 0; i < size; i++) {
            data[i] = rand() % 10000; 
        }

        vector<int> dataRandom = data;
        vector<int> dataReversed = data;
        vector<int> dataSorted = data;

        sort(dataSorted.begin(), dataSorted.end()); 
        sort(dataReversed.begin(), dataReversed.end(), greater<int>()); 

        cout << "Size: " << size << endl;

        
        cout << "Bubble Sort - Random: " << measureTime([](vector<int>& a, int, int) { bubbleSort(a); }, dataRandom) << "ms" << endl;
        cout << "Bubble Sort - Sorted: " << measureTime([](vector<int>& a, int, int) { bubbleSort(a); }, dataSorted) << "ms" << endl;
        cout << "Bubble Sort - Reversed: " << measureTime([](vector<int>& a, int, int) { bubbleSort(a); }, dataReversed) << "ms" << endl;

        
        cout << "Insertion Sort - Random: " << measureTime([](vector<int>& a, int, int) { insertionSort(a); }, dataRandom) << "ms" << endl;
        cout << "Insertion Sort - Sorted: " << measureTime([](vector<int>& a, int, int) { insertionSort(a); }, dataSorted) << "ms" << endl;
        cout << "Insertion Sort - Reversed: " << measureTime([](vector<int>& a, int, int) { insertionSort(a); }, dataReversed) << "ms" << endl;

        
        cout << "Selection Sort - Random: " << measureTime([](vector<int>& a, int, int) { selectionSort(a); }, dataRandom) << "ms" << endl;
        cout << "Selection Sort - Sorted: " << measureTime([](vector<int>& a, int, int) { selectionSort(a); }, dataSorted) << "ms" << endl;
        cout << "Selection Sort - Reversed: " << measureTime([](vector<int>& a, int, int) { selectionSort(a); }, dataReversed) << "ms" << endl;

        
        cout << "Merge Sort - Random: " << measureTime(mergeSort, dataRandom) << "ms" << endl;
        cout << "Merge Sort - Sorted: " << measureTime(mergeSort, dataSorted) << "ms" << endl;
        cout << "Merge Sort - Reversed: " << measureTime(mergeSort, dataReversed) << "ms" << endl;

        
        cout << "Quick Sort - Random: " << measureTime(quickSort, dataRandom) << "ms" << endl;
        cout << "Quick Sort - Sorted: " << measureTime(quickSort, dataSorted) << "ms" << endl;
        cout << "Quick Sort - Reversed: " << measureTime(quickSort, dataReversed) << "ms" << endl;
    }
    return 0;
}
