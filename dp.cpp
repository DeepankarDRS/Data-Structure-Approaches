#include <bits/stdc++.h>
using namespace std;

/* ========================
   🔹 KADANE’S ALGORITHM
   ======================== */
int kadane(vector<int>& nums) {
    int best = nums[0], cur = nums[0];
    for(int i=1;i<nums.size();i++){
        cur = max(nums[i], cur+nums[i]);
        best = max(best, cur);
    }
    return best;
}
int maxCircularSubarray(vector<int>& nums) {
    int normal = kadane(nums);
    int total = accumulate(nums.begin(), nums.end(), 0);
    for(int &x: nums) x = -x;
    int minSub = -kadane(nums);
    return (minSub==total)? normal : max(normal,total-minSub);
}

/* ========================
   🔹 LCS
   ======================== */
int LCS(string a,string b){
    int n=a.size(), m=b.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dp[i][j] = (a[i-1]==b[j-1])? 1+dp[i-1][j-1]
                                        : max(dp[i-1][j], dp[i][j-1]);
    return dp[n][m];
}

/* ========================
   🔹 LIS
   ======================== */
int LIS(vector<int>& nums){
    vector<int> sub;
    for(int x: nums){
        auto it = lower_bound(sub.begin(),sub.end(),x);
        if(it==sub.end()) sub.push_back(x);
        else *it = x;
    }
    return sub.size();
}

/* ========================
   🔹 EDIT DISTANCE
   ======================== */
int editDistance(string a,string b){
    int n=a.size(), m=b.size();
    vector<vector<int>> dp(n+1,vector<int>(m+1,0));
    for(int i=0;i<=n;i++) dp[i][0]=i;
    for(int j=0;j<=m;j++) dp[0][j]=j;
    for(int i=1;i<=n;i++)
        for(int j=1;j<=m;j++)
            dp[i][j] = (a[i-1]==b[j-1])? dp[i-1][j-1]
                        : 1+min({dp[i-1][j], dp[i][j-1], dp[i-1][j-1]});
    return dp[n][m];
}

/* ========================
   🔹 COIN CHANGE
   ======================== */
int coinChangeMin(vector<int>& coins, int amt){
    vector<int> dp(amt+1,1e9);
    dp[0]=0;
    for(int c:coins)
        for(int x=c;x<=amt;x++)
            dp[x]=min(dp[x],1+dp[x-c]);
    return (dp[amt]>=1e9)? -1: dp[amt];
}
int coinChangeWays(vector<int>& coins, int amt){
    vector<int> dp(amt+1,0);
    dp[0]=1;
    for(int c:coins)
        for(int x=c;x<=amt;x++)
            dp[x]+=dp[x-c];
    return dp[amt];
}

/* ========================
   🔹 KNAPSACK
   ======================== */
int knapsack01(vector<int>& wt,vector<int>& val,int W){
    int n=wt.size();
    vector<int> dp(W+1,0);
    for(int i=0;i<n;i++)
        for(int w=W;w>=wt[i];w--)
            dp[w]=max(dp[w], val[i]+dp[w-wt[i]]);
    return dp[W];
}
int unboundedKnapsack(vector<int>& wt,vector<int>& val,int W){
    int n=wt.size();
    vector<int> dp(W+1,0);
    for(int i=0;i<n;i++)
        for(int w=wt[i];w<=W;w++)
            dp[w]=max(dp[w], val[i]+dp[w-wt[i]]);
    return dp[W];
}

/* ========================
   🔹 MCM
   ======================== */
int MCM(vector<int>& dims){
    int n=dims.size();
    vector<vector<int>> dp(n,vector<int>(n,0));
    for(int len=2;len<n;len++){
        for(int i=1;i+len-1<n;i++){
            int j=i+len-1;
            dp[i][j]=INT_MAX;
            for(int k=i;k<j;k++)
                dp[i][j]=min(dp[i][j], dp[i][k]+dp[k+1][j]+dims[i-1]*dims[k]*dims[j]);
        }
    }
    return dp[1][n-1];
}

/* ========================
   🔹 TREE DP (e.g., subtree sum)
   ======================== */
vector<vector<int>> g;
vector<int> subtree;
int dfsTreeDP(int u,int p){
    int sum=1;
    for(int v:g[u]) if(v!=p)
        sum+=dfsTreeDP(v,u);
    subtree[u]=sum;
    return sum;
}

