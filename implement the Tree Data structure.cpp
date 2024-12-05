#include <iostream>
using namespace std;

/*
 * Node structure for the Binary Search Tree (BST).
 * Contains:
 *  - `data`: The value stored in the node.
 *  - `left`: Pointer to the left child.
 *  - `right`: Pointer to the right child.
 */
struct Node {
    int data;
    Node* left;
    Node* right;

    // Constructor to initialize a new node
    Node(int value) {
        data = value;
        left = nullptr;
        right = nullptr;
    }
};

/*
 * Class representing the Binary Search Tree.
 * Contains:
 *  - `insert`: Function to insert a new node.
 *  - `search`: Function to search for a value in the tree.
 */
class BinarySearchTree {
private:
    Node* root; // Root node of the tree

    // Helper function for insertion
    Node* insertHelper(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value); // Create a new node if position is found
        }

        // Recursively insert in the left or right subtree
        if (value < node->data) {
            node->left = insertHelper(node->left, value);
        } else if (value > node->data) {
            node->right = insertHelper(node->right, value);
        }

        return node;
    }

    // Helper function for searching
    bool searchHelper(Node* node, int value) {
        if (node == nullptr) {
            return false; // Value not found
        }

        if (node->data == value) {
            return true; // Value found
        } else if (value < node->data) {
            return searchHelper(node->left, value); // Search in the left subtree
        } else {
            return searchHelper(node->right, value); // Search in the right subtree
        }
    }

public:
    // Constructor to initialize the tree
    BinarySearchTree() {
        root = nullptr;
    }

    // Public function to insert a value
    void insert(int value) {
        root = insertHelper(root, value);
    }

    // Public function to search for a value
    bool search(int value) {
        return searchHelper(root, value);
    }
};

int main() {
    BinarySearchTree bst;
    int choice;

    cout << "Binary Search Tree Operations:" << endl;
    cout << "1. Insert" << endl;
    cout << "2. Search" << endl;
    cout << "3. Exit" << endl;

    while (true) {
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            int value;
            cout << "Enter the value to insert: ";
            cin >> value;
            bst.insert(value);
            cout << "Value inserted successfully!" << endl;
        } else if (choice == 2) {
            int value;
            cout << "Enter the value to search: ";
            cin >> value;
            if (bst.search(value)) {
                cout << "Value found in the tree!" << endl;
            } else {
                cout << "Value not found in the tree!" << endl;
            }
        } else if (choice == 3) {
            cout << "Exiting the program." << endl;
            break;
        } else {
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

/*
 * Binary Search Tree Implementation Explanation:
 *
 * Purpose:
 *  - This program implements a simple binary search tree (BST) with support for:
 *    1. Insert operation: Adds a new value to the tree.
 *    2. Search operation: Checks if a value exists in the tree.
 *
 * Key Concepts:
 *  - Insertion:
 *      * Recursively finds the correct position for the new value.
 *      * Values smaller than the current node go to the left subtree.
 *      * Values larger than the current node go to the right subtree.
 *  - Searching:
 *      * Recursively compares the search value with the current node.
 *      * Terminates if the value is found or if the subtree becomes empty.
 *
 * Input:
 *  - The user interacts with the program through a menu.
 *  - Choices: Insert a value, search for a value, or exit the program.
 *
 * Output:
 *  - Confirmation of insertion.
 *  - Search result: Whether the value exists in the tree.
 *
 * Complexity:
 *  - Time Complexity:
 *     * Insertion: O(h), where h is the height of the tree.
 *     * Search: O(h), where h is the height of the tree.
 *     * In a balanced tree, h = O(log n), where n is the number of nodes.
 *  - Space Complexity: O(h) for recursive calls.
 *
 * Example:
 *  - Input:
 *     Binary Search Tree Operations:
 *     1. Insert
 *     2. Search
 *     3. Exit
 *     Enter your choice: 1
 *     Enter the value to insert: 15
 *     Value inserted successfully!
 *     Enter your choice: 2
 *     Enter the value to search: 15
 *  - Output:
 *     Value found in the tree!
 */
