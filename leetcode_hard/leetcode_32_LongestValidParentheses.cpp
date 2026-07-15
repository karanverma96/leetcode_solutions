class Solution {
public:
/* Approach: iterate from start to end on input string and from end to start on input string
           while iterating:
                       Use Sliding window logic to keep track of valid substrings
                       Slide the window when substring starting from window's left index if increased further will surely be invalid
                       manitain OpenCount and CloseCount for calculating valid substring length in O(1) time
                       keep updating maxLength if length of valid substring >= maxLength 
           Every Valid substring would have been checked when we are done with both the iterations
           Now you can return maxLength which will be the max of every valid substring length
*/
// T.C -> O(n) (two loops each with O(n) T.C) n = input string size
// S.C -> O(1)
    int longestValidParentheses(string s) {
        int maxLength = 0;
        int openCount = 0 , closeCount = 0;
        int i = 0 , n = s.size();

        /*  Rule: we will maintain a constraint closeCount <= openCount always true
            Logic:
            1) if rule does not break than we know if openCount == closeCount is true, we have a valid substring
            2) if openCount == closeCount && s[i] == ')' evaluates to true we need to reintialize so that we don't break our rule
        */
        while(i < n || openCount == closeCount){
            if(openCount == closeCount)
                maxLength = max(maxLength, openCount+closeCount);

            if(i >= n)
                break;
            if(openCount == closeCount && s[i] == ')')
            {
                openCount = 0; closeCount = 0;
                i++;
                continue;
            }

            /* if we reach till here that means this " openCount == closeCount && s[i] == ')' " 
               boolean expression was evaluated as false. because if it was evaluated as true
               than it must have gone inside the if{} and see there is a continue there around/at line 16
               So for that expression to be false there are two cases case1: openCount is not equal to closeCount
               Case 2: s[i] is not equal to ')' . If Case 1 than this code flow is in such a way that openCount > closeCount , closeCount can not come greater than OpenCount we don't let that happen.
               .If it is Case 2 than s[i] = ')' is false so the code flow will not reach closeCount++;
               Now you may be able to understand how this code preserves closeCount <= openCount constraint i made
               to solve this question.
            */
            if(s[i] == ')')
                closeCount++;
            else
                openCount++;
            i++;
        }

        /*  Rule: we will maintain a constraint closeCount >= openCount always true
            Logic:
            1) if rule does not break and openCount == closeCount is true, we have a valid substring.
            2) if openCount == closeCount && s[i] == '(' evaluates to true we need to reintialize so that we don't break our rule
        */
        i = n-1; openCount = 0; closeCount = 0; 
        while(i >= 0 || openCount == closeCount){
            if(openCount == closeCount)
                maxLength = max(maxLength, openCount+closeCount);

            if(i < 0) break;

            if(openCount == closeCount && s[i] == '(')
            {
                openCount = 0; closeCount = 0;
                i--;
                continue;
            }

           // Please see comment at the corresponding position in first loop
            if(s[i] == '(')
                openCount++;
            else
                closeCount++;
            i--;
        }

        //  maxLength will be correct because we are considering every valid substring
        return maxLength;
    }
};