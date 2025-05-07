#include <iostream>
#include <vector>
#include <omp.h>
using namespace std;
const int MAXN = 1e5;
vector<int> adj[MAXN + 5]; // adjacency list
bool visited[MAXN + 5];    // mark visited nodes
void dfs(int node)
{
    visited[node] = true;
#pragma omp parallel for
    for (int i = 0; i < adj[node].size(); i++)
    {
        int next_node = adj[node][i];
        if (!visited[next_node])
        {
            dfs(next_node);
        }
    }
}
int main()
{
    cout << "Please enter nodes and edges";
    int n, m; // number of nodes and edges
    cin >> n >> m;
    for (int i = 1; i <= m; i++)
    {
        int u, v; // edge between u and v
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }
    int start_node; // start node of DFS
    cin >> start_node;
    dfs(start_node);
    // Print visited nodes
    for (int i = 1; i <= n; i++)
    {
        if (visited[i])
        {
            cout << i << " ";
        }
    }
    cout << endl;
    return 0;
}


//  Create file using command- 
// Cat > filename.cpp 
//  Write code in terminal and press ctrl D to save the code 
//  To compile file use command-  
// g++ -o filename –fopenmp filename.cpp 
//  Run file using command- 
// ./filename
//




#include <iostream>
#include <vector>
#include <ctime>
#include <omp.h>
using namespace std;

const int MAXN = 1e5;

vector<int> adj[MAXN + 5];
bool visited_seq[MAXN + 5];
bool visited_par[MAXN + 5];
int n, m, sNode;

// Sequential DFS
void dfs_seq(int node) {
    visited_seq[node] = true;
    for (int i = 0; i < adj[node].size(); i++) {
        int next_node = adj[node][i];
        if (!visited_seq[next_node]) {
            dfs_seq(next_node);
        }
    }
}

// Parallel DFS (as-is, no changes)
void dfs_par(int node) {
    visited_par[node] = true;

    #pragma omp parallel for
    for (int i = 0; i < adj[node].size(); i++) {
        int next_node = adj[node][i];
        if (!visited_par[next_node]) {
            dfs_par(next_node);
        }
    }
}

int main() {
    cout << "Enter total number of nodes and edges: ";
    cin >> n >> m;

    cout << "Enter edges:\n";
    for (int i = 1; i <= m; i++) {
        int u, v;
        cin >> u >> v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout << "Enter start node: ";
    cin >> sNode;

    // Sequential DFS timing
    clock_t start_seq = clock();
    dfs_seq(sNode);
    clock_t end_seq = clock();
    double time_seq = double(end_seq - start_seq) / CLOCKS_PER_SEC;

    cout << "\nSequential DFS visited nodes:\n";
    for (int i = 1; i <= n; i++) {
        if (visited_seq[i]) cout << i << " ";
    }
    cout << "\nTime taken (Sequential DFS): " << time_seq << " seconds\n";

    // Parallel DFS timing
    double start_par = omp_get_wtime();
    dfs_par(sNode);
    double end_par = omp_get_wtime();
    double time_par = end_par - start_par;

    cout << "\nParallel DFS visited nodes:\n";
    for (int i = 1; i <= n; i++) {
        if (visited_par[i]) cout << i << " ";
    }
    cout << "\nTime taken (Parallel DFS): " << time_par << " seconds\n";

    return 0;
}

