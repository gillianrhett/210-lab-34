// COMSC 210 | Lab 34 | Gillian Rhett
#include <iostream>
#include <vector>
using namespace std;
const int SIZE = 7;
struct Edge {
    int src, dest, weight;
};

typedef pair<int, int> Pair; // Creates alias 'Pair' for the pair<int,int> data type

class Graph {
    public:
    // a vector of vectors of Pairs to represent an adjacency list
    vector<vector<Pair>> adjList;
    // Graph Constructor
    Graph(vector<Edge> const &edges) {
        // resize the vector to hold SIZE elements of type vector<Edge>
        adjList.resize(SIZE);
        // add edges to the directed graph
        for (auto &edge: edges) {
            int src = edge.src;
            int dest = edge.dest;
            int weight = edge.weight;
            // insert at the end
            adjList[src].push_back(make_pair(dest, weight));
            // for an undirected graph, add an edge from dest to src also
            adjList[dest].push_back(make_pair(src, weight));
        }
    }
    // Print the graph's adjacency list
    void printGraph() {
    cout << "Graph's adjacency list:" << endl;
    for (int i = 0; i < adjList.size(); i++) {
        cout << i << " --> ";
        for (Pair v : adjList[i])
            cout << "(" << v.first << ", " << v.second << ") ";
            cout << endl;
        }
    }
};

// function prototypes
// I used ChatGPT because I have never used AI to write code before and ChatGPT is free and has an easy user interface
void DFSUtil(const Graph& graph, int v, vector<bool>& visited); // Recursive helper function
void DFS(const Graph& graph, int startVertex); // Main DFS function

int main() {
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5}
    };
    // Creates graph
    Graph graph(edges);
    // Prints adjacency list representation of graph
    graph.printGraph();

    // driver to test the DFS function
    DFS(graph, )

    return 0;
}

// Recursive helper function -- by ChatGPT
void DFSUtil(const Graph& graph, int v, vector<bool>& visited) {
    visited[v] = true;
    cout << v << " ";

    // Visit all adjacent vertices
    for (const Pair& neighbor : graph.adjList[v]) {
        int adjacentVertex = neighbor.first;
        if (!visited[adjacentVertex]) {
            DFSUtil(graph, adjacentVertex, visited);
        }
    }
}

// Main DFS function -- by ChatGPT
void DFS(const Graph& graph, int startVertex) {
    vector<bool> visited(SIZE, false);

    cout << "DFS starting from vertex " << startVertex << ": ";

    DFSUtil(graph, startVertex, visited);
    cout << endl;
}