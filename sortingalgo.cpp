#include <bits/stdc++.h>
using namespace std;

/* ========================
   🔹 TOPOLOGICAL SORT (Kahn’s Algorithm)
   ======================== */
vector<int> topoSort(int n, vector<vector<int>>& adj) {
    vector<int> indeg(n,0);
    for(int u=0;u<n;u++) for(int v:adj[u]) indeg[v]++;
    queue<int> q;
    for(int i=0;i<n;i++) if(indeg[i]==0) q.push(i);
    vector<int> order;
    while(!q.empty()){
        int u=q.front(); q.pop(); order.push_back(u);
        for(int v:adj[u]){
            if(--indeg[v]==0) q.push(v);
        }
    }
    return order.size()==n ? order : vector<int>{}; // empty if cycle
}

/* ========================
   🔹 CYCLIC SORT (1..n Arrays)
   ======================== */
// Places numbers at correct indices
void cyclicSort(vector<int>& nums) {
    int i=0;
    while(i<nums.size()){
        int correct=nums[i]-1;
        if(nums[i]!=nums[correct]) swap(nums[i],nums[correct]);
        else i++;
    }
}

/* ========================
   🔹 COUNTING SORT
   ======================== */
vector<int> countingSort(vector<int>& nums,int maxVal) {
    vector<int> cnt(maxVal+1,0), out(nums.size());
    for(int x:nums) cnt[x]++;
    for(int i=1;i<=maxVal;i++) cnt[i]+=cnt[i-1];
    for(int i=nums.size()-1;i>=0;i--){
        out[cnt[nums[i]]-1]=nums[i];
        cnt[nums[i]]--;
    }
    return out;
}

/* ========================
   🔹 RADIX SORT (base 10)
   ======================== */
void countingSortExp(vector<int>& arr,int exp){
    int n=arr.size();
    vector<int> output(n), cnt(10,0);
    for(int x:arr) cnt[(x/exp)%10]++;
    for(int i=1;i<10;i++) cnt[i]+=cnt[i-1];
    for(int i=n-1;i>=0;i--){
        int digit=(arr[i]/exp)%10;
        output[cnt[digit]-1]=arr[i];
        cnt[digit]--;
    }
    arr=output;
}
void radixSort(vector<int>& arr){
    int mx=*max_element(arr.begin(),arr.end());
    for(int exp=1; mx/exp>0; exp*=10)
        countingSortExp(arr,exp);
}

/* ========================
   🔹 QUICKSELECT (k-th element)
   ======================== */
int partition(vector<int>& arr,int l,int r){
    int pivot=arr[r],i=l;
    for(int j=l;j<r;j++){
        if(arr[j]<=pivot) swap(arr[i++],arr[j]);
    }
    swap(arr[i],arr[r]); return i;
}
int quickSelect(vector<int>& arr,int l,int r,int k){
    if(l==r) return arr[l];
    int pi=partition(arr,l,r);
    if(k==pi) return arr[k];
    else if(k<pi) return quickSelect(arr,l,pi-1,k);
    else return quickSelect(arr,pi+1,r,k);
}

int main(){
    // Topological Sort
    int n=4; vector<vector<int>> adj={{1,2},{2},{3},{}};
    auto topo=topoSort(n,adj);
    cout<<"Topo Sort: "; for(int x:topo) cout<<x<<" "; cout<<"\n";

    // Cyclic Sort
    vector<int> nums={3,1,5,4,2};
    cyclicSort(nums);
    cout<<"Cyclic Sorted: "; for(int x:nums) cout<<x<<" "; cout<<"\n";

    // Counting Sort
    vector<int> arr={4,2,2,8,3,3,1};
    auto cs=countingSort(arr,8);
    cout<<"Counting Sort: "; for(int x:cs) cout<<x<<" "; cout<<"\n";

    // Radix Sort
    vector<int> rs={170,45,75,90,802,24,2,66};
    radixSort(rs);
    cout<<"Radix Sort: "; for(int x:rs) cout<<x<<" "; cout<<"\n";

    // QuickSelect (k-th smallest, 0-indexed)
    vector<int> qs={7,10,4,3,20,15};
    int k=2;
    cout<<k<<"-th smallest: "<<quickSelect(qs,0,qs.size()-1,k)<<"\n";

    return 0;
}
