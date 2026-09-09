/*
Intuition
Sorting for Cumulative Counting:

    1. By sorting the start_times and end_times of flowers, we can cumulatively count how many flowers have started and ended blooming up to each person’s arrival time.

        2   . Sorting people by their arrival times also allows us to check each arrival time in increasing order, which means we can "sweep" through the bloom times of flowers in a single pass.

Two-Pointer Technique for Counting:

    1. Since both start_times and end_times are sorted, the two-pointer approach lets us count the number of flowers that started and ended blooming up to any given arrival time without needing binary searches.
    2. Instead of resetting or redoing the count for each arrival time, we simply move each pointer forward whenever necessary. This lets us accumulate the count without going back or re-evaluating previous times.

Approach
1. Processing in Sorted Order:
    First, sort start_times and end_times. Then, sort people by arrival times. Sorting lets us process each arrival time progressively, so we only need to move each pointer in one direction (from left to right).

2. Two Pointers for Start and End Counts:
    Initialize two pointers: start_ptr and end_ptr, both starting at the beginning of the start_times and end_times arrays.
    For each arrival time (processed in sorted order):
        Move start_ptr forward to count all flowers that have started blooming up to the current arrival time.
        Move end_ptr forward to count all flowers that have stopped blooming before the current arrival time.

3. Calculate Flowers in Bloom:
    For each arrival time, the difference start_ptr - end_ptr gives the count of flowers currently blooming.
    start_ptr tells us how many flowers have started blooming by this time.
    end_ptr tells us how many flowers have finished blooming before this time.
    Subtracting these counts gives the exact number of flowers that are still in bloom.

Since people was initially paired with their indices, after processing in sorted order, we place the results back in the original order.

Avoids Repeated Searches: Instead of performing a binary search for each arrival time, we just increment pointers, which is much faster.

Complexity
Time complexity:
O(nlogn) + O(n)

Space complexity:
*/


class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        // Separate start and end times
        vector<int> start_times, end_times;
        for (const auto& flower : flowers) {
            start_times.push_back(flower[0]);
            end_times.push_back(flower[1]);
        }

        // Sort start and end times
        sort(start_times.begin(), start_times.end());
        sort(end_times.begin(), end_times.end());

        // Prepare the answer vector
        vector<int> result(people.size());

        // For each person's arrival time, calculate the number of flowers in bloom
        for (int i = 0; i < people.size(); ++i) {
            int time = people[i];

            // Count flowers that have started blooming by `time`
            int blooms_started = upper_bound(start_times.begin(), start_times.end(), time) - start_times.begin();

            // Count flowers that have stopped blooming by `time`
            int blooms_ended = lower_bound(end_times.begin(), end_times.end(), time) - end_times.begin();

            // The number of flowers in bloom is the difference
            result[i] = blooms_started - blooms_ended;
        }

        return result;

    }
};
