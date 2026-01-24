// https://leetcode.com/problems/find-the-first-player-to-win-k-games-in-a-row/description/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int findWinningPlayer(vector<int> &skills, int k)
    {
        int n = skills.size();
        vector<int> prefix(n - 1);
        map<int, int> mp;
        int mx = skills[0];
        for (int i = 0; i < n - 1; i++)
        {
            if (skills[i + 1] > mx)
            {
                mx = skills[i + 1];
            }
            mp[mx]++;
        }
        int res = 0;
        for (int i = 0; i < n; i++)
        {
            if (mp[skills[i]] >= k)
            {
                res = i;
                break;
            }
            if (skills[i] == mx)
            {
                res = i;
                break;
            }
        }
        return res;
    }
};