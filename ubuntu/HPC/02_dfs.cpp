#include<iostream>
#include<vector>
#include<omp.h>
using namespace std;
const int MAXN=1e5;

vector<int>adj[MAXN+5];
bool visited[MAXN+5];

void dfs(int node){
    visited[node]=true;
    
    #pragma omp parallel for
    for (int i = 0; i < adj[node].size(); i++)
    {
        int next_node=adj[node][i];
        if (!visited[next_node])
        {
            dfs(next_node);
        }
        
    }
    
}

int main(){
    int n,m,sNode;
    cout<<"Enter total No. of Nodes and edges: ";
    cin>>n>>m;
    cout<<"Enter edges"<<endl;

    for (int i = 1; i <=m; i++)
    {
        int u,v;
        cin>>u>>v;
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    cout<<"Enter start node: ";
    cin>>sNode;

    dfs(sNode);

    for (int i = 1; i <= n; i++)
    {
        if (visited[i]) 
        {
            cout<<i<<" ";
        }
    }
    cout<<endl;

    return 0;
    
}