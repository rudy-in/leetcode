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
