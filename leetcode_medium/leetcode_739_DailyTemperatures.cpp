/*Intuition
In the Description of the question it is given that answer[i] = number of days you have to wait after the ith day to get a warmer temperature which if you see carefully boils down to answer[i] = j - i , where j is the index of next greater element for temperatures[i].

if something like next greater/smaller element or previous greater/smaller element is needed in the question, my thinking goes towards montonic stack.

What is montonic stack?. It's nothing but a stack with an invariant: elements from bottom to top will either be strictly increasing/decreasing.

So which invariant we need to maintain?
[73,74,75,75,71,69,72,76,73]
if you try to find the answer of this
test case using brute force and try to think how stack can help us.

You will realize we need to maintain strictly decreasing invariant.

Approach:
Now that we know we need a strictly decreasing stack, here is how we build it.

We maintain a stack of indices, not values, because we need the index to calculate j - i later. The invariant is that temperatures at these indices stay strictly decreasing from bottom to top.

For each day i, we look at the index sitting on top of the stack. If the stack is empty or temperature at that top index is still greater than temperatures[i], our decreasing invariant still holds so we just push i and move to next day.

But if temperatures[i] is greater than temperature at top index, that means day i is the next warmer day for whatever index is sitting on top. So we pop it and calculate i - index as its answer. We don't stop at just one pop, we keep popping and calculating answer as long as top of stack keeps losing to temperatures[i], because a single warmer day can be the answer for multiple previous days sitting in the stack, not just one. Once we hit an index whose temp is still bigger than temperatures[i], or stack becomes empty, we push i and continue to next day.

At the end whatever indices are still left in the stack never found a warmer day ahead, so their answer stays 0.

Complexity
Time complexity: O(n)
Space complexity: O(n)
*/

class Solution {
public:
    vector<int> dailyTemperatures(vector<int>& temperatures) {
        stack<int> st;
        int n = temperatures.size();
        vector<int> ans(n,0);

        // we need to mainatin stricly decreasing stack i.e monotonically decreasing
        for(int i = 0; i < n; i++)
        {
            if(st.empty() || temperatures[st.top()] > temperatures[i])
                st.push(i);
            else
            {
                while(!st.empty())
                {
                    if(temperatures[st.top()] < temperatures[i])
                    {
                        ans[st.top()] = i - st.top();
                        st.pop();
                    }
                    else
                        break;
                }
                st.push(i);
            }
        }

        return ans;
    }
};
 