/* ========================
   🔹 GRAPH DP (DAG longest path)
   ======================== */
int longestPathDAG(int n, vector<vector<int>>& edges){
    vector<vector<int>> adj(n);
    vector<int> indeg(n,0);
    for(auto &e:edges){ adj[e[0]].push_back(e[1]); indeg[e[1]]++; }
    queue<int> q; vector<int> dist(n,0);
    for(int i=0;i<n;i++) if(!indeg[i]) q.push(i);
    while(!q.empty()){
        int u=q.front(); q.pop();
        for(int v:adj[u]){
            dist[v]=max(dist[v],dist[u]+1);
            if(--indeg[v]==0) q.push(v);
        }
    }
    return *max_element(dist.begin(),dist.end());
}

/* ========================
   🔹 DIGIT DP (Sum of digits in [0..N])
   ======================== */
string num;
long long dpDigit[20][2][200];
long long digitDP(int pos,bool tight,int sum){
    if(pos==num.size()) return sum;
    long long &res=dpDigit[pos][tight][sum];
    if(res!=-1) return res;
    res=0;
    int limit = tight? num[pos]-'0':9;
    for(int d=0;d<=limit;d++)
        res+=digitDP(pos+1,tight&&(d==limit),sum+d);
    return res;
}
long long sumOfDigits(long long N){
    num=to_string(N);
    memset(dpDigit,-1,sizeof(dpDigit));
    return digitDP(0,true,0);
}

/* ========================
   🔹 BITMASK DP (TSP O(n^2 * 2^n))
   ======================== */
int tspDP[1<<15][15];
int tsp(vector<vector<int>>& dist,int mask,int pos){
    int n=dist.size();
    if(mask==(1<<n)-1) return dist[pos][0]; // return to start
    int &ans=tspDP[mask][pos];
    if(ans!=-1) return ans;
    ans=1e9;
    for(int city=0;city<n;city++){
        if(!(mask&(1<<city)))
            ans=min(ans, dist[pos][city]+tsp(dist,mask|(1<<city),city));
    }
    return ans;
}

/* ========================
   🔹 DRIVER
   ======================== */
int main(){
    vector<int> arr={-2,1,-3,4,-1,2,1,-5,4};
    cout<<"Kadane: "<<kadane(arr)<<"\n";

    cout<<"LCS(abc, ac): "<<LCS("abc","ac")<<"\n";

    vector<int> nums={10,9,2,5,3,7,101,18};
    cout<<"LIS: "<<LIS(nums)<<"\n";

    cout<<"Edit Dist (kitten->sitting): "<<editDistance("kitten","sitting")<<"\n";

    vector<int> coins={1,2,5};
    cout<<"Coin Change Min(11): "<<coinChangeMin(coins,11)<<"\n";
    cout<<"Coin Change Ways(5): "<<coinChangeWays(coins,5)<<"\n";

    vector<int> wt={1,3,4,5}, val={1,4,5,7};
    cout<<"Knapsack01(7): "<<knapsack01(wt,val,7)<<"\n";
    cout<<"Unbounded Knapsack(7): "<<unboundedKnapsack(wt,val,7)<<"\n";

    vector<int> dims={40,20,30,10,30};
    cout<<"MCM: "<<MCM(dims)<<"\n";

    // Tree DP example
    g={{1,2},{0,3},{0},{1}}; subtree.assign(4,0);
    dfsTreeDP(0,-1);
    cout<<"Subtree size of root: "<<subtree[0]<<"\n";

    // Graph DP example
    vector<vector<int>> edges={{0,1},{1,2},{0,2}};
    cout<<"Longest path in DAG: "<<longestPathDAG(3,edges)<<"\n";

    // Digit DP example
    cout<<"Sum of digits [0..99]: "<<sumOfDigits(99)<<"\n";

    // Bitmask DP example (TSP)
    vector<vector<int>> dist={{0,10,15,20},{10,0,35,25},{15,35,0,30},{20,25,30,0}};
    memset(tspDP,-1,sizeof(tspDP));
    cout<<"TSP cost: "<<tsp(dist,1,0)<<"\n";

    return 0;
}
