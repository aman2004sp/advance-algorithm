#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

// Global variable to count comparisons
int comparisonCount = 0;

// Function to swap two elements
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

// Function to partition the array around a pivot
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Pivot element
    int i = low - 1; // Index of smaller element

    for (int j = low; j < high; j++) {
        comparisonCount++; // Increment comparison count
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

// Function to randomize the pivot element
int randomizedPartition(vector<int>& arr, int low, int high) {
    srand(time(0)); // Seed for randomness
    int randomPivot = low + rand() % (high - low + 1);
    swap(arr[randomPivot], arr[high]); // Move random pivot to end
    return partition(arr, low, high);
}

// Function to implement Quick Sort
void randomizedQuickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pivotIndex = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pivotIndex - 1); // Sort left of pivot
        randomizedQuickSort(arr, pivotIndex + 1, high); // Sort right of pivot
    }
}

// Function to print the array
void printArray(const vector<int>& arr) {
    for (int num : arr) {
        cout << num << " ";
    }
    cout << endl;
}

int main() {
    // Ask user for input
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    cout << "Original Array: ";
    printArray(arr);

    // Sort the array using Randomized Quick Sort
    randomizedQuickSort(arr, 0, n - 1);

    cout << "Sorted Array: ";
    printArray(arr);

    // Report the number of comparisons
    cout << "Number of Comparisons: " << comparisonCount << endl;

    return 0;
}



/*
 * Randomized Quick Sort Explanation:
 *
 * Purpose:
 *  - This program sorts an array of integers using the Randomized Quick Sort algorithm.
 *  - The program also calculates and displays the number of comparisons made during sorting.
 *
 * Key Concepts:
 *  - Quick Sort is a divide-and-conquer algorithm that partitions the array into two subarrays
 *    around a pivot element and recursively sorts the subarrays.
 *  - Randomized Quick Sort improves the average performance by choosing a random pivot, reducing
 *    the chances of encountering the worst-case scenario.
 *
 * Functions:
 *  1. `swap`: Exchanges the values of two elements in the array.
 *  2. `partition`: Reorders the elements of the array such that all elements smaller than the pivot
 *     are on the left, and all greater elements are on the right.
 *  3. `randomizedPartition`: Randomly selects a pivot by swapping a random element with the last
 *     element, then partitions the array around it.
 *  4. `randomizedQuickSort`: Recursively sorts the array by partitioning it around the pivot.
 *  5. `printArray`: Prints the elements of the array.
 *
 * Input:
 *  - The program prompts the user to enter the number of elements and the array itself.
 *
 * Output:
 *  - The sorted array in ascending order.
 *  - The number of comparisons made during sorting.
 *
 * Complexity:
 *  - Time Complexity:
 *     * Best/Average Case: O(n * log(n)) due to balanced partitions.
 *     * Worst Case: O(n^2) when partitions are highly imbalanced (rare with randomization).
 *  - Space Complexity: O(log(n)) due to recursive stack usage.
 *
 
 */
