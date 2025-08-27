#include <bits/stdc++.h>
using namespace std;

/* ========================
   🔹 MERGE INTERVALS
   ======================== */
// Merge overlapping intervals
vector<vector<int>> mergeIntervals(vector<vector<int>>& intervals) {
    vector<vector<int>> res;
    if(intervals.empty()) return res;
    sort(intervals.begin(), intervals.end());
    res.push_back(intervals[0]);
    for(int i=1;i<intervals.size();i++){
        if(intervals[i][0] <= res.back()[1]) // overlap
            res.back()[1] = max(res.back()[1], intervals[i][1]);
        else
            res.push_back(intervals[i]);
    }
    return res;
}

// Meeting Rooms (min # rooms required)
int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<int> start, end;
    for(auto &in:intervals){ start.push_back(in[0]); end.push_back(in[1]); }
    sort(start.begin(), start.end()); sort(end.begin(), end.end());
    int i=0,j=0,rooms=0,maxRooms=0;
    while(i<start.size()){
        if(start[i]<end[j]){ rooms++; i++; }
        else { rooms--; j++; }
        maxRooms=max(maxRooms,rooms);
    }
    return maxRooms;
}

/* ========================
   🔹 K-WAY MERGE
   ======================== */
// Merge K Sorted Lists
struct Node{
    int val, idx, list;
    bool operator>(const Node& other) const { return val>other.val; }
};

vector<int> mergeKSorted(vector<vector<int>>& lists){
    priority_queue<Node,vector<Node>,greater<Node>> pq;
    for(int i=0;i<lists.size();i++)
        if(!lists[i].empty())
            pq.push({lists[i][0],0,i});
    vector<int> res;
    while(!pq.empty()){
        auto cur=pq.top(); pq.pop();
        res.push_back(cur.val);
        if(cur.idx+1<lists[cur.list].size())
            pq.push({lists[cur.list][cur.idx+1],cur.idx+1,cur.list});
    }
    return res;
}

/* ========================
   🔹 SWEEP LINE
   ======================== */
// Overlap Count (max intervals overlapping)
int maxOverlap(vector<pair<int,int>>& intervals){
    vector<pair<int,int>> events;
    for(auto [s,e]:intervals){ events.push_back({s,1}); events.push_back({e,-1}); }
    sort(events.begin(),events.end());
    int cur=0,ans=0;
    for(auto [t,val]:events){
        cur+=val;
        ans=max(ans,cur);
    }
    return ans;
}

// Skyline Problem (basic sweep line)
vector<pair<int,int>> getSkyline(vector<vector<int>>& buildings){
    vector<pair<int,int>> events;
    for(auto &b:buildings){
        events.push_back({b[0],-b[2]}); // start (neg height)
        events.push_back({b[1], b[2]}); // end (pos height)
    }
    sort(events.begin(),events.end());
    multiset<int> heights={0};
    int prev=0;
    vector<pair<int,int>> res;
    for(auto [x,h]:events){
        if(h<0) heights.insert(-h); 
        else heights.erase(heights.find(h));
        int cur=*heights.rbegin();
        if(cur!=prev){ res.push_back({x,cur}); prev=cur; }
    }
    return res;
}

int main(){
    // Merge Intervals
    vector<vector<int>> intervals={{1,3},{2,6},{8,10},{15,18}};
    auto merged=mergeIntervals(intervals);
    cout<<"Merged Intervals: "; for(auto &v:merged) cout<<"["<<v[0]<<","<<v[1]<<"] "; cout<<"\n";
    
    // Meeting Rooms
    vector<vector<int>> meetings={{0,30},{5,10},{15,20}};
    cout<<"Min Meeting Rooms: "<<minMeetingRooms(meetings)<<"\n";

    // K-way Merge
    vector<vector<int>> lists={{1,4,7},{2,5,8},{3,6,9}};
    auto mergedList=mergeKSorted(lists);
    cout<<"K-way Merge: "; for(int x:mergedList) cout<<x<<" "; cout<<"\n";

    // Sweep Line (Max Overlap)
    vector<pair<int,int>> iv={{1,5},{2,6},{4,7},{5,8}};
    cout<<"Max Overlap: "<<maxOverlap(iv)<<"\n";

    // Skyline
    vector<vector<int>> buildings={{2,9,10},{3,7,15},{5,12,12},{15,20,10},{19,24,8}};
    auto skyline=getSkyline(buildings);
    cout<<"Skyline: "; for(auto [x,h]:skyline) cout<<"("<<x<<","<<h<<") "; cout<<"\n";

    return 0;
}
