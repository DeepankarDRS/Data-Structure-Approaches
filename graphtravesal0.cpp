#include <bits/stdc++.h>
using namespace std;

/* ========================
   🔹 BFS (Breadth-First Search)
   ======================== */

// Shortest path in unweighted graph
vector<int> bfsShortestPath(int n, vector<vector<int>>& adj, int src) {
    vector<int> dist(n, -1);
    queue<int> q; q.push(src); dist[src]=0;
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int v:adj[u]) if(dist[v]==-1){
            dist[v]=dist[u]+1; q.push(v);
        }
    }
    return dist;
}

// Bipartite Check
bool isBipartite(vector<vector<int>>& adj) {
    int n=adj.size();
    vector<int> color(n,-1);
    for(int i=0;i<n;i++) if(color[i]==-1){
        queue<int>q; q.push(i); color[i]=0;
        while(!q.empty()){
            int u=q.front(); q.pop();
            for(int v:adj[u]){
                if(color[v]==-1){ color[v]=!color[u]; q.push(v);}
                else if(color[v]==color[u]) return false;
            }
        }
    }
    return true;
}

/* ========================
   🔹 DFS (Depth-First Search)
   ======================== */

// Connected Components (Undirected)
void dfsComp(int u, vector<vector<int>>& adj, vector<int>& vis) {
    vis[u]=1;
    for(int v:adj[u]) if(!vis[v]) dfsComp(v,adj,vis);
}

// Cycle Detection (Directed Graph)
bool dfsCycle(int u, vector<vector<int>>& adj, vector<int>& vis, vector<int>& rec) {
    vis[u]=1; rec[u]=1;
    for(int v:adj[u]){
        if(!vis[v] && dfsCycle(v,adj,vis,rec)) return true;
        else if(rec[v]) return true;
    }
    rec[u]=0; return false;
}

// Topological Sort
void topoDFS(int u, vector<vector<int>>& adj, vector<int>& vis, stack<int>& st){
    vis[u]=1;
    for(int v:adj[u]) if(!vis[v]) topoDFS(v,adj,vis,st);
    st.push(u);
}

/* ========================
   🔹 Dijkstra
   ======================== */
vector<int> dijkstra(int n, vector<vector<pair<int,int>>>& adj, int src){
    vector<int> dist(n,1e9); dist[src]=0;
    priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>> pq;
    pq.push({0,src});
    while(!pq.empty()){
        auto [d,u]=pq.top(); pq.pop();
        if(d>dist[u]) continue;
        for(auto [v,w]:adj[u]){
            if(dist[v]>d+w){
                dist[v]=d+w;
                pq.push({dist[v],v});
            }
        }
    }
    return dist;
}

/* ========================
   🔹 Floyd–Warshall
   ======================== */
void floydWarshall(vector<vector<int>>& dist){
    int n=dist.size();
    for(int k=0;k<n;k++)
        for(int i=0;i<n;i++)
            for(int j=0;j<n;j++)
                if(dist[i][k]<1e9 && dist[k][j]<1e9)
                    dist[i][j]=min(dist[i][j],dist[i][k]+dist[k][j]);
}

/* ========================
   🔹 Bellman–Ford
   ======================== */
bool bellmanFord(int n, vector<tuple<int,int,int>>& edges, int src, vector<int>& dist){
    dist.assign(n,1e9); dist[src]=0;
    for(int i=1;i<n;i++){
        for(auto [u,v,w]:edges)
            if(dist[u]<1e9 && dist[v]>dist[u]+w)
                dist[v]=dist[u]+w;
    }
    // detect negative cycle
    for(auto [u,v,w]:edges)
        if(dist[u]<1e9 && dist[v]>dist[u]+w) return false;
    return true;
}

/* ========================
   🔹 Euler Tour (Tree Flatten)
   ======================== */
vector<int> tin, tout, flat;
int timer=0;
void eulerDFS(int u,int p,vector<vector<int>>& adj){
    tin[u]=++timer; flat.push_back(u);
    for(int v:adj[u]) if(v!=p) eulerDFS(v,u,adj);
    tout[u]=timer;
}

int main(){
    // Example Graph
    int n=5;
    vector<vector<int>> adj={{1,2},{0,3},{0,3},{1,2,4},{3}};
    vector<int> dist=bfsShortestPath(n,adj,0);
    cout<<"BFS dist from 0: "; for(int d:dist) cout<<d<<" "; cout<<"\n";

    cout<<"Is Bipartite? "<<isBipartite(adj)<<"\n";

    vector<int> vis(n,0);
    dfsComp(0,adj,vis);
    cout<<"Visited from DFS starting at 0: "; for(int x:vis) cout<<x<<" "; cout<<"\n";

    return 0;
}
