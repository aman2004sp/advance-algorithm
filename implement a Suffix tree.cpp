#include <iostream>
#include <map>
#include <string>
using namespace std;

/*
 * Node structure for the Suffix Tree.
 * Contains:
 *  - `children`: A map of child nodes (keyed by characters).
 *  - `start`: The starting index of the substring represented by this edge.
 *  - `end`: The ending index of the substring (pointer for dynamic changes).
 *  - `suffixLink`: A pointer to another node for fast traversal (used in Ukkonen's algorithm).
 */
struct Node {
    map<char, Node*> children; // Children nodes
    int start;                 // Start index of the edge
    int* end;                  // End index of the edge (pointer for dynamic updates)
    Node* suffixLink;          // Suffix link for Ukkonen's algorithm

    // Constructor to initialize a new node
    Node(int start, int* end) {
        this->start = start;
        this->end = end;
        this->suffixLink = nullptr;
    }

    // Get the length of the edge
    int edgeLength() {
        return *end - start + 1;
    }
};

/*
 * Class to represent the Suffix Tree.
 * Contains:
 *  - `root`: Pointer to the root node of the tree.
 *  - `text`: The input string for which the suffix tree is built.
 */
class SuffixTree {
private:
    string text;
    Node* root;        // Root of the tree
    Node* activeNode;  // Active node during construction
    int activeEdge;    // Index of the active edge in the text
    int activeLength;  // Length of the active edge
    int remainingSuffixCount; // Suffixes yet to be added
    int* leafEnd;      // Pointer to the current end of all leaves
    int size;          // Length of the input string

    // Function to build the suffix tree
    void buildSuffixTree();

    // Helper function for traversal
    void traverseHelper(Node* node, int height, string& result);

public:
    // Constructor
    SuffixTree(const string& input);

    // Function to print the suffix tree
    void printSuffixTree();
};

// Constructor to initialize the suffix tree
SuffixTree::SuffixTree(const string& input) {
    text = input + "$"; // Append a unique character to the string
    size = text.size();
    root = new Node(-1, new int(-1)); // Root has no edge
    leafEnd = new int(-1);           // Initialize leaf end pointer
    buildSuffixTree();               // Build the tree
}

// Function to build the suffix tree using Ukkonen's algorithm
void SuffixTree::buildSuffixTree() {
    activeNode = root; // Start at the root
    activeEdge = -1;
    activeLength = 0;
    remainingSuffixCount = 0;

    for (int i = 0; i < size; i++) {
        (*leafEnd)++;
        remainingSuffixCount++;

        Node* lastCreatedInternalNode = nullptr;

        while (remainingSuffixCount > 0) {
            if (activeLength == 0) activeEdge = i;

            if (activeNode->children.find(text[activeEdge]) == activeNode->children.end()) {
                activeNode->children[text[activeEdge]] = new Node(i, leafEnd);

                if (lastCreatedInternalNode != nullptr) {
                    lastCreatedInternalNode->suffixLink = activeNode;
                    lastCreatedInternalNode = nullptr;
                }
            } else {
                Node* nextNode = activeNode->children[text[activeEdge]];

                if (activeLength >= nextNode->edgeLength()) {
                    activeEdge += nextNode->edgeLength();
                    activeLength -= nextNode->edgeLength();
                    activeNode = nextNode;
                    continue;
                }

                if (text[nextNode->start + activeLength] == text[i]) {
                    activeLength++;
                    if (lastCreatedInternalNode != nullptr) {
                        lastCreatedInternalNode->suffixLink = activeNode;
                        lastCreatedInternalNode = nullptr;
                    }
                    break;
                }

                int* splitEnd = new int(nextNode->start + activeLength - 1);
                Node* split = new Node(nextNode->start, splitEnd);
                activeNode->children[text[activeEdge]] = split;

                split->children[text[i]] = new Node(i, leafEnd);
                nextNode->start += activeLength;
                split->children[text[nextNode->start]] = nextNode;

                if (lastCreatedInternalNode != nullptr) {
                    lastCreatedInternalNode->suffixLink = split;
                }

                lastCreatedInternalNode = split;
            }

            remainingSuffixCount--;

            if (activeNode == root && activeLength > 0) {
                activeLength--;
                activeEdge = i - remainingSuffixCount + 1;
            } else if (activeNode != root) {
                activeNode = activeNode->suffixLink;
            }
        }
    }
}

// Helper function to traverse and collect substrings
void SuffixTree::traverseHelper(Node* node, int height, string& result) {
    if (node == nullptr) return;

    if (node->start != -1) {
        result += text.substr(node->start, node->edgeLength());
    }

    for (auto& child : node->children) {
        traverseHelper(child.second, height + child.second->edgeLength(), result);
        result += "\n";
    }
}

// Function to print the suffix tree
void SuffixTree::printSuffixTree() {
    string result;
    traverseHelper(root, 0, result);
    cout << "Suffix Tree:" << endl << result << endl;
}

int main() {
    string input;
    cout << "Enter the text to build the suffix tree: ";
    cin >> input;

    SuffixTree suffixTree(input);

    suffixTree.printSuffixTree();

    return 0;
}
/*
 * Suffix Tree Implementation Explanation:
 *
 * Purpose:
 *  - Efficiently represent all suffixes of a given string in a tree structure.
 *  - Enables efficient substring searching and other string operations.
 *
 * Key Concepts:
 *  - Each edge in the suffix tree represents a substring of the input.
 *  - Leaf nodes represent suffixes starting from different positions.
 *  - Ukkonen's algorithm is used for efficient construction in O(n) time.
 *
 * Steps:
 *  1. Append a unique character ('$') to the input to ensure no suffix is a prefix of another.
 *  2. Use active pointers (node, edge, length) to track the current construction state.
 *  3. Split nodes dynamically as new suffixes are added.
 *
 * Input:
 *  - A string provided by the user.
 *
 * Output:
 *  - Prints the suffix tree as edges with substrings.
 *
 * Complexity:
 *  - Time Complexity: O(n) for building the tree.
 *  - Space Complexity: O(n) for storing nodes and edges.
 *

 */

