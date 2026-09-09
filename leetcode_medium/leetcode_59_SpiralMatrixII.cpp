/*Intuition
Both approaches below are the same core idea — simulate the spiral by walking the matrix directly — expressed two different ways. If you've done grid BFS before, you might reach for direction vectors ({dr, dc} pairs) out of habit. That works here too, but there's a subtlety worth knowing about, especially if an interviewer pushes on it as a follow-up. I'll cover both, plus that follow-up, below.

Approach1: Four Boundary Pointers
Think of the matrix as a set of shrinking rings. Maintain top, bottom, left, right as the current unfilled boundary. Fill one edge at a time (left→right along top, top→bottom along right, right→left along bottom, bottom→top along left), then shrink the corresponding boundary inward. Repeat until all n*n cells are filled.

The only subtlety: on the last ring, if n is odd, it collapses to a single row or column. Without an extra check, the third and fourth loops of that final ring would double back and overwrite cells already filled by the first and second loops. Guard against this with currElement <= n*n in those two loops.
*/
//Code
class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        int top = 0, down = n - 1;
        int left = 0, right = n - 1;
        int currElement = 1;

        while (currElement <= n * n) {
            // move left to right, row = top fixed
            for (int c = left; c <= right; c++)
                matrix[top][c] = currElement++;
            top++;

            // move top to down, col = right fixed
            for (int r = top; r <= down; r++)
                matrix[r][right] = currElement++;
            right--;

            // move right to left, row = down fixed
            for (int c = right; c >= left && currElement <= n * n; c--)
                matrix[down][c] = currElement++;
            down--;

            // move down to top, col = left fixed
            for (int r = down; r >= top && currElement <= n * n; r--)
                matrix[r][left] = currElement++;
            left++;
        }

        return matrix;
    }
};

/*
Complexity:
Time O(n²) — every cell filled exactly once. Space O(1) auxiliary (just four pointers + a counter); O(n²) if you count the output matrix itself.
*/


/*
Approach 2: Direction Vectors (single loop)

Instead of four loops, walk one cell at a time with a "current heading," turning when you'd cross a boundary — closer to how you'd write a BFS direction-vector loop, but with one active direction instead of checking all four neighbors per cell.

A word of caution first: a common version of this checks matrix[nextRow][nextCol] != 0 to decide "has this cell already been filled, so I should turn?" That works only because 0 happens to mean "empty" in this problem. If the constraints changed — e.g., fill values from INT_MIN to INT_MIN + n², where any value including 0 could be legitimate — that sentinel check silently breaks. This is a classic bug category: using a special data value to mean "unset" only works when that value can never be genuinely valid data.

The fix that keeps O(1) auxiliary space: turn based on boundaries, never based on cell contents.
*/

//Code

class Solution {
public:
    vector<vector<int>> generateMatrix(int n) {
        vector<vector<int>> matrix(n, vector<int>(n, 0));
        vector<pair<int,int>> directions = {{0,1}, {1,0}, {0,-1}, {-1,0}};

        int top = 0, bottom = n - 1, left = 0, right = n - 1;
        int row = 0, col = 0, dirIdx = 0;

        for (int val = 1; val <= n * n; val++) {
            matrix[row][col] = val;

            int nextRow = row + directions[dirIdx].first;
            int nextCol = col + directions[dirIdx].second;

            bool hitBoundary = nextRow < top || nextRow > bottom || nextCol < left || nextCol > right;

            if (hitBoundary) {
                if (dirIdx == 0) top++;
                else if (dirIdx == 1) right--;
                else if (dirIdx == 2) bottom--;
                else left++;

                dirIdx = (dirIdx + 1) % 4;
                nextRow = row + directions[dirIdx].first;
                nextCol = col + directions[dirIdx].second;
            }

            row = nextRow;
            col = nextCol;
        }

        return matrix;
    }
};

/*
Complexity:
Time O(n²), Space O(1) auxiliary — same as Approach 1. The turn condition here is purely positional (compared against top/bottom/left/right), so it stays correct no matter what values you're filling with.

Which one should you use?

Both are O(n²) time / O(1) auxiliary space — there's no efficiency difference. The real tradeoff is readability vs. compactness:


Approach 1 is easier to explain out loud and verify by hand ("I peel off the top row, then right column, then bottom row, then left column, shrinking inward"). Good default choice.
Approach 2 has less code duplication (1 loop instead of 4), and generalizes more safely if the "fill value" assumption ever changes — as long as you turn based on boundaries, not on inspecting the data itself.


If an interviewer asks "can you avoid the 4 separate loops?", Approach 2 is the answer — but be ready to explain why you're checking boundaries instead of cell values, since that's usually the real point of the follow-up.
*/