// https://leetcode.com/problems/median-of-two-sorted-arrays/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;
class Solution
{
private:
    int infinity = 1e6 + 1;
    int negativeInfinity = -(1e6 + 1);
    double actualSolution(vector<int> &nums1, vector<int> &nums2)
    {
        int n1 = nums1.size();
        int n2 = nums2.size();
        bool isOdd = (n1 + n2) & 1;

        int half = (n1 + n2) / 2 + ((n1 + n2) % 2);
        // binary search on the number of elements eli bch ne5ouhom mel 1st array
        int l = 0;
        int r = n1;
        int mid;
        int numberOfElmsFrom1;
        while (l <= r)
        {
            numberOfElmsFrom1 = (l + r) / 2;
            int i = numberOfElmsFrom1 - 1;
            int j = half - i - 2;
            float aLeft = (i >= 0 ? nums1[i] : negativeInfinity);
            float bLeft = (j >= 0 ? nums2[j] : negativeInfinity);
            float aRight = (i + 1 <= n1 - 1 ? nums1[i + 1] : infinity);
            float bRight = (j + 1 <= n2 - 1 ? nums2[j + 1] : infinity);
            if (aLeft <= bRight && bLeft <= aRight)
            {
                float leftMax = aLeft > bLeft ? aLeft : bLeft;
                if (!isOdd)
                {
                    float rightMin = aRight < bRight ? aRight : bRight;
                    return ((leftMax + rightMin) / 2);
                }
                else
                {
                    return leftMax;
                }
            }
            else if (aLeft > bRight)
            {
                r = numberOfElmsFrom1 - 1;
            }
            else
            {
                l = numberOfElmsFrom1 + 1;
            }
        }
        return 0;
    }

public:
    double findMedianSortedArrays(vector<int> &nums1, vector<int> &nums2)
    {
        int n1 = nums1.size();
        int n2 = nums2.size();

        if (n1 == 0)
        {
            nums1.push_back(negativeInfinity);
            nums1.push_back(infinity);
        }
        if (n2 == 0)
        {
            nums2.push_back(negativeInfinity);
            nums2.push_back(infinity);
        }
        if (n1 > n2)
        {
            return actualSolution(nums2, nums1);
        }
        else
        {
            return actualSolution(nums1, nums2);
        }
    }
};
