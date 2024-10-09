# The problem

You are given two positive integers n and k. A factor of an integer n is defined as an integer i where n % i == 0.

Consider a list of all factors of n sorted in ascending order, return the kth factor in this list or return -1 if n has less than k factors.



Example 1:

Input: n = 12, k = 3
Output: 3
Explanation: Factors list is [1, 2, 3, 4, 6, 12], the 3rd factor is 3.

Example 2:

Input: n = 7, k = 2
Output: 7
Explanation: Factors list is [1, 7], the 2nd factor is 7.

Example 3:

Input: n = 4, k = 4
Output: -1
Explanation: Factors list is [1, 2, 4], there is only 3 factors. We should return -1.



Constraints:

    1 <= k <= n <= 1000



Follow up:

Could you solve this problem in less than O(n) complexity?


# My solution

# Intuition
To find the k-th factor of an integer \( n \), we first need to identify all the factors of \( n \). A factor is an integer \( i \) such that \( n \% i == 0 \). By iterating through possible divisors, we can collect these factors. Since factors can be paired (i.e., if \( i \) is a factor, then \( n/i \) is also a factor), we can efficiently collect them by iterating only up to \( \sqrt{n} \).

# Approach
1. Use a vector to store the factors of \( n \).
2. Loop through integers from 1 to \( \sqrt{n} \) to check for factors.
3. For each factor \( i \) found, add it to the list. If \( i \) is not the same as \( n/i \), add the paired factor as well.
4. After collecting the factors, sort the vector to ensure the factors are in ascending order.
5. Check if the vector has at least \( k \) factors. If so, return the k-th factor; otherwise, return -1.

# Complexity
- Time complexity: \( O(\sqrt{n} \log \sqrt{n}) \) for collecting factors and sorting them.

- Space complexity: \( O(n) \) in the worst case, where all numbers up to \( n \) could be factors.

# Code
```cpp
#include <vector>
#include <algorithm>

class Solution {
public:
    int kthFactor(int n, int k) {
        std::vector<int> factors;

        for (int i = 1; i * i <= n; ++i) {
            if (n % i == 0) {
                factors.push_back(i);
                if (i != n / i) {
                    factors.push_back(n / i);
                }
            }
        }

        std::sort(factors.begin(), factors.end());

        if (k <= factors.size()) {
            return factors[k - 1];
        }

        return -1;
    }
};
```
