#include <iostream>
using namespace std;

/*
 * A B-Tree node structure.
 * Contains:
 *  - `keys`: Array of keys in the node.
 *  - `t`: Minimum degree of the B-Tree (defines the range for the number of keys).
 *  - `children`: Array of child pointers.
 *  - `n`: Current number of keys in the node.
 *  - `leaf`: Boolean to indicate if the node is a leaf.
 */
class BTreeNode {
public:
    int* keys;          // Array of keys
    int t;              // Minimum degree
    BTreeNode** children; // Array of child pointers
    int n;              // Current number of keys
    bool leaf;          // True if the node is a leaf

    // Constructor for BTreeNode
    BTreeNode(int _t, bool _leaf);

    // Function to traverse all nodes in a subtree rooted at this node
    void traverse();

    // Function to insert a new key in a non-full node
    void insertNonFull(int k);

    // Function to split the child of this node
    void splitChild(int i, BTreeNode* y);

    // Friend class for accessing private members
    friend class BTree;
};

/*
 * A B-Tree class.
 * Contains:
 *  - Root node.
 *  - Minimum degree (t).
 */
class BTree {
private:
    BTreeNode* root; // Pointer to the root node
    int t;           // Minimum degree

public:
    // Constructor for BTree
    BTree(int _t) {
        root = nullptr;
        t = _t;
    }

    // Function to traverse the tree
    void traverse() {
        if (root != nullptr) {
            root->traverse();
        }
    }

    // Function to insert a new key
    void insert(int k);
};

// Constructor for BTreeNode
BTreeNode::BTreeNode(int _t, bool _leaf) {
    t = _t;
    leaf = _leaf;

    keys = new int[2 * t - 1];         // Allocate memory for keys
    children = new BTreeNode*[2 * t]; // Allocate memory for child pointers
    n = 0;                            // Initialize the number of keys as 0
}

// Function to traverse all nodes in a subtree
void BTreeNode::traverse() {
    int i;
    for (i = 0; i < n; i++) {
        if (!leaf) {
            children[i]->traverse(); // Recursively visit child nodes
        }
        cout << keys[i] << " "; // Print the key
    }

    if (!leaf) {
        children[i]->traverse(); // Visit the last child
    }
}

// Function to insert a new key in the B-Tree
void BTree::insert(int k) {
    if (root == nullptr) {
        root = new BTreeNode(t, true); // Create a new root
        root->keys[0] = k;            // Insert the key into the root
        root->n = 1;                  // Update the number of keys
    } else {
        if (root->n == 2 * t - 1) { // Root is full
            BTreeNode* newRoot = new BTreeNode(t, false); // Create a new root
            newRoot->children[0] = root;                 // Make old root a child

            newRoot->splitChild(0, root); // Split the old root

            int i = (newRoot->keys[0] < k) ? 1 : 0; // Determine which subtree to go to
            newRoot->children[i]->insertNonFull(k); // Insert in the appropriate subtree

            root = newRoot; // Update root
        } else {
            root->insertNonFull(k); // Insert in the non-full root
        }
    }
}

// Function to insert a key in a non-full node
void BTreeNode::insertNonFull(int k) {
    int i = n - 1; // Index of the rightmost key

    if (leaf) {
        while (i >= 0 && keys[i] > k) { // Find location for new key
            keys[i + 1] = keys[i]; // Shift keys to make space
            i--;
        }

        keys[i + 1] = k; // Insert the new key
        n++;             // Update the number of keys
    } else {
        while (i >= 0 && keys[i] > k) {
            i--; // Find child to descend
        }

        if (children[i + 1]->n == 2 * t - 1) { // Child is full
            splitChild(i + 1, children[i + 1]); // Split the child

            if (keys[i + 1] < k) {
                i++;
            }
        }
        children[i + 1]->insertNonFull(k); // Recur for the appropriate child
    }
}

// Function to split a full child
void BTreeNode::splitChild(int i, BTreeNode* y) {
    BTreeNode* z = new BTreeNode(y->t, y->leaf); // Create a new node
    z->n = t - 1;                               // Update the number of keys in the new node

    for (int j = 0; j < t - 1; j++) {
        z->keys[j] = y->keys[j + t]; // Move the last (t-1) keys to the new node
    }

    if (!y->leaf) {
        for (int j = 0; j < t; j++) {
            z->children[j] = y->children[j + t]; // Move the child pointers
        }
    }

    y->n = t - 1; // Update the number of keys in the old node

    for (int j = n; j >= i + 1; j--) {
        children[j + 1] = children[j]; // Shift children to make space
    }

    children[i + 1] = z; // Link the new child

    for (int j = n - 1; j >= i; j--) {
        keys[j + 1] = keys[j]; // Shift keys to make space
    }

    keys[i] = y->keys[t - 1]; // Move a key from the old node to the parent
    n++;                      // Increment the number of keys
}

int main() {
    int t, n;
    cout << "Enter the minimum degree (t) of the B-Tree: ";
    cin >> t;

    BTree bTree(t);

    cout << "Enter the number of keys to insert: ";
    cin >> n;

    cout << "Enter the keys: ";
    for (int i = 0; i < n; i++) {
        int key;
        cin >> key;
        bTree.insert(key);
    }

    cout << "Traversal of the B-Tree: ";
    bTree.traverse();
    cout << endl;

    return 0;
}
/*
 * B-Tree Implementation Explanation:
 *
 * Purpose:
 *  - The program implements a B-Tree, a self-balancing tree data structure optimized for disk-based storage.
 *
 * Key Concepts:
 *  - A B-Tree node contains a range of keys (up to 2t-1) and child pointers (up to 2t).
 *  - Keys are stored in sorted order, and nodes are split when they become full.
 *
 * Functions:
 *  1. `insert`: Handles the insertion of a key, splitting nodes as needed.
 *  2. `traverse`: Recursively traverses and prints the B-Tree in sorted order.
 *  3. `insertNonFull`: Inserts a key in a node that is not full.
 *  4. `splitChild`: Splits a full child node into two nodes and moves a key to the parent.
 *
 * Input:
 *  - Minimum degree (`t`) of the B-Tree.
 *  - Number of keys and the keys to insert.
 *
 * Output:
 *  - Traversal of the B-Tree after all keys are inserted.
 *
 * Complexity:
 *  - Time Complexity:
 *     * Search: O(log n)
 *     * Insertion: O(log n)
 *     * Deletion: O(log n)
 *  - Space Complexity: O(n)
 *
 * Example:
 *  - Input:
 *     Enter the minimum degree (t) of the B-Tree: 3
 *     Enter the number of keys to insert: 7
 *     Enter the keys: 10 20 5 6 12 30 7
 *  - Output:
 *     Traversal of the B-Tree: 5 6 7 10 12 20 30
 */
