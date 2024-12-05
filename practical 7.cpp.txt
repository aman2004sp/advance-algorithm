#include <iostream>
#include <vector>
using namespace std;

/*
 * Function to compute the Longest Prefix Suffix (LPS) array.
 * The LPS array helps avoid redundant comparisons in the KMP algorithm.
 */
void computeLPSArray(const string& pattern, vector<int>& lps) {
    int length = 0; // Length of the previous longest prefix suffix
    int i = 1;
    lps[0] = 0; // lps[0] is always 0

    // Loop through the pattern to fill the LPS array
    while (i < pattern.size()) {
        if (pattern[i] == pattern[length]) {
            length++;
            lps[i] = length;
            i++;
        } else {
            if (length != 0) {
                length = lps[length - 1]; // Backtrack
            } else {
                lps[i] = 0;
                i++;
            }
        }
    }
}

/*
 * Function to implement the KMP algorithm for pattern searching.
 * It returns the starting indices of all occurrences of the pattern in the text.
 */
void KMPsearch(const string& text, const string& pattern) {
    int n = text.size();
    int m = pattern.size();

    // Step 1: Compute the LPS array
    vector<int> lps(m);
    computeLPSArray(pattern, lps);

    int i = 0; // Index for text
    int j = 0; // Index for pattern

    cout << "Pattern found at indices: ";
    while (i < n) {
        if (pattern[j] == text[i]) {
            i++;
            j++;
        }

        if (j == m) {
            // Pattern found, print the starting index
            cout << i - j << " ";
            j = lps[j - 1];
        } else if (i < n && pattern[j] != text[i]) {
            if (j != 0) {
                j = lps[j - 1]; // Use LPS to skip unnecessary comparisons
            } else {
                i++;
            }
        }
    }
    cout << endl;
}

int main() {
    string text, pattern;

    // Input text and pattern from the user
    cout << "Enter the text: ";
    getline(cin, text);
    cout << "Enter the pattern to search: ";
    getline(cin, pattern);

    // Call the KMP search function
    KMPsearch(text, pattern);

    return 0;
}
/*
 * Knuth-Morris-Pratt (KMP) Algorithm Explanation:
 *
 * Purpose:
 *  - Efficiently find all occurrences of a pattern in a given text.
 *  - Uses the LPS array to avoid redundant comparisons by "jumping" over unnecessary checks.
 *
 * Key Components:
 *  1. LPS Array:
 *      * LPS (Longest Prefix Suffix) stores the length of the longest prefix
 *        which is also a suffix for the pattern up to each position.
 *  2. Search Algorithm:
 *      * Compares characters of the pattern with the text.
 *      * When a mismatch occurs, uses the LPS array to determine how much to backtrack.
 *
 * Input:
 *  - `text`: The main string in which to search for the pattern.
 *  - `pattern`: The substring to search for.
 *
 * Output:
 *  - Prints the starting indices of all occurrences of the pattern in the text.
 *
 * Complexity:
 *  - Time Complexity:
 *     * LPS Array Construction: O(m), where m is the length of the pattern.
 *     * Search Operation: O(n), where n is the length of the text.
 *     * Total: O(n + m).
 *  - Space Complexity: O(m) for the LPS array.
 *
 * Example:
 *  - Input:
 *      Enter the text: ababcabcabababd
 *      Enter the pattern to search: abab
 *  - Output:
 *      Pattern found at indices: 0 7
 *
 * How It Works:
 *  - LPS Array for "abab": [0, 0, 1, 2]
 *  - Search progresses by comparing the pattern with the text.
 *  - When a mismatch occurs, the LPS array determines the next position to resume comparison.
 */
