// https://leetcode.com/problems/find-minimum-in-rotated-sorted-array/
#include <bits/stdc++.h>
using namespace std;
class Solution
{
public:
    int findMin(vector<int> &nums)
    {
        int first = nums[0];
        int n = nums.size();
        int l = 1;
        int r = n - 1;
        int mid;
        // search for the first index such as nums[index] <= fisrt
        while (l < r)
        {
            mid = (l + r) / 2;
            if (nums[mid] <= first)
            {
                r = mid;
            }
            else
            {
                l = mid + 1;
            }
        }
        return min(nums[r], first);
    }
};