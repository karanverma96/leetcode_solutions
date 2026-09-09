/*
Intuition
The N-Queens problem is about placing n queens on an n x n chessboard such that no two queens attack each other. This means that for each queen, no other queen should be in the same row, column, or diagonal. Using backtracking, we can systematically explore each potential position for a queen, keeping track of restrictions imposed by each placement to ensure safe positioning for subsequent queens. If a solution meets all criteria, we store it; if not, we backtrack, removing the last queen and trying other options.

Approach
We create a recursive function backtrack() that places queens row by row.
For each row, we try to place a queen in every column that is not under attack.
To keep track of threats, we use three sets:
    1. cols to track which columns have queens.
    2. d1 for major diagonals (row - col).
    3. d2 for minor diagonals (row + col).

Before placing a queen, we check if the target column, major diagonal, and minor diagonal are free. If so, we place the queen and update cols, d1, and d2.

After placing a queen, we recursively call backtrack() for the next row.
If we reach the last row (row == n), we add the current board configuration to our results.
On backtracking, we remove the last queen and clear its associated column and diagonal entries to allow for alternative placements in prior rows.
This process continues until all solutions are found.

Complexity
Time complexity:
The time complexity is approximately O(N!) because each row has N choices, but choices diminish as we go down rows due to constraints on columns and diagonals.

Space complexity:
The space complexity is O(N) for the sets (cols, d1, d2) and the recursive stack depth, since we need to keep track of queens' positions up to N rows deep.
*/

class Solution {
public:

    void backtrack(vector<vector<string>>& ans, vector<string>& cur_config, unordered_set<int>& cols, unordered_set<int>& d1, unordered_set<int>& d2, int n, int row) {
        if (row == n) {
            ans.push_back(cur_config);
            return;
        }

        for (int col = 0; col < n; col++) {
            if (cols.find(col) == cols.end() && d1.find(row - col) == d1.end() && d2.find(row + col) == d2.end()) {
                cur_config[row][col] = 'Q';
                cols.insert(col);
                d1.insert(row - col);
                d2.insert(row + col);

                backtrack(ans, cur_config, cols, d1, d2, n, row + 1);

                cur_config[row][col] = '.';
                cols.erase(col);
                d1.erase(row - col);
                d2.erase(row + col);
            }
        }
    }

    vector<vector<string>> solveNQueens(int n) {
        vector<vector<string>> ans;
        vector<string> cur_config(n, string(n, '.'));
        unordered_set<int> cols;    // Columns with queens
        unordered_set<int> d1;      // Major diagonals (row - col)
        unordered_set<int> d2;      // Minor diagonals (row + col)

        backtrack(ans, cur_config, cols, d1, d2, n, 0);
        return ans;
    }

};
