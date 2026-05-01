// COMSC 210 | Lab 34 | Gillian Rhett
#include <iostream>
#include <vector>
#include <queue> // for breadth first search function and minimum spanning tree function
#include <algorithm> // for reversing a vector in the shortestPath function
#include <string> // for input validation
using namespace std;
const int SIZE = 8;
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
// I used ChatGPT because I have never used AI to write code before and ChatGPT is cheap (I ended up paying $8 for the good version) and has an easy user interface
void DFSUtil(const Graph&, int, vector<bool>&); // Recursive helper function for DFS()
void DFS(const Graph&, int); // main depth first search function
void BFS(const Graph&, int); // breadth first search funciton
void shortestPath(const Graph&, const vector<string>&, int, int); // finds and displays the shortest path between two nodes
void minimumSpanningTree(const Graph&, const vector<string>&); // displays the smallest (shortest total distance) version of the graph where every city is connected
int getInt(int); // my own function for validating user input

int main() {
    /* I commented out steps 1 and 2
    // Creates a vector of graph edges/weights
    vector<Edge> edges = {
        // (x, y, w) —> edge from x to y having weight w
        // {0,1,12},{0,2,8},{0,3,21},{2,3,6},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5} // from step 1
        // Step 2: Change the graph by deleting at least two nodes and adding at least six nodes. 
        //    Change the weights as well.
        //    I deleted nodes 1 and 3
        {0,2,8},{2,6,2},{5,6,6},{4,5,9},{2,4,4},{2,5,5},{4,7,1},{7,8,3},{6,9,10},{8,9,12},{8,10,7},
        {8,11,11},{8,12,14},{9,12,16}
    };
    // Creates graph
    Graph graph(edges);
    // Prints adjacency list representation of graph
    graph.printGraph();

    // driver to test the DFS function
    DFS(graph, 0);
    BFS(graph, 0);
    */

    // Step 3, also made by ChatGPT
    vector<string> cities = {
        "San Francisco", "Oakland", "San Jose",
        "Sacramento", "Fresno", "Los Angeles", "San Diego", 
        "Pleasant Hill" // I added this myself for fun
    };

    vector<Edge> routes = {
        {0, 1, 13},   // San Francisco <-> Oakland
        {0, 2, 48},   // San Francisco <-> San Jose
        {0, 3, 87},   // San Francisco <-> Sacramento
        {2, 3, 120},  // San Jose <-> Sacramento
        {2, 6, 460},  // San Jose <-> San Diego
        {5, 6, 120},  // Los Angeles <-> San Diego
        {4, 5, 220},  // Fresno <-> Los Angeles
        {2, 4, 150},  // San Jose <-> Fresno
        {2, 5, 340},  // San Jose <-> Los Angeles
        // I added these three myself:
        {1, 7, 19},   // Oakland <-> Pleasant Hill
        {2, 7, 49},   // San Jose <-> Pleasant Hill
        {3, 7, 68}    // Sacramento <-> Pleasant Hill
    };

    Graph map(routes);
/* commenting out the demos of steps before 6
    cout << "California Route Map\n";
    cout << "====================\n\n";

    for (int i = 0; i < SIZE; i++) {
        cout << cities[i] << " connects to:\n";

        for (const Pair& route : map.adjList[i]) {
            cout << "  -> " << cities[route.first]
                 << " (" << route.second << " miles)\n";
        }
        cout << endl;
    }

    cout << "Step 4: shortest path demo" << endl;
    cout << "\t0 San Francisco" << endl;
    cout << "\t1 Oakland" << endl;
    cout << "\t2 San Jose" << endl;
    cout << "\t3 Sacramento" << endl;
    cout << "\t4 Fresno" << endl;
    cout << "\t5 Los Angeles" << endl;
    cout << "\t6 San Diego" << endl;
    cout << "\t7 Pleasant Hill" << endl;
    cout << "First city" << endl;
    int city1 = getInt();
    cout << "Second city" << endl;
    int city2 = getInt();
    shortestPath(map, cities, city1, city2);

    cout << "\nStep 5: Minimum Spanning Tree\n";
    minimumSpanningTree(map, cities);
*/

    cout << "City Routes Menu:" << endl;
    cout << "[1] Display distances of all available routes to adjacent cities" << endl;
    cout << "[2] Display touring route (BFS)" << endl;
    cout << "[3] Display direct travel route (DFS)" << endl;
    cout << "[4] Calculate shortest path between two cities" << endl;
    cout << "[5] Find Minimum Spanning Tree" << endl;
    cout << "[0] Exit" << endl;
    cout << "Your choice ";

    int choice = 1;
    while (choice != 0) {
        choice = getInt(5);
        if(choice == 1) { // display all the nodes and edges
            cout << "California Route Map\n";
            cout << "====================\n\n";

            for (int i = 0; i < SIZE; i++) {
                cout << cities[i] << " connects to:\n";

                for (const Pair& route : map.adjList[i]) {
                    cout << "  -> " << cities[route.first]
                        << " (" << route.second << " miles)\n";
                }
                cout << endl;
            }
        }

        if(choice == 2) { // breadth first search
            cout << "= Touring Route =" << endl;
            cout << "Starting city ";
            int city = getInt(SIZE - 1);
            BFS(map, city); // TODO change this and 3 to let user pick the starting city
        }

        if(choice == 3) { // depth first search
            DFS(map, 0);
        }

        if(choice == 4) { // shortest path
            cout << "= Shortest path =" << endl;
            cout << "\t0 San Francisco" << endl;
            cout << "\t1 Oakland" << endl;
            cout << "\t2 San Jose" << endl;
            cout << "\t3 Sacramento" << endl;
            cout << "\t4 Fresno" << endl;
            cout << "\t5 Los Angeles" << endl;
            cout << "\t6 San Diego" << endl;
            cout << "\t7 Pleasant Hill" << endl;
            cout << "First city" << endl;
            int city1 = getInt(SIZE - 1);
            cout << "Second city" << endl;
            int city2 = getInt(SIZE - 1);
            shortestPath(map, cities, city1, city2);
        }

        if(choice == 5) {

        }

        if(choice == 0) {
            cout << "Goodbye" << endl;
        }
    }

    return 0;
}

 // ============================= FUNCTION DEFINITIONS ==============================================

