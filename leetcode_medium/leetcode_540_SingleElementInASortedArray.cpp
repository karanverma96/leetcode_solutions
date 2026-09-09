/*
Intuition
As array is sorted and we need to implement in log(n) time , it's obvious that we need to use binary search.Binary search typically works by dividing the search space in half at each step, so we need to carefully identify the halves and eliminate one of them based on the current element (nums[mid]). Also we need to check if nums[mid] is the single element

Approach
// Credit for some of the good explanation paragraph goes to takeuforward

How to check if arr[mid] i.e. the current element is the single element:

A crucial observation to note is that if an element appears twice in a sequence, either the preceding or the subsequent element will also be the same. But only for the single element, this condition will not be satisfied. So, to check this, the condition will be the following:

If arr[mid] != arr[mid-1] and arr[mid] != arr[mid+1]: If this condition is true for arr[mid], we can conclude arr[mid] is the single element.
The above condition will throw errors in the following 3 cases:

If the array size is 1.
If ‘mid’ points to 0 i.e. the first index.
If ‘mid’ points to n-1 i.e. the last index.

At the start of the algorithm, we address the above edge cases without requiring separate conditions during the check for arr[mid] inside the loop. And the search space will be from index 1 to n-2 as indices 0 and n-1 have already been checked.

Resolving edge cases:

If n == 1: This means the array size is 1. If the array contains only one element, we will return that element only.
If arr[0] != arr[1]: This means the very first element of the array is the single element. So, we will return arr[0].
If arr[n-1] != arr[n-2]: This means the last element of the array is the single element. So, we will return arr[n-1].

nums = [1,1,2,3,3,4,4,8,8]

Now observe the above example and go to the mid element which is 3 at index number 4 now see the right halve has even number of elements and the left halve when we elimnate the duplicate has odd number of elements. so it is obvious that halve with odd number of elements will have the single element , so we will elimnate right halve.

if((nums[mid] == nums[mid-1] && mid%2 != 0) || (nums[mid] != nums[mid-1] && mid%2 == 0))

The above condition checks if the left half is even , so accordingly we can elimnate that halve else we will elimnate right halve.

Complexity
Time complexity:
O(log(n))

Space complexity:
O(1)
*/


class Solution {
public:
    int singleNonDuplicate(vector<int>& nums) {
        int n = nums.size();
        int low = 1;
        int high = n-2;
        // edge cases
        if(n == 1) return nums[0];
        if(nums[0] != nums[1]) return nums[0];
        if(nums[n-1] != nums[n-2]) return nums[n-1];

        while(low<=high){
            int mid = (low+high)/2;

            if(nums[mid] != nums[mid+1] && nums[mid] != nums[mid-1]){
                return nums[mid];
            }


            // check left half even and elimnate it
            if((nums[mid] == nums[mid-1] && mid%2 != 0) || (nums[mid] != nums[mid-1] && mid%2 == 0)){
                low = mid + 1;
            }
            else
            {
                high = mid - 1;
            }

        }

        // dummy return
        return -1;
    }
};
