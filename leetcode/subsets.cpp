// https://leetcode.com/problems/subsets/description/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> res;
    vector<vector<int>> subsets(vector<int> &nums)
    {
        vector<int> v;
        solve(nums, v, 0);
        return res;
    }
    void solve(vector<int> &nums, vector<int> curr, int pos)
    {
        if (pos == nums.size())
        {
            res.push_back(curr);
            return;
        }
        solve(nums, curr, pos + 1);
        curr.push_back(nums[pos]);
        solve(nums, curr, pos + 1);
    }
};