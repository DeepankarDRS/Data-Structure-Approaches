#include <bits/stdc++.h>
using namespace std;

/*
-----------------------------------------
Optimal Approach: Count Inversions using Merge Sort
-----------------------------------------
Concept:
An inversion is a pair (i, j) such that i < j and arr[i] > arr[j].

We use a modified merge sort:
1. Divide the array into two halves.
2. Recursively count inversions in left half and right half.
3. While merging, count cross-inversions (where an element from left half is greater than an element from right half).
4. Sum up the counts.

Time Complexity: O(n log n)
-----------------------------------------
Dry Run Example: arr = {5, 3, 2, 1, 4}
Sorted merges with count calculation:
- Left: {5,3} → inversions: (5,3)
- Right: {2,1,4}
    → {2,1} → inversions: (2,1)
    → Merge with 4 → (none extra)
- Cross-inversions:
    (5,2), (5,1), (5,4), (3,2), (3,1)
Total inversions = 7

-----------------------------------------
*/

int merge(vector<int> &arr, int low, int mid, int high) {
    vector<int> temp;      // Temporary array for sorted merge
    int left = low;        // Start index of left half
    int right = mid + 1;   // Start index of right half
    int cnt = 0;           // Count of inversions

    // Merge process
    while (left <= mid && right <= high) {
        if (arr[left] <= arr[right]) {
            // No inversion — take from left
            temp.push_back(arr[left]);
            left++;
        }
        else {
            // Inversion found — all remaining elements in left half
            // will be greater than arr[right]
            temp.push_back(arr[right]);
            cnt += (mid - left + 1);
            right++;
        }
    }

    // Copy remaining left half
    while (left <= mid) {
        temp.push_back(arr[left]);
        left++;
    }

    // Copy remaining right half
    while (right <= high) {
        temp.push_back(arr[right]);
        right++;
    }

    // Copy back to original array
    for (int i = low; i <= high; i++) {
        arr[i] = temp[i - low];
    }

    return cnt;
}

int mergeSort(vector<int> &arr, int low, int high) {
    int cnt = 0;
    if (low >= high) return cnt; // Base case: 1 element → no inversions

    int mid = (low + high) / 2;
    cnt += mergeSort(arr, low, mid);       // Count in left half
    cnt += mergeSort(arr, mid + 1, high);  // Count in right half
    cnt += merge(arr, low, mid, high);     // Count cross-inversions

    return cnt;
}

int numberOfInversions(vector<int> &a, int n) {
    return mergeSort(a, 0, n - 1);
}

int main() {
    vector<int> a = {5, 3, 2, 1, 4};
    int n = a.size();

    // Count and print number of inversions
    int cnt = numberOfInversions(a, n);
    cout << "The number of inversions are: " << cnt << endl;

    /*
    Dry Run Output:
    Step 1: Split into {5,3} and {2,1,4}
    Step 2: Count inversions in each half
    Step 3: Merge and count cross inversions
    Final Answer:7 inversions
    */
    return 0;
}
