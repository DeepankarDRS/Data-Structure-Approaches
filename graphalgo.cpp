#include <bits/stdc++.h>
using namespace std;

/* ========================
   🔹 DISJOINT SET UNION (Union-Find)
   - Connected components, cycle detection, MST (Kruskal)
   ======================== */
struct DSU {
    vector<int> parent, sz;
    DSU(int n) {
        parent.resize(n); sz.assign(n,1);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if(parent[x]==x) return x;
        return parent[x]=find(parent[x]);
    }
    bool unite(int a,int b){
        a=find(a); b=find(b);
        if(a==b) return false;
        if(sz[a]<sz[b]) swap(a,b);
        parent[b]=a; sz[a]+=sz[b];
        return true;
    }
};

/* ========================
   🔹 TARJAN'S Algorithm
   - Bridges & Articulation Points
   ======================== */
void tarjanDFS(int u,int p,vector<int>&disc,vector<int>&low,
               vector<vector<int>>&g,vector<pair<int,int>>&bridges,
               vector<int>&ap,int &time){
    disc[u]=low[u]=++time;
    int children=0;
    for(int v:g[u]){
        if(v==p) continue;
        if(!disc[v]){
            children++;
            tarjanDFS(v,u,disc,low,g,bridges,ap,time);
            low[u]=min(low[u],low[v]);
            if(low[v]>disc[u]) bridges.push_back({u,v}); // bridge
            if(low[v]>=disc[u] && p!=-1) ap[u]=1;        // articulation
        } else low[u]=min(low[u],disc[v]);
    }
    if(p==-1 && children>1) ap[u]=1;
}

/* ========================
   🔹 TARJAN'S SCC (Kosaraju alternative)
   ======================== */
void sccDFS(int u,vector<int>&disc,vector<int>&low,stack<int>&st,vector<int>&inStack,
            vector<vector<int>>&g,vector<vector<int>>&sccs,int &time){
    disc[u]=low[u]=++time; st.push(u); inStack[u]=1;
    for(int v:g[u]){
        if(!disc[v]) {
            sccDFS(v,disc,low,st,inStack,g,sccs,time);
            low[u]=min(low[u],low[v]);
        } else if(inStack[v]) low[u]=min(low[u],disc[v]);
    }
    if(low[u]==disc[u]){
        vector<int> comp;
        while(true){
            int v=st.top(); st.pop(); inStack[v]=0;
            comp.push_back(v);
            if(v==u) break;
        }
        sccs.push_back(comp);
    }
}

/* ========================
   🔹 KRUSKAL’S MST
   ======================== */
int kruskalMST(int n,vector<tuple<int,int,int>>&edges){
    sort(edges.begin(),edges.end(),[](auto &a,auto &b){return get<0>(a)<get<0>(b);});
    DSU dsu(n);
    int cost=0;
    for(auto [w,u,v]:edges)
        if(dsu.unite(u,v)) cost+=w;
    return cost;
}

/* ========================
   🔹 PRIM’S MST
   ======================== */
int primMST(int n, vector<vector<pair<int,int>>>&g){
    vector<int> key(n,INT_MAX), inMST(n,0);
    key[0]=0;
    priority_queue<pair<int,int>, vector<pair<int,int>>, greater<>> pq;
    pq.push({0,0});
    int cost=0;
    while(!pq.empty()){
        auto [w,u]=pq.top(); pq.pop();
        if(inMST[u]) continue;
        inMST[u]=1; cost+=w;
        for(auto [v,wt]:g[u])
            if(!inMST[v] && wt<key[v]){
                key[v]=wt;
                pq.push({wt,v});
            }
    }
    return cost;
}

int main(){
    int n=5;
    vector<tuple<int,int,int>> edges={{1,0,1},{2,0,2},{3,1,2},{4,1,3},{5,2,4}};
    cout<<"Kruskal MST cost: "<<kruskalMST(n,edges)<<"\n";

    vector<vector<pair<int,int>>> g(n);
    g[0]={{1,1},{2,2}};
    g[1]={{0,1},{2,3},{3,4}};
    g[2]={{0,2},{1,3},{4,5}};
    g[3]={{1,4}};
    g[4]={{2,5}};
    cout<<"Prim MST cost: "<<primMST(n,g)<<"\n";

    // Tarjan Bridges + Articulation
    vector<vector<int>> g2={{1,2},{0,2},{0,1,3,4},{2,4},{2,3}};
    vector<int> disc(n,0), low(n,0), ap(n,0); int time=0;
    vector<pair<int,int>> bridges;
    tarjanDFS(0,-1,disc,low,g2,bridges,ap,time);
    cout<<"Bridges: "; for(auto &b:bridges) cout<<"("<<b.first<<","<<b.second<<") ";
    cout<<"\nArticulation Points: "; for(int i=0;i<n;i++) if(ap[i]) cout<<i<<" ";
    cout<<"\n";

    // Tarjan SCC
    vector<vector<int>> g3={{1},{2,3},{0},{4},{}};
    disc.assign(5,0); low.assign(5,0);
    vector<int> inStack(5,0); stack<int> st; time=0;
    vector<vector<int>> sccs;
    for(int i=0;i<5;i++) if(!disc[i]) sccDFS(i,disc,low,st,inStack,g3,sccs,time);
    cout<<"SCCs: "; for(auto &comp:sccs){ cout<<"{"; for(int x:comp) cout<<x<<" "; cout<<"} "; }
    cout<<"\n";

    return 0;
}
