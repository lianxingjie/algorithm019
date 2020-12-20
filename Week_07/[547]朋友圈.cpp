class Solution {
public:
    int findCircleNum(vector<vector<int>>& M) {
        int n = M.size();
        int ret = 0;

        vector<bool> visited(n, false);
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                ++ret;
                visit(M, i, visited);
            }
        }
        return ret;
    }

    void visit(vector<vector<int>>& M, int row, vector<bool> &visited) {
        visited[row] = true;
        for (int i = 0; i < M.size(); i++) {
            if (!visited[i] && M[row][i] == 1) {
                visit(M, i, visited);
            }
        }
    }
};