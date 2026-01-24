// https://leetcode.com/problems/best-time-to-buy-and-sell-stock/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int maxProfit(vector<int> &prices)
    {
        int n = prices.size();
        int mx = 0;
        vector<int> a(n);
        for (int i = 0; i < n; i++)
        {
            mx = max(mx, prices[n - 1 - i]);
            a[n - 1 - i] = mx;
        }
        mx = 0;
        for (int i = 0; i < n - 1; i++)
        {
            mx = max(mx,  a[i + 1]-prices[i] );
        }
        return mx;
    }
};
