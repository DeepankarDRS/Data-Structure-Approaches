📚 Table of Contents

    What is a Prefix?

    Why Prefix Tricks Work

    Core Variants

        1D Prefix Sum

        Prefix XOR

        Prefix Mod (Sum % k)

        2D Prefix Sum (Matrix)

        Difference Array (Range Updates)

    Hashing + Prefix: Counting Subarrays

        Count Subarrays with Sum = K

        Count Subarrays with XOR = K

        Count Subarrays with Sum Divisible by K

        Longest Subarray with Sum = 0

    Templates (C++ & Python)

    Worked Mini-Example

    Complexity & Pitfalls

    Practice Checklist

    License

# What is a Prefix?

For an array a[0..n-1]:

    Prefix Sum: pref[i] = a[0] + a[1] + ... + a[i]

    Prefix XOR: px[i] = a[0] ^ a[1] ^ ... ^ a[i]

    Prefix Mod: Store pref[i] % k to reason about divisibility.

These let you answer subarray queries in O(1) after O(n) preprocessing:

    Sum of a[l..r] = pref[r] - (l ? pref[l-1] : 0)

    XOR of a[l..r] = px[r] ^ (l ? px[l-1] : 0)

# Why Prefix Tricks Work

For any associative operation ⊕ (like + or ^):

a[l..r] = pref[r] ⊕ inverse(pref[l-1])

    For +, inverse is subtraction.

    For ^, inverse is itself (x ^ x = 0), hence px[r] ^ px[l-1].

This algebraic structure + a hash map of seen prefixes ⇒ count or locate subarrays in O(n).
## Core Variants
### 1D Prefix Sum

    Build once, answer many range-sum queries.

    Handles negatives too.

### Prefix XOR

    Ideal for problems where sum logic fails (e.g., bitwise constraints).

    Works because XOR is associative and self-inverse.

### Prefix Mod (Sum % k)

    If (pref[r] - pref[l-1]) % k == 0 ⇒ pref[r] % k == pref[l-1] % k.

    Counting pairs with equal remainders gives number of subarrays divisible by k.

### 2D Prefix Sum (Matrix)

    P[i][j] = sum of rectangle (0,0) → (i,j).

    Rectangle sum (x1,y1)-(x2,y2) in O(1) using inclusion–exclusion.

### Difference Array (Range Updates)

    1D: To add val on [l, r]:

        diff[l] += val; diff[r+1] -= val;

        Reconstruct with prefix sum.

    2D: Add to rectangle via 4 updates in a 2D diff grid.

## Hashing + Prefix: Counting Subarrays
Count Subarrays with Sum = K

Idea: For current prefix sum S, we need a previous prefix S - K.
Maintain a frequency map of seen prefix sums.

Correctness:

Sum(l..i) = pref[i] - pref[l-1] = K  ⇔  pref[l-1] = pref[i] - K

### Count Subarrays with XOR = K

Idea: For current prefix xor X, we need previous prefix X ^ K.
Maintain a frequency map of seen prefix xors.

Correctness:

XOR(l..i) = px[i] ^ px[l-1] = K  ⇔  px[l-1] = px[i] ^ K

### Count Subarrays with Sum Divisible by K

Idea: Count pairs of indices with equal remainder pref[i] % k.
Use frequency of remainders; each pair contributes one subarray.
Longest Subarray with Sum = 0

Idea: First index where a given pref occurs vs. latest index; maximize gap.


✅ Count Subarrays with Sum = K (C++)

    #include <bits/stdc++.h>
    using namespace std;

    long long countSubarraysSumK(const vector<long long>& a, long long K) {
    unordered_map<long long, long long> freq;
    freq[0] = 1; // empty prefix
    long long pref = 0, ans = 0;
    for (auto x : a) {
        pref += x;
        if (freq.count(pref - K)) ans += freq[pref - K];
        freq[pref]++;
      }
      return ans;
  }

✅ Count Subarrays with XOR = K (C++)

      #include <bits/stdc++.h>
      using namespace std;
      
      long long countSubarraysXorK(const vector<int>& a, int K) {
          unordered_map<int, long long> freq;
          freq[0] = 1; // empty prefix xor
          int px = 0;
          long long ans = 0;
          for (int x : a) {
              px ^= x;
              int want = px ^ K;
              if (freq.count(want)) ans += freq[want];
              freq[px]++;
          }
          return ans;
      }

✅ Count Subarrays with Sum Divisible by K (C++)

    #include <bits/stdc++.h>
    using namespace std;
    
    long long countSubarraysDivByK(const vector<long long>& a, long long K) {
        vector<long long> freq(K, 0);
        long long pref = 0, ans = 0;
        freq[0] = 1; // remainder 0 at empty prefix
        for (auto x : a) {
            pref += x;
            long long r = ((pref % K) + K) % K; // safe for negatives
            ans += freq[r];
            freq[r]++;
        }
        return ans;
    }

