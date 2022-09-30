#include <iostream>
#include <algorithm>
#include <vector>
#include <numeric>
#include <iterator>
#include <map>
#include <stack>
using namespace std;

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};
 
class Solution {
public:
    int maxProfit(vector<int>& prices) {
        auto _begin{ std::begin(prices) };
        auto _end{ std::prev(end(prices)) };
        int maxProfit{ 0 };
        while (_begin < _end) {
            while (*_begin >= *next(_begin)) {
                if (next(_begin) == _end)
                    return maxProfit;
                ++_begin;
            }
            while (*_end <= *prev(_end))
                --_end;
            if (*_end - *_begin > maxProfit)
                maxProfit = *_end - *_begin;
            ++_begin;
            --_end;
        }
        return maxProfit;
    }
};

int main()
{
    Solution S;
    //ListNode* list1 = new ListNode;
    //list1->val = 1;
    //list1->next = new ListNode;
    //list1->next->val = 2;
    //list1->next->next = new ListNode;
    //list1->next->next->val = 3;
    //list1->next->next->next = nullptr;

    //ListNode* list2 = new ListNode;
    //list2->val = 1;
    //list2->next = new ListNode;
    //list2->next->val = 3;
    //list2->next->next = new ListNode;
    //list2->next->next->val = 4;
    //list2->next->next->next = nullptr;
    vector<int> v{ 7,1,5,3,6,4};
    S.maxProfit(v);


}


    