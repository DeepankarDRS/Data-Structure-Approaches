// ======================================================
// 📌 Greedy Algorithms — Master Cheat Sheet (C++)
// Covers all core greedy problems for contests/interviews
// ======================================================

#include <bits/stdc++.h>
using namespace std;

// ------------------------------------------------------
// 1️⃣ Activity Selection (Interval Scheduling)
// Greedy choice: pick activity that finishes earliest
int activitySelection(vector<pair<int,int>> intervals) {
    sort(intervals.begin(), intervals.end(), [](auto &a, auto &b){
        return a.second < b.second;   // sort by end time
    });

    int count = 0, lastEnd = -1e9;
    for (auto [start, end] : intervals) {
        if (start >= lastEnd) { // can attend
            count++;
            lastEnd = end;
        }
    }
    return count;
}

// ------------------------------------------------------
// 2️⃣ Minimum Meeting Rooms
// Variant of interval scheduling
int minMeetingRooms(vector<pair<int,int>> intervals) {
    vector<int> starts, ends;
    for (auto &iv : intervals) {
        starts.push_back(iv.first);
        ends.push_back(iv.second);
    }
    sort(starts.begin(), starts.end());
    sort(ends.begin(), ends.end());

    int rooms = 0, endPtr = 0;
    for (int i = 0; i < starts.size(); i++) {
        if (starts[i] < ends[endPtr]) rooms++;
        else endPtr++;
    }
    return rooms;
}

// ------------------------------------------------------
// 3️⃣ Huffman Coding
// Optimal prefix codes based on frequency
struct Node {
    char ch;
    int freq;
    Node *left, *right;
    Node(char c, int f) : ch(c), freq(f), left(NULL), right(NULL) {}
};
struct cmp {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};
void printCodes(Node* root, string code) {
    if (!root) return;
    if (root->ch != '#') cout << root->ch << " : " << code << "\n";
    printCodes(root->left, code + "0");
    printCodes(root->right, code + "1");
}
void huffmanCoding(vector<pair<char,int>> freq) {
    priority_queue<Node*, vector<Node*>, cmp> pq;
    for (auto &p : freq) pq.push(new Node(p.first, p.second));
    while (pq.size() > 1) {
        Node *l = pq.top(); pq.pop();
        Node *r = pq.top(); pq.pop();
        Node *merged = new Node('#', l->freq + r->freq);
        merged->left = l; merged->right = r;
        pq.push(merged);
    }
    printCodes(pq.top(), "");
}

// ------------------------------------------------------
// 4️⃣ Gas Station Problem
// Return index of start gas station to complete circle
int canCompleteCircuit(vector<int>& gas, vector<int>& cost) {
    int total = 0, curr = 0, start = 0;
    for (int i = 0; i < gas.size(); i++) {
        total += gas[i] - cost[i];
        curr += gas[i] - cost[i];
        if (curr < 0) {
            start = i + 1;
            curr = 0;
        }
    }
    return total >= 0 ? start : -1;
}

// ------------------------------------------------------
// 5️⃣ Job Scheduling with Deadlines & Profits
// Maximize profit by scheduling jobs before deadline
struct Job {
    int id, deadline, profit;
};
bool cmpJob(Job a, Job b) { return a.profit > b.profit; }
int jobScheduling(vector<Job> jobs) {
    sort(jobs.begin(), jobs.end(), cmpJob);
    int maxDeadline = 0;
    for (auto &j : jobs) maxDeadline = max(maxDeadline, j.deadline);
    vector<int> slot(maxDeadline+1, -1);

    int countJobs = 0, totalProfit = 0;
    for (auto &j : jobs) {
        for (int d = j.deadline; d > 0; d--) {
            if (slot[d] == -1) {
                slot[d] = j.id;
                countJobs++;
                totalProfit += j.profit;
                break;
            }
        }
    }
    cout << "Jobs done: " << countJobs << ", Profit: " << totalProfit << "\n";
    return totalProfit;
}

// ------------------------------------------------------
// 6️⃣ Fractional Knapsack
// Take fractions of items to maximize value/weight
struct Item {
    int value, weight;
};
bool cmpItem(Item a, Item b) {
    double r1 = (double)a.value / a.weight;
    double r2 = (double)b.value / b.weight;
    return r1 > r2;
}
double fractionalKnapsack(int W, vector<Item> items) {
    sort(items.begin(), items.end(), cmpItem);
    double ans = 0;
    for (auto &it : items) {
        if (W >= it.weight) {
            ans += it.value;
            W -= it.weight;
        } else {
            ans += (double)it.value * W / it.weight;
            break;
        }
    }
    return ans;
}

