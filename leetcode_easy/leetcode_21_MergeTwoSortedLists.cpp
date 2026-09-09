/*Intuition
My first thought was: we're given two sorted linked lists and we need to merge them. That reminded me of how I used to merge two sorted arrays, which brought Merge Sort to mind and specifically the merge function.

So we need to apply the same algorithm that we used in merge function on differnt data structure i.e LinkedList.

Iterating with two pointers and comparing values with <= works fine with LinkedList as well, so no issue there.

But in merge function we needed a temp array to hold the sorted elements. Here we don't need that we can just create a dummy node, keep a tail pointer and attach whatever node we need directly to tail->next. By doing like this we are just splicing together nodes from the two given lists.
Approach (I recommend skimming through my code once before reading the approach)

Design Decision: Why a dummy node? Using a dummy node as the starting point for tail means we don't need to check if list1 is null, if list2 is null, or if both are null and at the end, we can simply return dummy->next as the new head.

Main loop logic: We attach whichever node is smaller, list1's or list2's to tail, then move that list's pointer one step ahead. If both values are equal, list1's node is attached. Since we always attach the smaller of the two, the merged list is built in non-decreasing order.

Handling leftovers: Once we're out of the loop, one of the two lists is guaranteed to be nullptr. The last node in the merged list is always ≤ to the first leftover node in the remaining list and since that leftover list is already sorted. We can just attach the rest of it directly.

Best Practice: Why delete dummy? dummy is heap allocated. If we don't delete it before returning than that memory stays allocated with no way to reach it later and as C++ don't have garabage collector this leads to memory Leak.

Complexity
Time complexity:
O(n+m) where n is the size of list1 and m is the size of list2.

Space complexity:
Auxiliary Space complexity: O(1)

*/
/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
        ListNode* dummy = new ListNode();
        ListNode* tail = dummy;

        while(list1 != nullptr && list2 != nullptr){
            if(list1->val <= list2->val)
            {
                tail->next = list1;
                list1 = list1->next;
            }
            else
            {
                tail->next = list2;
                list2 = list2->next;
            }

            tail = tail->next;
        }

        while(list1 != nullptr){
            tail->next = list1;
            list1 = list1->next;
            tail = tail->next;
        }

        while(list2 != nullptr){
            tail->next = list2;
            list2 = list2->next;
            tail = tail->next;
        }

        ListNode* newHead = dummy->next;
        delete dummy;
        return newHead;
    }
};

/*Why This Approach Works (Detailed Reasoning)

Design decision: the dummy node

If we started with tail = list1, list1 could be nullptr according to the problem constraints. Since we use tail to build the new list, connecting a node means doing tail->next, and if tail itself is nullptr than you will get runtime error. To handle this, we'd need to check if list1 is null, and if it is, fall back to list2 (assuming at least one list isn't null) and separately handle the case where both are null.

Let's say we handled all of that with extra conditions and also added a condition to make sure the smaller value becomes the starting tail.Now Building the list itself would work fine but when it's time to return, we no longer have the new head pointer since tail has moved forward. We'd need store which one was smaller in some variable just to return it later.That's a lot of if conditions and extra variable for something that can be solved more simply: create a new node, call it dummy and set tail = dummy. dummy has no relation to either list's nodes and at the end we can simply return dummy->next as the new head.

Correctness: why the merge stays sorted

Conceptually, the main loop is attaching nodes from list1 and list2 whichever is smaller gets attached first, and these attached nodes form our new merged list. The attached node is always the smaller of the two and if both are equal we attach list1's node.Whichever list the node is attached from that list's pointer moves one step ahead. Since we always attach the smaller value that's why the merge list stays sorted.

Correctness: why the leftovers are safe to attach directly

Once we're out of the while loop, one of the two lists is guaranteed to be nullptr. Say list1 still has nodes left and list2 is exhausted: every node from list2 is already in its correct position in the merged list so the merged list so far is fully sorted.The last node attached to the merged list will always be less than or equal to the first leftover node in list1 and since list1's leftover nodes are already sorted among themselves, we can attach them directly.

Memory management(Best Practice for C++): why we delete dummy

If we don't call delete dummy before the function returns than the memory allocated on the heap doesn't get cleaned up automatically, since C++ has no garbage collector. Once we go out of scope, we also lose the pointer to that memory, so we have no way to delete it ourselves. That's a memory leak and repeated leaks like this can eventually lead to consumption of significant memory.
*/