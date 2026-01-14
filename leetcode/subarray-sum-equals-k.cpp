//https://leetcode.com/problems/subarray-sum-equals-k/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int subarraySum(vector<int> &nums, int k)
    {
        int n = nums.size();
        vector<int> prefix(n + 1);
        map<int, int> mp;
        long long s = 0;
        int res = 0;

        for (int i = 0; i < n + 1; i++)
        {
            if (i != 0)
            {
                s += nums[i - 1];
            }
            prefix[i] = s;
            res += (mp[s - k]);
            mp[s]++;
        }

        return res;
    }
};