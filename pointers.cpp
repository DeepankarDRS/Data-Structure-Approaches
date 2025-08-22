#include <bits/stdc++.h>
using namespace std;

/* ========================
   🔹 TWO POINTERS
   ======================== */

// Pair Sum in Sorted Array
bool pairSum(vector<int>& nums, int target) {
    int l = 0, r = nums.size() - 1;
    while (l < r) {
        int sum = nums[l] + nums[r];
        if (sum == target) return true;
        (sum < target) ? l++ : r--;
    }
    return false;
}

// Remove Duplicates (Sorted Array)
int removeDuplicates(vector<int>& nums) {
    int i = 0;
    for (int n : nums)
        if (i < 1 || n != nums[i-1]) nums[i++] = n;
    return i;
}

// 3-Sum (unique triplets)
vector<vector<int>> threeSum(vector<int>& nums) {
    vector<vector<int>> res;
    sort(nums.begin(), nums.end());
    for (int i = 0; i < nums.size(); i++) {
        if (i > 0 && nums[i] == nums[i-1]) continue;
        int l = i+1, r = nums.size()-1;
        while (l < r) {
            int sum = nums[i] + nums[l] + nums[r];
            if (sum == 0) { res.push_back({nums[i],nums[l],nums[r]});
                while (l < r && nums[l] == nums[l+1]) l++;
                while (l < r && nums[r] == nums[r-1]) r--;
                l++; r--;
            } else if (sum < 0) l++;
            else r--;
        }
    }
    return res;
}

// Trapping Rainwater
int trap(vector<int>& h) {
    int l=0, r=h.size()-1, lmax=0, rmax=0, ans=0;
    while(l<r){
        if(h[l]<h[r]){
            lmax=max(lmax,h[l]);
            ans+=lmax-h[l++];
        } else {
            rmax=max(rmax,h[r]);
            ans+=rmax-h[r--];
        }
    }
    return ans;
}

/* ========================
   🔹 SLIDING WINDOW
   ======================== */

// Longest Substring Without Repeating
int lengthOfLongestSubstring(string s) {
    unordered_map<char,int> mp;
    int l=0, ans=0;
    for(int r=0;r<s.size();r++){
        mp[s[r]]++;
        while(mp[s[r]]>1) mp[s[l++]]--;
        ans=max(ans,r-l+1);
    }
    return ans;
}

// Smallest Subarray ≥ K
int minSubArrayLen(int target, vector<int>& nums) {
    int l=0, sum=0, ans=INT_MAX;
    for(int r=0;r<nums.size();r++){
        sum+=nums[r];
        while(sum>=target){
            ans=min(ans,r-l+1);
            sum-=nums[l++];
        }
    }
    return ans==INT_MAX?0:ans;
}

// Max Sum of K-size Subarray
int maxSumK(vector<int>& nums, int k) {
    int sum=0, ans=0;
    for(int i=0;i<nums.size();i++){
        sum+=nums[i];
        if(i>=k-1){ ans=max(ans,sum); sum-=nums[i-k+1]; }
    }
    return ans;
}

/* ========================
   🔹 FAST–SLOW POINTERS
   ======================== */

// Cycle Detection (Floyd)
bool hasCycle(ListNode* head) {
    ListNode *slow=head,*fast=head;
    while(fast && fast->next){
        slow=slow->next;
        fast=fast->next->next;
        if(slow==fast) return true;
    }
    return false;
}

// Middle of Linked List
ListNode* middleNode(ListNode* head) {
    ListNode *slow=head,*fast=head;
    while(fast && fast->next){
        slow=slow->next; fast=fast->next->next;
    }
    return slow;
}

// Happy Number
bool isHappy(int n) {
    auto sqSum=[&](int x){int s=0; while(x){s+=(x%10)*(x%10); x/=10;} return s;};
    int slow=n, fast=sqSum(n);
    while(fast!=1 && slow!=fast){
        slow=sqSum(slow);
        fast=sqSum(sqSum(fast));
    }
    return fast==1;
}

int main() {
    // Quick test
    vector<int> nums={1,2,3,4,5};
    cout << "PairSum(9): " << pairSum(nums,9) << "\n";
    cout << "Max Sum K=2: " << maxSumK(nums,2) << "\n";
    cout << "Happy(19): " << isHappy(19) << "\n";
}
