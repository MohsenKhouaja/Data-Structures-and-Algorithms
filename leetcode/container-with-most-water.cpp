// https://leetcode.com/problems/container-with-most-water/description/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxArea(vector<int> &height)
    {
        int n = height.size();
        int l = 0;
        int r = n - 1;
        int water = 0;
        while (l < r)
        {
            water = max(water, (r - l) * min(height[l], height[r]));
            if (height[l] < height[r])
            {
                l++;
            }
            else
            {
                r--;
            }
        }
        return water;
    }
};