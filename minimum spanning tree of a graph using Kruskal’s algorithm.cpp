#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

/*
 * Structure to represent an edge of the graph.
 * Contains:
 *  - `src`: Source vertex
 *  - `dest`: Destination vertex
 *  - `weight`: Weight of the edge
 */
struct Edge {
    int src, dest, weight;
};

/*
 * Structure to represent a subset for union-find.
 * Contains:
 *  - `parent`: Parent of the subset
 *  - `rank`: Rank of the subset
 */
struct Subset {
    int parent, rank;
};

/*
 * Function to find the parent of an element in the union-find data structure.
 * Implements path compression for efficiency.
 * Parameters:
 *  - subsets: Vector of subsets
 *  - i: Element to find the parent for
 * Returns:
 *  - Parent of the element `i`.
 */
int find(vector<Subset>& subsets, int i) {
    if (subsets[i].parent != i) {
        subsets[i].parent = find(subsets, subsets[i].parent);
    }
    return subsets[i].parent;
}

/*
 * Function to perform union of two subsets.
 * Implements union by rank for efficiency.
 * Parameters:
 *  - subsets: Vector of subsets
 *  - x: First subset
 *  - y: Second subset
 */
void unionSubsets(vector<Subset>& subsets, int x, int y) {
    int rootX = find(subsets, x);
    int rootY = find(subsets, y);

    if (subsets[rootX].rank < subsets[rootY].rank) {
        subsets[rootX].parent = rootY;
    } else if (subsets[rootX].rank > subsets[rootY].rank) {
        subsets[rootY].parent = rootX;
    } else {
        subsets[rootY].parent = rootX;
        subsets[rootX].rank++;
    }
}

/*
 * Function to compare two edges by weight.
 * Used for sorting edges in ascending order.
 */
bool compareEdges(const Edge& e1, const Edge& e2) {
    return e1.weight < e2.weight;
}

int main() {
    // Input number of vertices and edges
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    // Input edges
    vector<Edge> edges(E);
    cout << "Enter the edges in the format (src dest weight):\n";
    for (int i = 0; i < E; i++) {
        cout << "Edge " << i + 1 << ": ";
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    // Sort edges in ascending order by weight
    sort(edges.begin(), edges.end(), compareEdges);

    // Create subsets for union-find
    vector<Subset> subsets(V);
    for (int v = 0; v < V; v++) {
        subsets[v].parent = v;
        subsets[v].rank = 0;
    }

    // Vector to store the result MST
    vector<Edge> mst;

    // Iterate through sorted edges and build MST
    for (const Edge& edge : edges) {
        int x = find(subsets, edge.src);
        int y = find(subsets, edge.dest);

        // If including this edge doesn't form a cycle
        if (x != y) {
            mst.push_back(edge);
            unionSubsets(subsets, x, y);
        }

        // Stop if MST has V-1 edges
        if (mst.size() == V - 1) {
            break;
        }
    }

    // Display the MST
    cout << "Minimum Spanning Tree (MST):\n";
    int totalWeight = 0;
    for (const Edge& edge : mst) {
        cout << edge.src << " -- " << edge.dest << " == " << edge.weight << endl;
        totalWeight += edge.weight;
    }
    cout << "Total weight of MST: " << totalWeight << endl;

    return 0;
}
/*
 * Kruskal's Algorithm Explanation:
 *
 * Purpose:
 *  - This program finds the Minimum Spanning Tree (MST) of a graph using Kruskal's algorithm.
 *  - It ensures the total weight of the MST is minimized without forming cycles.
 *
 * Key Concepts:
 *  - The graph is represented using edges with weights.
 *  - The edges are sorted by weight in ascending order.
 *  - A union-find data structure is used to detect cycles and merge subsets.
 *
 * Functions:
 *  1. `find`: Finds the root of a subset using path compression for efficiency.
 *  2. `unionSubsets`: Merges two subsets using union by rank.
 *  3. `compareEdges`: Compares two edges based on their weight for sorting.
 *
 * Input:
 *  - The user inputs the number of vertices and edges.
 *  - The user then provides each edge in the format: source vertex, destination vertex, weight.
 *
 * Output:
 *  - The edges included in the MST.
 *  - The total weight of the MST.
 *
 * Complexity:
 *  - Time Complexity:
 *     * Sorting edges: O(E * log(E))
 *     * Union-Find operations: O(E * log(V)) (amortized)
 *     Total: O(E * log(E) + E * log(V))
 *  - Space Complexity: O(V) for union-find subsets.
 *
 * Example:
 *  - Input:
 *     Enter the number of vertices: 4
 *     Enter the number of edges: 5
 *     Enter the edges in the format (src dest weight):
 *     Edge 1: 0 1 10
 *     Edge 2: 0 2 6
 *     Edge 3: 0 3 5
 *     Edge 4: 1 3 15
 *     Edge 5: 2 3 4
 *  - Output:
 *     Minimum Spanning Tree (MST):
 *     2 -- 3 == 4
 *     0 -- 3 == 5
 *     0 -- 1 == 10
 *     Total weight of MST: 19
 */
