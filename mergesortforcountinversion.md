Index:  0   1   2   3   4

Value: [5,  3,  2,  1,  4]
| Merge Call   | Comparing         | Action          | Inversions Added | Inversion Pairs     | Temp Array   |
| ------------ | ----------------- | --------------- | ---------------- | ------------------- | ------------ |
| merge(0,0,1) | 5 vs 3            | 5 > 3 → push 3  | +1               | (5,3)               | \[3]         |
|              | Left remains: 5   | push 5          | 0                |                     | \[3,5]       |
| merge(0,1,2) | 3 vs 2            | 3 > 2 → push 2  | +2               | (3,2), (5,2)        | \[2]         |
|              | Left remains: 3,5 | push both       | 0                |                     | \[2,3,5]     |
| merge(3,3,4) | 1 vs 4            | 1 <= 4 → push 1 | 0                | None                | \[1]         |
|              | Right remains: 4  | push 4          | 0                |                     | \[1,4]       |
| merge(0,2,4) | 2 vs 1            | 2 > 1 → push 1  | +3               | (2,1), (3,1), (5,1) | \[1]         |
|              | 2 vs 4            | 2 <= 4 → push 2 | 0                |                     | \[1,2]       |
|              | 3 vs 4            | 3 <= 4 → push 3 | 0                |                     | \[1,2,3]     |
|              | 5 vs 4            | 5 > 4 → push 4  | +1               | (5,4)               | \[1,2,3,4]   |
|              | Left remains: 5   | push 5          | 0                |                     | \[1,2,3,4,5] |
Final Result

    Sorted Array: [1, 2, 3, 4, 5]

    Total Inversions: 7

    All Inversion Pairs:

(5,3), (3,2), (5,2), (2,1), (3,1), (5,1), (5,4)
## ⏳ Time Complexity
- **Merge Sort** complexity: `O(n log n)`  
- Space Complexity: `O(n)`
## full step-by-step dry run — array = [5, 3, 2, 1, 4]

Notation & variables used

    arr is the array (modified in place by merges).

    merge(arr, low, mid, high) merges arr[low..mid] and arr[mid+1..high].

    left = pointer starting at low, right = pointer starting at mid+1.

    When arr[left] > arr[right], we add cnt += (mid - left + 1) because every element from left..mid is > arr[right].

    I show absolute indices (0-based) and values.

Recursion tree (top-level calls & segments)

    mergeSort(0,4)

        splits into mergeSort(0,2) and mergeSort(3,4)

    mergeSort(0,2)

        splits into mergeSort(0,1) and mergeSort(2,2)

    mergeSort(0,1)

        splits into mergeSort(0,0) and mergeSort(1,1)

        then merge(0,0,1) merges [5] and [3]

    merge(0,1,2) merges the result of step 3 with [2]

    mergeSort(3,4)

        merges [1] and [4] via merge(3,3,4)

    Final merge(0,2,4) merges left arr[0..2] and right arr[3..4].

Detailed merges (every comparison, pointer move, temp, and cnt)
Initial array (before any calls)

Index : 0 1 2 3 4
Values: [5, 3, 2, 1, 4]
1) merge(0,0,1) — merging [5] (index 0) and [3] (index 1)

    low=0, mid=0, high=1

    left = 0 (val=5), right = 1 (val=3), temp = [], cnt = 0

Step-by-step:

    Compare arr[left]=5 vs arr[right]=3. Since 5 > 3:

        push 3 → temp = [3]

        cnt += (mid - left + 1) = (0 - 0 + 1) = 1

        Added inversion: (5,3)

        right -> 2 (now right > high)

    Right exhausted → copy remaining left elements:

        push 5 → temp = [3,5]

    Copy back to arr[0..1] → arr becomes: [3,5,2,1,4]

Return from merge: cnt = 1
Local inversion pairs found: (5,3)
2) merge(0,1,2) — merging [3,5] (indices 0..1) and [2] (index 2)

Current arr segment before merge: indices 0..2 = [3,5,2]

    low=0, mid=1, high=2

    left=0 (3), right=2 (2), temp=[], cnt=0

Step-by-step:

    Compare 3 vs 2. 3 > 2:

        push 2 → temp=[2]

        cnt += (mid - left + 1) = (1 - 0 + 1) = 2

        Adds inversions: (3,2) and (5,2) (both left elements 3 and 5 are > 2)

        right -> 3 (right > high)

    Right exhausted → copy remaining left elements:

        push 3 → temp=[2,3]

        push 5 → temp=[2,3,5]

    Copy back to arr[0..2] → arr becomes: [2,3,5,1,4]

Return from merge: cnt = 2
Local inversion pairs found in this merge: (3,2), (5,2)

Left-subtree totals so far: from merge(0,0,1) = 1, plus this merge = 2 → left-subtree sum = 3
3) Right subtree merge(3,3,4) — merging [1] (idx 3) and [4] (idx 4)

    low=3, mid=3, high=4

    left=3 (1), right=4 (4), temp=[], cnt=0

Step-by-step:

    Compare 1 vs 4. 1 <= 4:

        push 1 → temp=[1]

        left -> 4 (left > mid)

    Copy remaining right:

        push 4 → temp=[1,4]

    Copy back to arr[3..4] → arr remains [2,3,5,1,4] (segment sorted)

Return from merge: cnt = 0
No inversion pairs found in this merge.
4) Final merge(0,2,4) — merging [2,3,5] (0..2) and [1,4] (3..4)

Current arr before final merge: [2,3,5,1,4]

    low=0, mid=2, high=4

    left=0 (2), right=3 (1), temp=[], cnt=0

Step-by-step:

    Compare 2 vs 1. 2 > 1:

        push 1 → temp=[1]

        cnt += (mid - left + 1) = (2 - 0 + 1) = 3

        Adds inversions: (2,1), (3,1), (5,1) — because all left elements 2,3,5 are > 1.

        right -> 4

    Compare 2 vs 4. 2 <= 4:

        push 2 → temp=[1,2]

        left -> 1

    Compare 3 vs 4. 3 <= 4:

        push 3 → temp=[1,2,3]

        left -> 2

    Compare 5 vs 4. 5 > 4:

        push 4 → temp=[1,2,3,4]

        cnt += (mid - left + 1) = (2 - 2 + 1) = 1

        Adds inversion: (5,4)

        right -> 5 (right > high)

    Right exhausted → copy remaining left:

        push 5 → temp=[1,2,3,4,5]

    Copy back to arr[0..4] → arr becomes: [1,2,3,4,5]

Return from final merge: cnt = 4 (3 from 1 + 1 from 4)
Summing the counts

    merge(0,0,1) = 1 → (5,3)

    merge(0,1,2) = 2 → (3,2), (5,2)

    merge(3,3,4) = 0

    merge(0,2,4) = 4 → (2,1), (3,1), (5,1), (5,4)

Total inversions = 1 + 2 + 0 + 4 = 7
All inversion pairs (explicitly listed)

    (5,3)

    (3,2)

    (5,2)

    (2,1)

    (3,1)

    (5,1)

    (5,4)

(7 pairs total)
Final state & output

    Final sorted array (after algorithm): [1, 2, 3, 4, 5]

    Final inversion count returned by numberOfInversions() = 7

Why cnt += (mid - left + 1) is correct (brief)

When arr[left] > arr[right], because both halves are individually sorted, every element from index left through mid (inclusive) is ≥ arr[left] and therefore > arr[right]. So we can add all those at once instead of counting one-by-one.