void DFSUtil(const Graph& graph, int v, vector<bool>& visited) {
// Recursive helper function for DFS -- by ChatGPT
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


void DFS(const Graph& graph, int startVertex) {
// Depth First Search -- by ChatGPT
    vector<bool> visited(SIZE, false);

    cout << "DFS starting from vertex " << startVertex << ": " << endl; // TODO change this to city-relevant text

    DFSUtil(graph, startVertex, visited);
    cout << endl;
}

void BFS(const Graph& graph, int startVertex) {
// Breadth First Search -- by ChatGPT
    vector<bool> visited(SIZE, false);
    queue<int> q;

    // Mark the starting vertex as visited and enqueue it
    visited[startVertex] = true;
    q.push(startVertex);

    cout << "Breadth-First Search starting from vertex " << startVertex << ": " << endl; // TODO change this to city-relevant text

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        cout << current << " ";

        // Visit all adjacent vertices
        for (const Pair& neighbor : graph.adjList[current]) {
            int adjacentVertex = neighbor.first;

            if (!visited[adjacentVertex]) {
                visited[adjacentVertex] = true;
                q.push(adjacentVertex);
            }
        }
    }
    cout << endl;
}

void shortestPath(const Graph& graph, const vector<string>& cities, int start, int destination) {
// Finds the shortest path between two cities using Dijkstra's Algorithm -- by ChatGPT
    vector<int> distance(SIZE, INT_MAX);
    vector<int> previous(SIZE, -1);
    vector<bool> visited(SIZE, false);

    distance[start] = 0;

    for (int i = 0; i < SIZE; ++i) {
        int current = -1;
        int minDistance = INT_MAX;

        for (int j = 0; j < SIZE; ++j) {
            if (!visited[j] && distance[j] < minDistance) {
                minDistance = distance[j];
                current = j;
            }
        }

        if (current == -1) break;
        visited[current] = true;

        for (const Pair& neighbor : graph.adjList[current]) {
            int next = neighbor.first;
            int weight = neighbor.second;

            if (!visited[next] && distance[current] + weight < distance[next]) {
                distance[next] = distance[current] + weight;
                previous[next] = current;
            }
        }
    }

    if (distance[destination] == INT_MAX) {
        cout << "No route exists between " << cities[start]
             << " and " << cities[destination] << "." << endl;
        return;
    }

    vector<int> path;
    for (int at = destination; at != -1; at = previous[at]) {
        path.push_back(at);
    }

    reverse(path.begin(), path.end());

    cout << "Shortest route from " << cities[start]
         << " to " << cities[destination] << ": ";

    for (size_t i = 0; i < path.size(); ++i) {
        cout << cities[path[i]];
        if (i < path.size() - 1) cout << " -> ";
    }

    cout << " (" << distance[destination] << " miles)" << endl;
}

int getInt(int max) {
    int num_in = -1;
    string temp_input;
    while(num_in < 0 || num_in > max) {
        cout << "enter a number (0 to " << max << "): ";
        cin >> temp_input;
        try {
            num_in = stoi(temp_input);
        }
        catch(const exception& e) {
            cout << "invalid input";
            num_in = -1;
        }        
    }
    return num_in;
}

void minimumSpanningTree(const Graph& graph, const vector<string>& cities) {
// displays the smallest (shortest total distance) version of the graph where every city is connected -- by ChatGPT
    vector<int> key(SIZE, INT_MAX);     // Minimum weight to connect
    vector<int> parent(SIZE, -1);       // Store MST
    vector<bool> inMST(SIZE, false);    // Track included nodes

    key[0] = 0; // Start from node 0 (San Francisco)

    for (int count = 0; count < SIZE - 1; count++) {
        int u = -1;
        int minKey = INT_MAX;

        // Find vertex with minimum key not yet included
        for (int v = 0; v < SIZE; v++) {
            if (!inMST[v] && key[v] < minKey) {
                minKey = key[v];
                u = v;
            }
        }

        if (u == -1) break;

        inMST[u] = true;

        // Update adjacent vertices
        for (const Pair& neighbor : graph.adjList[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (!inMST[v] && weight < key[v]) {
                key[v] = weight;
                parent[v] = u;
            }
        }
    }

    cout << "\nMinimum Spanning Tree (MST):\n";
    int totalWeight = 0;

    for (int i = 1; i < SIZE; i++) {
        if (parent[i] != -1) {
            cout << cities[parent[i]] << " -> " 
                 << cities[i] << " (" << key[i] << " miles)\n";
            totalWeight += key[i];
        }
    }

    cout << "Total distance of MST: " << totalWeight << " miles\n";
}