✅ Longest Subarray with Sum = 0 (C++)

    #include <bits/stdc++.h>
    using namespace std;
    
    int longestZeroSumSubarray(const vector<long long>& a) {
        unordered_map<long long, int> first;
        long long pref = 0;
        int best = 0;
        first[0] = -1; // empty prefix at index -1
        for (int i = 0; i < (int)a.size(); ++i) {
            pref += a[i];
            if (first.count(pref)) {
                best = max(best, i - first[pref]);
            } else {
                first[pref] = i;
            }
        }
        return best;
    }

✅ 2D Prefix Sum (C++)

    #include <bits/stdc++.h>
    using namespace std;
    
    struct Prefix2D {
        int n, m;
        vector<vector<long long>> P;
        Prefix2D(const vector<vector<long long>>& A) {
            n = A.size(); m = n ? A[0].size() : 0;
            P.assign(n+1, vector<long long>(m+1, 0));
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= m; ++j)
                    P[i][j] = A[i-1][j-1] + P[i-1][j] + P[i][j-1] - P[i-1][j-1];
        }
        // sum on [r1..r2], [c1..c2], inclusive; 0-indexed
        long long query(int r1, int c1, int r2, int c2) {
            r1++; c1++; r2++; c2++;
            return P[r2][c2] - P[r1-1][c2] - P[r2][c1-1] + P[r1-1][c1-1];
        }
    };

✅ Difference Array (Range Add) & Restore (C++)

    #include <bits/stdc++.h>
    using namespace std;
    
    vector<long long> applyRangeAdds(int n, const vector<tuple<int,int,long long>>& ops) {
        vector<long long> diff(n+1, 0);
        for (auto [l, r, val] : ops) {
            diff[l] += val;
            if (r + 1 < (int)diff.size()) diff[r+1] -= val;
        }
        vector<long long> a(n);
        long long run = 0;
        for (int i = 0; i < n; ++i) {
            run += diff[i];
            a[i] = run;
        }
        return a;
    }

(Python equivalents)

    from collections import defaultdict
    from typing import List
    
    def count_subarrays_sum_k(a: List[int], K: int) -> int:
        freq = defaultdict(int)
        freq[0] = 1
        pref = ans = 0
        for x in a:
            pref += x
            ans += freq[pref - K]
            freq[pref] += 1
        return ans
    
    def count_subarrays_xor_k(a: List[int], K: int) -> int:
        freq = defaultdict(int)
        freq[0] = 1
        px = ans = 0
        for x in a:
            px ^= x
            ans += freq[px ^ K]
            freq[px] += 1
        return ans
    
    def count_subarrays_div_by_k(a: List[int], K: int) -> int:
        freq = [0]*K
        freq[0] = 1
        pref = ans = 0
        for x in a:
            pref += x
            r = (pref % K + K) % K
            ans += freq[r]
            freq[r] += 1
        return ans

Array: a = [4, 2, 2, 6, 4], K = 6
Count subarrays with XOR = K

    px evolves:

        i=0: px=4, want=4^6=2, freq[2]=0 → ans=0, freq[4]++

        i=1: px=6, want=6^6=0, freq[0]=1 → ans=1, freq[6]++

        i=2: px=4, want=4^6=2, freq[2]=0 → ans=1, freq[4]++ (now freq[4]=2)

        i=3: px=2, want=2^6=4, freq[4]=2 → ans=3, freq[2]++

        i=4: px=6, want=6^6=0, freq[0]=1 → ans=4, freq[6]++

Answer: 4 subarrays have XOR 6.
(They are: [4,2], [2,6], [2,2,6,4] appropriately indexed, etc.)
Complexity & Pitfalls
    Time & Space
    Technique	Preprocess	Query	Count/Longest
    1D Prefix Sum	O(n)	O(1)	O(n) with map
    Prefix XOR	O(n)	O(1)	O(n) with map
    Prefix Mod (Divisible by k)	O(n)	—	O(n)
    2D Prefix Sum	O(nm)	O(1)	—
    Difference Array (Range Add)	O(#ops+n)	—	—
    Common Gotchas

    Negatives & Mod: Always normalize ((x % k) + k) % k.

    Overflow in C++: Use long long for sums.

    Initialize Map: freq[0] = 1 is crucial (empty prefix).

    Sliding Window vs Prefix: Sliding window only works with non-negative arrays for sum problems. Use prefix + map if negatives exist.

    2D Boundaries: Build with an extra zero row/col; adjust indices carefully.

    XOR Specifics: There’s no “prefix mod XOR”; XOR math is different from sum. Use the px ^ K trick exactly.

Practice Checklist

Subarray sum equals K (with negatives) — prefix + hashmap

Subarray XOR equals K — prefix XOR + hashmap

Subarray sum divisible by K — remainder frequency counting

Longest zero-sum subarray — first-seen index map

2D range sum query — 2D prefix + inclusion–exclusion

Range increments — difference array (1D & 2D)

Mix & match: longest subarray with sum K (two-sum on prefixes)

Edge cases: all zeros / all same values / single element / empty


