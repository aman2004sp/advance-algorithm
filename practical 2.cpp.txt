#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
using namespace std;

/*
 * Function to swap two elements.
 * Parameters:
 *  - a: First element
 *  - b: Second element
 * Swaps the values of the two elements.
 */
void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
}

/*
 * Partition function for dividing the array around a pivot element.
 * Parameters:
 *  - arr: The array to partition
 *  - low: Starting index
 *  - high: Ending index
 * Returns:
 *  - The index of the pivot element after partitioning.
 */
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[high]; // Choose the last element as pivot
    int i = low - 1; // Pointer for smaller elements

    // Traverse and place elements smaller than pivot to its left
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]); // Place pivot in correct position
    return i + 1; // Return pivot index
}

/*
 * Randomized partition function.
 * Randomly selects a pivot and partitions the array around it.
 * Parameters:
 *  - arr: The array to partition
 *  - low: Starting index
 *  - high: Ending index
 * Returns:
 *  - The index of the pivot element after partitioning.
 */
int randomizedPartition(vector<int>& arr, int low, int high) {
    srand(time(0)); // Seed for randomness
    int randomPivot = low + rand() % (high - low + 1); // Random pivot index
    swap(arr[randomPivot], arr[high]); // Move random pivot to end
    return partition(arr, low, high);
}

/*
 * Randomized Select function to find the ith smallest element.
 * Parameters:
 *  - arr: The array
 *  - low: Starting index
 *  - high: Ending index
 *  - i: The rank (1-based index) of the smallest element to find
 * Returns:
 *  - The ith smallest element in the array.
 * Logic:
 *  - Randomly partition the array and determine the position of the pivot.
 *  - Recursively search the left or right subarray based on the position of the pivot.
 */
int randomizedSelect(vector<int>& arr, int low, int high, int i) {
    if (low == high) {
        return arr[low]; // Only one element left
    }

    int pivotIndex = randomizedPartition(arr, low, high); // Partition around random pivot
    int k = pivotIndex - low + 1; // Position of pivot in sorted array

    if (i == k) {
        return arr[pivotIndex]; // The pivot is the ith smallest element
    } else if (i < k) {
        return randomizedSelect(arr, low, pivotIndex - 1, i); // Search left subarray
    } else {
        return randomizedSelect(arr, pivotIndex + 1, high, i - k); // Search right subarray
    }
}

int main() {
    // Prompt the user to input the array size and elements
    int n;
    cout << "Enter the number of elements in the array: ";
    cin >> n;

    vector<int> arr(n);
    cout << "Enter the elements of the array: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }

    // Ask the user for the rank of the smallest element to find
    int i;
    cout << "Enter the value of i (1-based index) to find the ith smallest element: ";
    cin >> i;

    // Validate input for i
    if (i < 1 || i > n) {
        cout << "Invalid value of i. It should be between 1 and " << n << "." << endl;
        return 1; // Exit program with error
    }

    // Find and display the ith smallest element
    int result = randomizedSelect(arr, 0, n - 1, i);
    cout << "The " << i << "th smallest element is: " << result << endl;

    return 0;
}



/*
 * Randomized Select Explanation:
 *
 * Purpose:
 *  - This program finds the ith smallest element in an unsorted array using the Randomized Select algorithm.
 *
 * Key Concepts:
 *  - Randomized Select is a variation of Quick Sort that partitions the array and focuses only on the relevant subarray.
 *  - Randomization reduces the likelihood of worst-case time complexity by randomly selecting a pivot element.
 *
 * Functions:
 *  1. `swap`: Exchanges two elements in the array.
 *  2. `partition`: Divides the array around a pivot such that smaller elements are on the left and larger on the right.
 *  3. `randomizedPartition`: Selects a random pivot and partitions the array.
 *  4. `randomizedSelect`: Recursively finds the ith smallest element in the partitioned subarray.
 *
 * Input:
 *  - The user enters the array size, elements, and the value of i.
 *
 * Output:
 *  - The program outputs the ith smallest element.
 *
 * Complexity:
 *  - Time Complexity:
 *     * Average Case: O(n) due to partitioning and focusing on one subarray.
 *     * Worst Case: O(n^2) if partitions are highly imbalanced (rare with randomization).
 *  - Space Complexity: O(log n) for the recursive stack.
 
 */
