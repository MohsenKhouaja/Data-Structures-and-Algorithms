// https://leetcode.com/problems/group-anagrams/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<vector<string>> groupAnagrams(vector<string> &strs)
    {
        vector<vector<string>> res;
        unordered_map<string, vector<string>> map;
        int n = strs.size();
        for (int i = 0; i < n; i++)
        {
            string current = strs[i];
            sort(current.begin(), current.end());
            map[current].push_back(strs[i]);
        }
        for (auto elm : map)
        {
            res.push_back(elm.second);
        }
        return res;
    }
};
