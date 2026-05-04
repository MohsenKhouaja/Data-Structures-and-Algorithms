// https://leetcode.com/problems/longest-repeating-character-replacement/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int characterReplacement(string s, int k)
    {
        int n = s.size();
        int mx = 1;
        int l = 0;
        int r = 0;
        int occOfMostCommonLetter = 1;
        map<char, int> mp;
        mp[s[r]]++;
        while (r <= n - 1)
        {
            for (char c = 'A'; c <= 'Z'; c++)
            {
                occOfMostCommonLetter = max(occOfMostCommonLetter, mp[c]);
            }
            cout << l << " " << r << " occ=" << occOfMostCommonLetter << endl;
            if (r - l + 1 - occOfMostCommonLetter > k)
            {
                mp[s[l]]--;
                l++;
            }
            else
            {
                mx = r - l + 1;
                if (r == n - 1)
                    return mx;
                r++;
                mp[s[r]]++;
            }
        }
        return mx;
    }
};

/*
AABABBA

Input: s = "AABABBB", k = 1
Output: 5


itha ken r-l +1 - k > occ
*/