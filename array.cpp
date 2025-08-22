#include <bits/stdc++.h>
using namespace std;

/* ======================================================
   🔹 PREFIX SUM
   ------------------------------------------------------
   - Precompute cumulative sums of an array.
   - Query any subarray sum [l,r] in O(1) time.
   - Applications: range sums, balance arrays, subarray checks.
   ====================================================== */
vector<int> buildPrefixSum(vector<int>& arr) {
    int n = arr.size();
    vector<int> pre(n+1, 0); // pre[0] = 0 (for convenience)
    for (int i = 0; i < n; i++)
        pre[i+1] = pre[i] + arr[i]; // cumulative sum
    return pre;
}

/* ======================================================
   🔹 SUFFIX SUM
   ------------------------------------------------------
   - Similar to prefix sum but built from the end.
   - Useful for reverse queries, partition problems,
     or when we need sums of suffixes.
   ====================================================== */
vector<int> buildSuffixSum(vector<int>& arr) {
    int n = arr.size();
    vector<int> suf(n+1, 0); // suf[n] = 0
    for (int i = n-1; i >= 0; i--)
        suf[i] = suf[i+1] + arr[i];
    return suf;
}

/* ======================================================
   🔹 DIFFERENCE ARRAY
   ------------------------------------------------------
   - Supports range updates efficiently.
   - Instead of updating each element in [l,r], we:
       diff[l] += val;
       diff[r+1] -= val;
   - Final array restored by prefix sum of diff.
   - Applications: interval increment problems, range ops.
   ====================================================== */
vector<int> applyRangeUpdates(vector<int> arr, vector<tuple<int,int,int>> updates) {
    int n = arr.size();
    vector<int> diff(n+1, 0);

    // Apply updates lazily in diff array
    for (auto [l,r,val] : updates) {
        diff[l] += val;
        if (r+1 < n) diff[r+1] -= val;
    }

    // Restore original array by prefix sum
    int curr = 0;
    for (int i = 0; i < n; i++) {
        curr += diff[i];
        arr[i] += curr;
    }
    return arr;
}

/* ======================================================
   🔹 PREFIX XOR
   ------------------------------------------------------
   - Similar to prefix sum but with XOR operation.
   - Helps in XOR subarray queries:
       XOR(l,r) = preXor[r+1] ^ preXor[l]
   - Applications: subarray XOR problems, parity checks.
   ====================================================== */
vector<int> buildPrefixXor(vector<int>& arr) {
    int n = arr.size();
    vector<int> preXor(n+1, 0); // preXor[0] = 0
    for (int i = 0; i < n; i++)
        preXor[i+1] = preXor[i] ^ arr[i];
    return preXor;
}

/* ======================================================
   🔹 SEGMENT TREE with LAZY PROPAGATION
   ------------------------------------------------------
   - Supports efficient range updates + range queries.
   - Normal segment tree updates a whole range in O(n).
   - Lazy Propagation defers updates until needed,
     making range update + query = O(log n).
   - Applications: range increment, interval problems.
   ====================================================== */
struct LazySegTree {
    int n;
    vector<int> tree, lazy;

    LazySegTree(int size) {
        n = size;
        tree.assign(4*n, 0);
        lazy.assign(4*n, 0);
    }

    // Build tree from array
    void build(vector<int>& arr, int idx, int l, int r) {
        if (l == r) {
            tree[idx] = arr[l];
            return;
        }
        int mid = (l+r)/2;
        build(arr, 2*idx, l, mid);
        build(arr, 2*idx+1, mid+1, r);
        tree[idx] = tree[2*idx] + tree[2*idx+1];
    }

    // Propagate pending updates
    void propagate(int idx, int l, int r) {
        if (lazy[idx] != 0) {
            tree[idx] += (r-l+1) * lazy[idx]; // update node
            if (l != r) { // push to children
                lazy[2*idx] += lazy[idx];
                lazy[2*idx+1] += lazy[idx];
            }
            lazy[idx] = 0; // clear lazy tag
        }
    }

    // Range update
    void update(int idx, int l, int r, int ql, int qr, int val) {
        propagate(idx, l, r);
        if (qr < l || r < ql) return; // no overlap
        if (ql <= l && r <= qr) {
            lazy[idx] += val;
            propagate(idx, l, r);
            return;
        }
        int mid = (l+r)/2;
        update(2*idx, l, mid, ql, qr, val);
        update(2*idx+1, mid+1, r, ql, qr, val);
        tree[idx] = tree[2*idx] + tree[2*idx+1];
    }

    // Range query
    int query(int idx, int l, int r, int ql, int qr) {
        propagate(idx, l, r);
        if (qr < l || r < ql) return 0; // no overlap
        if (ql <= l && r <= qr) return tree[idx]; // total overlap
        int mid = (l+r)/2;
        return query(2*idx, l, mid, ql, qr) + query(2*idx+1, mid+1, r, ql, qr);
    }
};

/* ======================================================
   🔹 DEMO
   ====================================================== */
int main() {
    vector<int> arr = {1,2,3,4,5};

    // Prefix Sum demo
    auto pre = buildPrefixSum(arr);
    cout << "Sum [1,3] = " << pre[4] - pre[1] << "\n"; // arr[1..3]

    // Suffix Sum demo
    auto suf = buildSuffixSum(arr);
    cout << "Suffix sum from 2 = " << suf[2] << "\n";

    // Difference Array demo
    vector<tuple<int,int,int>> updates = {{1,3,2}}; // add 2 in range [1,3]
    auto updated = applyRangeUpdates(arr, updates);
    cout << "After range update: ";
    for(int x: updated) cout << x << " "; cout << "\n";

    // Prefix XOR demo
    vector<int> arr2 = {1,2,3};
    auto preXor = buildPrefixXor(arr2);
    cout << "XOR [0,2] = " << (preXor[3] ^ preXor[0]) << "\n";

    // Lazy Segment Tree demo
    vector<int> arr3 = {1,2,3,4,5};
    LazySegTree st(arr3.size());
    st.build(arr3,1,0,arr3.size()-1);
    cout << "Initial range sum [1,3] = " << st.query(1,0,4,1,3) << "\n";
    st.update(1,0,4,1,3,2); // add +2 in [1,3]
    cout << "After update, sum [1,3] = " << st.query(1,0,4,1,3) << "\n";

    return 0;
}
