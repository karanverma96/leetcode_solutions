/*
Intuition
Since the array is sorted, my first instinct was binary search. The real question was: once I find the number closest to x, how do I get the remaining k-1 closest numbers?

I made an observation by picturing the sorted array on a number line:

....a, b, c, c_n, d, e, f....

The numbers closest to c_n (the closest number to x) are potentially the other closest numbers to x itself. This gives the intuition that the k closest numbers will always form a contiguous subarray that includes c_n.

I convinced myself this is always true by breaking it into cases:

- Only one closest number: duplicates of it, if any, will be adjacent since the array is sorted, still contiguous.
- Two different closest numbers (a, b): picture them as a ... x ... b on the number line. If any other element existed between a and b, it would be closer to x than one of them, contradiction. So a and b must be adjacent.
- Three or more different closest numbers: not possible, by the same "nothing can sit between the closest pair" argument.

So no matter how many elements tie for closest, they always form one contiguous block which is where the answer lives.

Approach
Step 1: Binary search for the index of the element closest to x

Search the full array. At each mid, track the best candidate using abs(arr[mid] - x):
- If the current diff is smaller than the best seen so far, update the candidate.
- If it ties the best diff, prefer the smaller (leftmost) index.
- If arr[mid] > x, moving right only increases distance, so eliminate the right half.
- If arr[mid] < x, moving left only increases distance, so eliminate the left half.
- If arr[mid] == x, that's the exact closest match, stop immediately.

Step 2: Two-pointer expansion around the closest index

Since the closest numbers to c_n are potentially the closest numbers to x, I don't need to search the whole array again, I just expand outward from c_n with two pointers (left_p = c_n_index - 1, right_p = c_n_index + 1), always moving whichever pointer points to the smaller abs(ele - x). On a tie, I move the left pointer (per the problem's tie-breaking rule).

I keep expanding until either k elements are collected, or one of the pointers runs out of bounds.

Step 3: Handle a pointer running out early

If the loop stopped because left_p or right_p went out of bounds, not because I had k elements yet, only left_p matters from here, since the answer must be contiguous. I just keep sliding left_p left until k elements are accounted for.

Step 4: Build the answer

At this point left_p sits one step past the actual left boundary of the window (each "choose" step moved it one further). So I increment it once, then copy k elements starting from arr[left_p] into the answer. Since it's a contiguous slice of a sorted array, the result comes out sorted with no extra work.

Complexity
Time complexity: O(log n + k)
Space complexity: O(1) (excluding the output array)

Detailed Thought Process

1. The array is given sorted, so binary search comes to mind.

2. Think about the most closest number:

Case 1: Only one most closest number.
Can there be duplicates of this? Yes, but since the array is sorted, they would be adjacent/contiguous.

Case 2: Two different most closest numbers.
Is this possible? Say a, b are the most closest numbers, so on the number line it would look like:
a ... x ... b
Can there be an element between a and b other than x? No, if there were, a and b would no longer be the most closest numbers (contradiction). So in the sorted array they will be adjacent. Now can there be duplicates? Yes, but by the same logic as Case 1, since the array is sorted, it would still form a contiguous subarray.

Case 3: Three different most closest numbers.
Is this possible? No, you can place a, b, c, x on the number line and see it's not possible, or you can take the hint from Case 2: there cannot be an element between a and b, where a, b are the closest numbers from Case 2.

3. Let's say we've found the index of one of the most closest numbers, now what about the remaining k-1 closest numbers?

Let's make an observation. Since the array is sorted, example on a number line:

..... a, b, c, closest number, d, e, f .......

i.e.  c >= b >= a >= (closest number, x) <= d <= e <= f

Now notice, the numbers closest to the closest number (c_n) are potentially the other closest numbers to x. So if we consider the closest numbers to c_n, we are potentially seeking the closest numbers to x.

Let's give an alias to the closest number, calling it c_n. If we move in the left direction of c_n, the first closest number to c_n in that direction will be a, then b, then c, according to the number line above. Similarly for the right direction of c_n: first d, then e, then f.

4. From the observations in point 3, we can say for certain that the k closest numbers to x will be a contiguous subarray containing the closest number, in the sorted array.

4.5. Finding c_n_index using binary search, what will be the range?

left_p = 0 and right_p = arr.size() - 1.

Calculate mid, mid can be a potential answer, so save its index and value (abs(mid_ele - x)). When we move to another mid, we can compare its abs value to the previous abs:
- If abs < previous_abs, change the potential answer's index and value.
- If abs == previous_abs, then if current_index < previous_index, change the potential index and value (abs(ele - x)).

Now, at mid, how do we know which direction to move?

- Check mid_ele > x, on the number line: x ... mid_ele. If we move in the right direction, numbers will increase, so closeness will decrease, so eliminate the right part, i.e., right_p = mid - 1.
- Check mid_ele < x, on the number line: mid_ele ... x. If we move in the left direction, numbers will decrease, and closeness will also decrease, so eliminate the left direction, i.e., left_p = mid + 1.

5. Now we have c_n_index, recall the observations from points 3 and 4. Then do the following: we don't know how far left we need to go from c_n, and similarly how far right. So what we'll do is take 2 pointers, one pointing to c_n_index - 1 and one pointing to c_n_index + 1.

6. Now we'll compare the elements at the 2 pointers using abs(ele - x), whichever element has the smaller abs value, we'll logically take that element by moving the corresponding pointer further. If the abs is the same, we'll take the element from the left pointer, according to the definition of "closest number" given in the problem statement. It will be either left_p-- or right_p++.

7. The terminating conditions for the movement of the above pointers are:
- left_p >= 0 && right_p < arr.size()
- and also if we've already chosen k elements.

8. If it terminated and we haven't chosen k elements yet, it could have terminated because of either left_p or right_p. But now we only need the position of left_p, because the k elements are contiguous, if we find left_p, we can consider k contiguous elements starting from the leftmost point. So you can just write:

    while (left_p >= 0 && elements_chosen < k) {
        left_p--;
        elements_chosen++;
    }

9. Now, when we chose an element, we actually moved the pointer ahead, so left_p will be one less than where the leftmost index of our k-closest-elements subarray should actually start. So just do left_p++.

10. Now just copy k elements into the answer, starting from arr[left_p], and since the array is sorted, our answer will also be sorted. Now you can return the answer.

Complexity Reasoning

Time Complexity -> O(log n + k), where n = array.size(). The optimal solution's Time Complexity is O(log(n-k) + k). Space Complexity is O(1) in both cases.

Our Time Complexity is almost equivalent to the optimal one, for example:
- If k = n = 10^8, our TC -> O(8*log(10) + 10^8), and the optimal solution's TC -> O(10^8), here k dominates, so the difference is negligible.
- When k = 1 and n = 10^8, our TC = O(8*log(10)), there's a slight O(1) difference from the optimal, but not much.
*/

