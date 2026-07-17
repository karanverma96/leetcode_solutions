class Solution {
public:
    /* what is Median:
                      mid = n/2 , where n is the size of the array
                      if you have even number of elements and you sort them than median = (nums[mid] + nums[mid+1])/2.0
                      if you have odd number of elements and you sort them than median = nums[mid]
    */

    /*Pure Brute Force Approach:
                    create a temp array
                    populate it with nums1 elements and nums2 elements
                    sort the temp array and now you can find the median
    */
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();

        vector<int> temp;

        for(const auto& num : nums1)
            temp.push_back(num);
        for(const auto& num : nums2)
            temp.push_back(num);
        
        sort(temp.begin(),temp.end());

        int mid = (m+n)/2;

        if( (m+n)%2 == 1)// odd number of elements
            return temp[mid];
        
        return (temp[mid] + temp[mid-1])/2.0;
    }
};


class Solution {
public:

    /* what is Median:
                      mid = n/2 , where n is the size of the array
                      if you have even number of elements and you sort them than median = (nums[mid] + nums[mid+1])/2.0
                      if you have odd number of elements and you sort them than median = nums[mid]
    */

    /* Better Approach:
                    merge the two sorted array using two pointer approach and place it in a temp array
                    as we used to do in merge sort.
                    Now we have the merged sorted array now you can return the median
    */
    // T.C -> O(m+n) , S.C -> O(m+n)
    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int i = 0, j = 0;
        vector<int> temp(m+n);
        int k = 0;

        while(i < m && j < n){

            if(nums1[i] <= nums2[j])
                temp[k++] = nums1[i++];
            else
                temp[k++] = nums2[j++];
            
        }

        while(i < m)
            temp[k++] = nums1[i++];

        while(j < n)
            temp[k++] = nums2[j++];

        int mid = (m+n)/2;

        if( (m+n)%2 == 1)// means total odd number of elements
            return temp[mid];
        
        return (temp[mid] + temp[mid-1])/2.0;
    }
};

class Solution {
public:
    /* what is Median:
                      mid = n/2 , where n is the size of the array
                      if you have even number of elements and you sort them than median = (nums[mid] + nums[mid+1])/2.0
                      if you have odd number of elements and you sort them than median = nums[mid]
    */

    /* more Better Approach in terms of S.C:
                    Find the elements which will be at middle indexes if we had a merge sorted array
                    Two pointer approach will be used same as we do in merge part of merge sort algo
                    , the difference here will be we will just keep track if any pointer reached any of
                    the middle indexes , we will not store the whole merged sorted array as there is no need
                    for that in this question. 
    */
    // T.C -> O(m+n) , S.C -> O(1)


    double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
        int m = nums1.size(), n = nums2.size();
        int i = 0, j = 0, k = 0;
        int firstMidIndex = (m+n)/2 - 1;
        int secondMidIndex = firstMidIndex + 1;
        int element1, element2;

        while(i < m && j < n){

            if(nums1[i] <= nums2[j]){
                if(k == firstMidIndex)
                    element1 = nums1[i];

                if(k == secondMidIndex)
                    element2 = nums1[i];
                i++;
            }
            else
            {
                if(k == firstMidIndex)
                    element1 = nums2[j];

                if(k == secondMidIndex)
                    element2 = nums2[j];
                j++;
            }

            k++;
        }

        while(i < m){
            if(k == firstMidIndex)
                element1 = nums1[i];

            if(k == secondMidIndex)
                    element2 = nums1[i++];
            i++; k++;
        }

        while(j < n){
            if(k == firstMidIndex)
                element1 = nums2[j];

            if(k == secondMidIndex)
                    element2 = nums2[j];
            j++; k++;
        }

        if( (m+n)%2 == 1) // odd number of elements
            return element2;

        return (element1 + element2)/2.0;
    }
};


