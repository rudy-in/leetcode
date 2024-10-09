# The problem
You are given a tree with n nodes numbered from 0 to n - 1 in the form of a parent array parent where parent[i] is the parent of ith node. The root of the tree is node 0. Find the kth ancestor of a given node.

The kth ancestor of a tree node is the kth node in the path from that node to the root node.

Implement the TreeAncestor class:

    TreeAncestor(int n, int[] parent) Initializes the object with the number of nodes in the tree and the parent array.
    int getKthAncestor(int node, int k) return the kth ancestor of the given node node. If there is no such ancestor, return -1.


Input
["TreeAncestor", "getKthAncestor", "getKthAncestor", "getKthAncestor"]
[[7, [-1, 0, 0, 1, 1, 2, 2]], [3, 1], [5, 2], [6, 3]]
Output
[null, 1, 0, -1]

Explanation
TreeAncestor treeAncestor = new TreeAncestor(7, [-1, 0, 0, 1, 1, 2, 2]);
treeAncestor.getKthAncestor(3, 1); // returns 1 which is the parent of 3
treeAncestor.getKthAncestor(5, 2); // returns 0 which is the grandparent of 5
treeAncestor.getKthAncestor(6, 3); // returns -1 because there is no such ancestor



Constraints:

    1 <= k <= n <= 5 * 104
    parent.length == n
    parent[0] == -1
    0 <= parent[i] < n for all 0 < i < n
    0 <= node < n
    There will be at most 5 * 104 queries.


# My Solution

# Intuition
To find the k-th ancestor of a node in a tree, we need an efficient way to traverse the tree upwards without having to repeatedly access parent nodes one by one. The goal is to preprocess the tree structure so that we can quickly determine any ancestor by leveraging the properties of binary lifting.

# Approach
1. Use a 2D vector `up` where `up[i][j]` stores the \(2^j\)-th ancestor of node \(i\).
2. Initialize `up` such that `up[i][0]` is the parent of node \(i\).
3. Fill in the `up` table using the relation:
   \[
   \text{up}[i][j] = \text{up}[\text{up}[i][j-1]][j-1]
   \]
4. To find the k-th ancestor of a node, decompose \( k \) into its binary representation and jump to ancestors in logarithmic steps.

# Complexity
- Time complexity: \( O(n \log n) \) for preprocessing and \( O(\log n) \) for each query.
- Space complexity: \( O(n \log n) \) for the `up` table.

# Code
```cpp
#include <vector>
#include <cmath>

class TreeAncestor {
public:
    std::vector<std::vector<int>> up;
    int maxLog;

    TreeAncestor(int n, std::vector<int>& parent) {
        maxLog = std::log2(n) + 1;
        up.resize(n, std::vector<int>(maxLog, -1));

        for (int i = 0; i < n; ++i) {
            up[i][0] = parent[i];
        }

        for (int j = 1; j < maxLog; ++j) {
            for (int i = 0; i < n; ++i) {
                if (up[i][j - 1] != -1) {
                    up[i][j] = up[up[i][j - 1]][j - 1];
                }
            }
        }
    }

    int getKthAncestor(int node, int k) {
        for (int j = 0; j < maxLog; ++j) {
            if (k & (1 << j)) {
                node = up[node][j];
                if (node == -1) return -1;
            }
        }
        return node;
    }
};
```
