# Problem Statement:
## Given an array nums[], return a new array res[] such that:


### 🔁 1. Brute Force
💡 Logic:
For every index i, loop through the array and multiply every other element except nums[i].

vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n);

    for (int i = 0; i < n; i++) {
        int prod = 1;
        for (int j = 0; j < n; j++) {
            if (i != j) prod *= nums[j];
        }
        res[i] = prod;
    }
    return res;
}
 ### ⏱ Time Complexity:
O(n^2) — Two nested loops for each element.

### 📦 Space Complexity:
Extra Space: O(1)

### Output Space: O(n)

## ➗ 2. Using Division
💡 Logic:
Multiply all non-zero elements.

Count the number of zeros.

If more than one zero → all products will be 0.

If one zero → only the zero index will have product of non-zero elements.

Else → product of all / nums[i].


vector<int> productExceptSelf(vector<int>& nums) {
    int prod = 1, zeroCount = 0;
    for (int num : nums) {
        if (num != 0) prod *= num;
        else zeroCount++;
    }

    vector<int> res(nums.size());
    for (int i = 0; i < nums.size(); i++) {
        if (zeroCount > 1) res[i] = 0;
        else if (zeroCount == 1) res[i] = (nums[i] == 0 ? prod : 0);
        else res[i] = prod / nums[i];
    }
    return res;
}
⏱ Time Complexity:
O(n)

📦 Space Complexity:
Extra Space: O(1)

Output Space: O(n)

⚠️ Problem:
Fails for zero values if division isn't allowed.

🔄 3. Prefix & Suffix Arrays
💡 Logic:
Use two extra arrays:

pref[i] = product of all elements before index i

suff[i] = product of all elements after index i

Result: res[i] = pref[i] * suff[i]


vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n), pref(n), suff(n);

    pref[0] = 1;
    for (int i = 1; i < n; i++)
        pref[i] = nums[i - 1] * pref[i - 1];

    suff[n - 1] = 1;
    for (int i = n - 2; i >= 0; i--)
        suff[i] = nums[i + 1] * suff[i + 1];

    for (int i = 0; i < n; i++)
        res[i] = pref[i] * suff[i];

    return res;
}
⏱ Time Complexity:
O(n)

📦 Space Complexity:
Extra Space: O(n) (pref + suff)

Output Space: O(n)

## ⚡ 4. Prefix & Suffix (Optimized – Most Efficient)
💡 Logic:
Avoid using pref[] and suff[] arrays.

First pass → fill res[i] with prefix product up to i.

Second pass (reverse) → multiply res[i] with postfix product from the right.

vector<int> productExceptSelf(vector<int>& nums) {
    int n = nums.size();
    vector<int> res(n, 1);

    for (int i = 1; i < n; i++)
        res[i] = res[i - 1] * nums[i - 1];

    int postfix = 1;
    for (int i = n - 1; i >= 0; i--) {
        res[i] *= postfix;
        postfix *= nums[i];
    }

    return res;
}
⏱ Time Complexity:
O(n)

📦 Space Complexity:
Extra Space: O(1)

Output Space: O(n)

🔍 Concept Recap:
For value at i, result = product of all values to left × product of all values to right.

Example: a, b, c, x, d, e, f

res[x] = a * b * c * d * e * f = prefix[x] * suffix[x]

Division fails when nums[i] = 0 → handle with care or avoid entirely.


🧪 Example Input:

nums = [1, 2, 3, 4]
We want:

res[i] = product of all nums[j] where j != i
🔄 Step-by-Step Execution of Optimal Code
✅ Initialization:<br/>

res = [1, 1, 1, 1]  // initially all set to 1
🔁 Step 1: Forward Pass (Prefix product)

for (int i = 1; i < n; i++)
    res[i] = res[i - 1] * nums[i - 1];
i	res[i]	nums[i - 1]	res (after update)
1	res[1] = 1 * 1 = 1	nums[0]=1	[1, 1, 1, 1]
2	res[2] = 1 * 2 = 2	nums[1]=2	[1, 1, 2, 1]
3	res[3] = 2 * 3 = 6	nums[2]=3	[1, 1, 2, 6]
<br/>
📦 Prefix so far:


res = [1, 1, 2, 6]
Each res[i] now holds the product of all elements to the left of i.
<br/>
🔁 Step 2: Backward Pass (Postfix product)

postfix = 1;
for (int i = n - 1; i >= 0; i--) { 
      res[i] *= postfix;
      postfix *= nums[i];
}

| i | res\[i] before | postfix | res\[i] after | nums\[i] | postfix after         |
| - | -------------- | ------- | ------------- | -------- | --------------------- |
| 3 | 6              | 1       | 6 \* 1 = 6    | 4        | 1 \* 4 = 4            |
| 2 | 2              | 4       | 2 \* 4 = 8    | 3        | 4 \* 3 = 12           |
| 1 | 1              | 12      | 1 \* 12 = 12  | 2        | 12 \* 2 = 24          |
| 0 | 1              | 24      | 1 \* 24 = 24  | 1        | 24 \* 1 = 24 (unused) |

📦 Final Result:<br/>
res = [24, 12, 8, 6]
🧮 Final Output
cpp
Copy
Edit
return [24, 12, 8, 6]
✅ This means:

At index 0: 2×3×4 = 24 <br/>

At index 1: 1×3×4 = 12 <br/>

At index 2: 1×2×4 = 8 <br/>

At index 3: 1×2×3 = 6 <br/>

| Index | nums\[i] | Product of All Except nums\[i] | Final res\[i] |
| ----- | -------- | ------------------------------ | ------------- |
| 0     | 1        | 2 × 3 × 4 = 24                 | 24            |
| 1     | 2        | 1 × 3 × 4 = 12                 | 12            |
| 2     | 3        | 1 × 2 × 4 = 8                  | 8             |
| 3     | 4        | 1 × 2 × 3 = 6                  | 6             |



| Approach     | Time Complexity | Space Complexity |
|--------------|-----------------|------------------|
| Brute Force  | O(n²)           | O(1) extra       |
| Division     | O(n)            | O(1) extra       |
| Prefix Array | O(n)            | O(n)             |
| Optimal      | O(n)            | O(1) extra       |

