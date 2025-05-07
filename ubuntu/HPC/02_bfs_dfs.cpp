#include<iostream>
#include<vector>
#include<queue>
#include<omp.h>

using namespace std;

class Graph{
    int v;
    vector<vector<int>>adj;

    public:
        Graph(int v):v(v),adj(v){}

        void addEdge(int v,int w){
            adj[v].push_back(w);
        }

        void paralleDFS(int startVertex){
            vector<bool> visited(v,false);
            parallelDFSUtil(startVertex,visited);

        }

        parallelDFSUtil(int v,vector<bool>& visited){
            visited[v]=true;
            cout<<v<<" ";

            #pragma omg parallel for
            for (int i = 0; i < adj[v].size();++i )
            {
                int n=adj[v][i];
                if ((!visited[n]))
                {
                    parallelDFSUtil(n,visited);
                }
                
            }
            
        }


        void parallelBFS(int startVertex){
            vector<bool> visited(v,false);
            queue<int>q;

            visited[startVertex]=true;
            q.push(startVertex);

            while (!q.empty())
            {
                int v=q.front();
                q.pop();
                cout<<v<<" ";

                #pragma omp parallel for
                for (int i = 0; i < adj[v].size(); i++)
                {
                    int n=adj[v][i];
                    if (!visited[n])
                    {
                        visited[n]=true;
                        q.push(n);
                    }
                    
                }
                
            }
            
        }
};

int main(){
    Graph g(7);
    g.addEdge(0,1);
    g.addEdge(0,2);
    g.addEdge(1,3);
    g.addEdge(1,4);
    g.addEdge(2,5);
    g.addEdge(2,6);

    cout<<"Depth First Search (DFS):";
    g.parallelBFS(0);
    cout<<endl;

    cout<<"Breadth First Search (BFS): ";
    g.parallelBFS(0);
    cout<<endl;

    return 0;
}