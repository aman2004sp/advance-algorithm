#include <iostream>
#include <vector>
#include <climits>
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
 * Function to implement the Bellman-Ford algorithm.
 * Parameters:
 *  - edges: Vector of edges representing the graph
 *  - V: Number of vertices
 *  - E: Number of edges
 *  - source: The source vertex from which shortest paths are calculated
 * Prints:
 *  - Shortest distances from the source to all vertices
 *  - Reports if a negative weight cycle is detected
 */
void bellmanFord(vector<Edge>& edges, int V, int E, int source) {
    // Initialize distances from source to all vertices as infinite (INT_MAX)
    vector<int> distance(V, INT_MAX);
    distance[source] = 0;

    // Relax all edges (V-1) times
    for (int i = 1; i <= V - 1; i++) {
        for (const Edge& edge : edges) {
            if (distance[edge.src] != INT_MAX && distance[edge.src] + edge.weight < distance[edge.dest]) {
                distance[edge.dest] = distance[edge.src] + edge.weight;
            }
        }
    }

    // Check for negative weight cycles
    for (const Edge& edge : edges) {
        if (distance[edge.src] != INT_MAX && distance[edge.src] + edge.weight < distance[edge.dest]) {
            cout << "Graph contains a negative weight cycle!" << endl;
            return;
        }
    }

    // Print the shortest distances
    cout << "Vertex   Distance from Source" << endl;
    for (int i = 0; i < V; i++) {
        cout << i << "         " << (distance[i] == INT_MAX ? "INF" : to_string(distance[i])) << endl;
    }
}

int main() {
    // Input number of vertices and edges
    int V, E;
    cout << "Enter the number of vertices: ";
    cin >> V;
    cout << "Enter the number of edges: ";
    cin >> E;

    vector<Edge> edges(E);

    // Input the edges
    cout << "Enter the edges in the format (src dest weight):" << endl;
    for (int i = 0; i < E; i++) {
        cout << "Edge " << i + 1 << ": ";
        cin >> edges[i].src >> edges[i].dest >> edges[i].weight;
    }

    // Input the source vertex
    int source;
    cout << "Enter the source vertex: ";
    cin >> source;

    // Validate source vertex
    if (source < 0 || source >= V) {
        cout << "Invalid source vertex!" << endl;
        return 1;
    }

    // Call the Bellman-Ford algorithm
    bellmanFord(edges, V, E, source);

    return 0;
}
/*
 * Bellman-Ford Algorithm Explanation:
 *
 * Purpose:
 *  - This program calculates the shortest paths from a single source vertex to all other vertices in a graph.
 *  - It can handle graphs with negative weight edges.
 *  - Detects negative weight cycles and reports if one exists.
 *
 * Key Concepts:
 *  - The algorithm relaxes all edges V-1 times, where V is the number of vertices.
 *  - If a shorter path is found after V-1 iterations, it indicates a negative weight cycle.
 *
 * Functions:
 *  1. `bellmanFord`: Implements the core Bellman-Ford algorithm.
 *
 * Input:
 *  - The user inputs the number of vertices, edges, and the edges in the format `src dest weight`.
 *  - The user also specifies the source vertex.
 *
 * Output:
 *  - Shortest distances from the source to all vertices, or a message indicating a negative weight cycle.
 *
 * Complexity:
 *  - Time Complexity: O(V * E), where V is the number of vertices and E is the number of edges.
 *  - Space Complexity: O(V) for storing distances.
 *
 * Example:
 *  - Input:
 *     Enter the number of vertices: 5
 *     Enter the number of edges: 8
 *     Enter the edges in the format (src dest weight):
 *     Edge 1: 0 1 -1
 *     Edge 2: 0 2 4
 *     Edge 3: 1 2 3
 *     Edge 4: 1 3 2
 *     Edge 5: 1 4 2
 *     Edge 6: 3 2 5
 *     Edge 7: 3 1 1
 *     Edge 8: 4 3 -3
 *     Enter the source vertex: 0
 *  - Output:
 *     Vertex   Distance from Source
 *     0         0
 *     1         -1
 *     2         2
 *     3         -2
 *     4         1
 */

