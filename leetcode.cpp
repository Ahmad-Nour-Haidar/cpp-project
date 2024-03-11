#include <bits/stdc++.h>

using namespace std;

struct ListNode {
    int val;
    ListNode *next;

    ListNode() : val(0), next(nullptr) {}

    explicit ListNode(int x) : val(x), next(nullptr) {}

    ListNode(int x, ListNode *next) : val(x), next(next) {}
};

class Solution {
public:
    int pairSum(ListNode *head) {
        auto *slow = head;
        auto *fast = head;
        // find middle
        while (fast and fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        auto *mid = slow;
        stack<ListNode *> s;
        while (slow) {
            s.emplace(slow);
            slow = slow->next;
        }
        slow = head;
        int ans = 0;
        while (slow not_eq mid) {
            int top = s.top()->val;
            s.pop();
            ans = max(ans, slow->val + top);
            slow = slow->next;
        }
        return ans;
    }
};

int main() {


    return 0;
}