class Solution {
public:
    vector<int> findClosestElements(vector<int>& arr, int k, int x) {
        int n = arr.size();

        int closest_index = 0;
        int min_diff = INT_MAX;
        int left = 0, right = n - 1;

        // Binary search to find index of the closest element to x
        while (left <= right) {
            int mid = left + (right - left) / 2;
            int mid_val = arr[mid];
            int diff = abs(mid_val - x);

            if (mid_val < x) {
                left = mid + 1;
            } else if (mid_val > x) {
                right = mid - 1;
            } else {
                // Exact match found — this is the closest possible
                closest_index = mid;
                break;
            }

            // Update best candidate: smaller diff wins,
            // and on a tie, prefer the smaller (leftmost) index
            if (diff < min_diff || (diff == min_diff && mid < closest_index)) {
                closest_index = mid;
                min_diff = diff;
            }
        }

        // Two-pointer expansion around closest_index
        int left_p = closest_index - 1;
        int right_p = closest_index + 1;
        int count = 1; // closest_index itself is already 1 chosen element

        while (left_p >= 0 && right_p < n && count < k) {
            int diff_left = abs(arr[left_p] - x);
            int diff_right = abs(arr[right_p] - x);

            // Prefer left on tie, per problem's tie-breaking rule
            if (diff_left <= diff_right) {
                left_p--;
            } else {
                right_p++;
            }
            count++;
        }

        // just need to extend left_p now if count < k
        // (right_p doesn't need a symmetric extension — once left_p
        // is known, we just take k consecutive elements from there)
        while (left_p >= 0 && count < k) {
            left_p--;
            count++;
        }

        left_p++; // move back to the actual left boundary

        // Build the answer from the contiguous window
        vector<int> ans(k);
        for (int i = 0; i < k; i++) {
            ans[i] = arr[left_p++];
        }

        return ans;
    }
};
