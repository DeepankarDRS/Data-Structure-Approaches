#include <bits/stdc++.h>
using namespace std;

/* ========================
   🔹 MOORE’S VOTING (Majority > n/2)
   ======================== */
int majorityElement(vector<int>& nums) {
    int cand=-1, count=0;
    for(int x:nums){
        if(count==0){ cand=x; count=1; }
        else if(x==cand) count++;
        else count--;
    }
    // Verify candidate
    count=0;
    for(int x:nums) if(x==cand) count++;
    return (count>nums.size()/2)? cand : -1;
}

/* ========================
   🔹 BOYER–MOORE (Majority > n/3)
   ======================== */
vector<int> majorityElementN3(vector<int>& nums) {
    int cand1=-1,cand2=-1,c1=0,c2=0;
    for(int x:nums){
        if(x==cand1) c1++;
        else if(x==cand2) c2++;
        else if(c1==0){ cand1=x; c1=1; }
        else if(c2==0){ cand2=x; c2=1; }
        else { c1--; c2--; }
    }
    // Verify candidates
    c1=c2=0;
    for(int x:nums){
        if(x==cand1) c1++;
        else if(x==cand2) c2++;
    }
    vector<int> res;
    int n=nums.size();
    if(c1>n/3) res.push_back(cand1);
    if(c2>n/3) res.push_back(cand2);
    return res;
}

int main(){
    vector<int> nums1={2,2,1,1,1,2,2};
    cout<<"Majority > n/2: "<<majorityElement(nums1)<<"\n";

    vector<int> nums2={1,1,1,3,3,2,2,2};
    auto res=majorityElementN3(nums2);
    cout<<"Majority > n/3: "; for(int x:res) cout<<x<<" "; cout<<"\n";
    return 0;
}
