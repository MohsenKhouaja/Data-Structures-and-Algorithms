// https://neetcode.io/problems/two-integer-sum?list=neetcode150

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    vector<int> twoSum(vector<int> &nums, int target)
    {
        int n = nums.size();
        int l = 0;
        int r = n - 1;
        vector<pair<int, int>> v;
        for (int i = 0; i < n; i++)
        {
            v.push_back(make_pair(nums[i], i));
        }

        sort(v.begin(), v.end());
        while (l < r)
        {
            if (v[l].first + v[r].first == target)
            {
                vector<int> res;
                res.push_back(v[l].second);
                res.push_back(v[r].second);
                sort(res.begin(), res.end());
                return res;
            }
            else if (v[l].first + v[r].first < target)
            {
                l++;
            }
            else
            {
                r--;
            }
        }
    }
};
