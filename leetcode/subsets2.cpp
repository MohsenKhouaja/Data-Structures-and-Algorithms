// https://leetcode.com/problems/subsets-ii/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<int>> res;
    set<string> signatures;
    vector<vector<int>> subsetsWithDup(vector<int> &nums)
    {
        map<int, int> mp;
        vector<int> curr;
        dfs(nums, curr, mp, 0);
        return res;
    }
    string sign(map<int, int> occ)
    {
        string signature = "";
        for (auto [num, val] : occ)
        {
            int x = num;
            int y = val;
            signature += to_string(x) + ":" + to_string(y) + ",";
        }
        return signature;
    }
    void dfs(vector<int> &nums, vector<int> curr, map<int, int> currOcc, int pos)
    {
        if (pos == nums.size())
        {
            string signature = sign(currOcc);
            if (signatures.find(signature) == signatures.end())
            {
                res.push_back(curr);
                signatures.insert(signature);
            }
            return;
        }
        int currInt = nums[pos];
        dfs(nums, curr, currOcc, pos + 1);
        curr.push_back(currInt);
        currOcc[currInt]++;
        dfs(nums, curr, currOcc, pos + 1);
    }
};