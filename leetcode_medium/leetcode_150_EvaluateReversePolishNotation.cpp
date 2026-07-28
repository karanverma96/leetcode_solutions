
/* # Intuition Building:

Reverse Polish Notation is a postfix notation.
23- = 2-3, 32- = 3-2, 456\*+ = 4 + (6\*5), 4567*+- = 4 - ( (7*6) + 5 ) 
if we iterate over the tokens and we encounter an opertor than we need the previous 2 token for evaluating the expression. For "+" and "\*" the order of last two operands does not matter but for '-' and '/' it matters.
As there can be variable number of operands before we encounter an opertor and then just after that we again encounter an operator. So we can not just use fixed number of variables to keep track of last 2 operands. We need to use some datastructure in which we will be inserting the operands in left to right order and then we need that data structure to give us the last 2 inserted operands i.e Last 2 In and those first 2 out in bottom to top order --> LIFO , we need to use stack data structure.

# Approach:
1) Traverse the tokens array from left to right.
2) if Token is operand, push it to the stack.
3) if Token is operator. take the top two elements. first top element is
right operator and 2nd top is left operator (now pop them), process the operands with operator. Push the resulting value on to the stack.
4) Return the top element on the stack when the traversal is done.

Complexity
- Time complexity:
O(n)

- Space complexity:
O(n)
*/

// # Code:
class Solution {
public:
    int evalRPN(vector<string>& tokens) {
        stack<int> st; //taken the data type of the elements as int because we will only be pushing the operands or resulting value to the stack.

        for(auto& token : tokens){

            /* || operator helps in reducing code 
                Observe I could have used if elseif
                but the following two lines are same:
                int rightOper = st.top(); st.pop();
                int leftOper = st.top(); st.pop();
                for all the four operators.
            */
            if(token == "+" || token == "-" || token == "*" || token == "/"){
                int rightOper = st.top(); st.pop();
                int leftOper = st.top(); st.pop();

                // token[0] rather than of just token because switch statement does not support string
                switch(token[0]){
                    case '+':
                        st.push(leftOper + rightOper);
                        break;
                    case '-':
                        st.push(leftOper - rightOper);
                        break;
                    case '*':
                        st.push(leftOper * rightOper);
                        break;
                    case '/':
                        st.push(leftOper / rightOper);
                        break;
                }
            }
            else{
                st.push(stoi(token));
            }
        }

        return st.top();
    }
};