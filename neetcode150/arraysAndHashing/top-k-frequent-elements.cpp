// https://leetcode.com/problems/top-k-frequent-elements/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> topKFrequent(vector<int> &nums, int k)
    {
        unordered_map<int, int> occ;
        int n = nums.size();
        for (int i = 0; i < n; i++)
        {
            occ[nums[i]]++;
        }
        vector<pair<int, int>> v;
        for (auto elm : occ)
        {
            v.push_back(make_pair(elm.second, elm.first));
        }
        sort(v.begin(), v.end());
        vector<int> res;
        int m = v.size();
        for (int i = m - 1; (i >= m - k) && (i >= 0); i--)
        {
            res.push_back(v[i].second);
        }
        return res;
    }
};