// https://leetcode.com/problems/permutation-in-string/description/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool checkInclusion(string s1, string s2)
    {
        if (s2.length() < s1.length())
            return false;
        int freq1[26] = {};
        int freq2[26] = {};
        int ns1 = s1.size();
        for (int i = 0; i < ns1; i++)
        {
            freq1[s1[i] - 'a']++;
            freq2[s2[i] - 'a']++;
        }
        int l = 0;
        int r = l + ns1 - 1;
        while (r < s2.size())
        {
            bool compare = true;
            for (int i = 0; i < 26; i++)
            {
                if (freq1[i] != freq2[i])
                {
                    compare = false;
                    break;
                }
            }
            if (compare)
                return true;
            r++;
            if (r < s2.size())
                freq2[s2[r] - 'a']++;
            freq2[s2[l] - 'a']--;
            l++;
        }
        return false;
    };
};