// ------------------------------------------------------
// 7️⃣ Minimum Spanning Tree (Kruskal) - Greedy
struct DSU {
    vector<int> parent, rank;
    DSU(int n): parent(n), rank(n,0) { iota(parent.begin(), parent.end(), 0); }
    int find(int x){ return parent[x]==x?x:parent[x]=find(parent[x]); }
    bool unite(int a, int b){
        a=find(a), b=find(b);
        if(a==b) return false;
        if(rank[a]<rank[b]) swap(a,b);
        parent[b]=a;
        if(rank[a]==rank[b]) rank[a]++;
        return true;
    }
};
int kruskalMST(int n, vector<tuple<int,int,int>> edges) {
    sort(edges.begin(), edges.end(), [](auto &a, auto &b){
        return get<2>(a) < get<2>(b);
    });
    DSU dsu(n);
    int cost=0;
    for(auto [u,v,w]: edges){
        if(dsu.unite(u,v)) cost += w;
    }
    return cost;
}

// ------------------------------------------------------
// 8️⃣ Optimal Merge Pattern (like file merge cost problem)
// Huffman-like greedy: always merge two smallest
int optimalMerge(vector<int> files) {
    priority_queue<int, vector<int>, greater<int>> pq(files.begin(), files.end());
    int cost = 0;
    while(pq.size() > 1) {
        int a = pq.top(); pq.pop();
        int b = pq.top(); pq.pop();
        cost += a+b;
        pq.push(a+b);
    }
    return cost;
}

// ------------------------------------------------------
// 🔟 Candy Distribution
// Distribute candies based on ratings, each child must have
// more candy than neighbor if rating higher
int candyDistribution(vector<int>& ratings) {
    int n = ratings.size();
    vector<int> candy(n,1);
    for(int i=1;i<n;i++)
        if(ratings[i]>ratings[i-1]) candy[i]=candy[i-1]+1;
    for(int i=n-2;i>=0;i--)
        if(ratings[i]>ratings[i+1]) candy[i]=max(candy[i],candy[i+1]+1);
    return accumulate(candy.begin(),candy.end(),0);
}

// ------------------------------------------------------
// 1️⃣1️⃣ Minimum Coins (Coin Change Greedy)
// Works when coin system is canonical (like Indian/US)
int minCoins(vector<int>& coins, int V) {
    sort(coins.rbegin(), coins.rend());
    int count=0;
    for(auto c: coins){
        count += V/c;
        V %= c;
    }
    return count;
}

// ------------------------------------------------------
int main() {
    // ✅ Activity Selection
    vector<pair<int,int>> intervals = {{1,3},{2,5},{4,6},{6,7},{5,9}};
    cout << "Max activities: " << activitySelection(intervals) << "\n";

    // ✅ Meeting Rooms
    vector<pair<int,int>> meetings = {{0,30},{5,10},{15,20}};
    cout << "Min rooms: " << minMeetingRooms(meetings) << "\n";

    // ✅ Huffman Coding
    vector<pair<char,int>> freq = {{'a',5},{'b',9},{'c',12},{'d',13},{'e',16},{'f',45}};
    cout << "Huffman Codes:\n"; huffmanCoding(freq);

    // ✅ Gas Station
    vector<int> gas = {1,2,3,4,5}, cost = {3,4,5,1,2};
    cout << "Gas start: " << canCompleteCircuit(gas,cost) << "\n";

    // ✅ Job Scheduling
    vector<Job> jobs = {{1,4,20},{2,1,10},{3,1,40},{4,1,30}};
    jobScheduling(jobs);

    // ✅ Fractional Knapsack
    vector<Item> items = {{60,10},{100,20},{120,30}};
    cout << "Knapsack value: " << fractionalKnapsack(50, items) << "\n";

    // ✅ Kruskal MST
    vector<tuple<int,int,int>> edges = {{0,1,10},{0,2,6},{0,3,5},{1,3,15},{2,3,4}};
    cout << "MST cost: " << kruskalMST(4,edges) << "\n";

    // ✅ Optimal Merge
    vector<int> files = {20,30,10,5,30};
    cout << "Optimal merge cost: " << optimalMerge(files) << "\n";

    // ✅ Candy Distribution
    vector<int> ratings = {1,0,2};
    cout << "Candies: " << candyDistribution(ratings) << "\n";

    // ✅ Min Coins
    vector<int> coins = {1,2,5,10,20,50,100,500,2000};
    cout << "Min coins: " << minCoins(coins, 121) << "\n";

    return 0;
}
