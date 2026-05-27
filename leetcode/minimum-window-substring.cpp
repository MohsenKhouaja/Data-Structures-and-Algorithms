// https://leetcode.com/problems/minimum-window-substring/description/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    int tArr[52] = {0};
    int sArr[52] = {0};
    bool boolean = false;
    set<pair<int, string>> substrings;
    inline bool sIncludesT()
    {
        for (int i = 0; i < 52; i++)
        {
            if (sArr[i] < tArr[i])
                return false;
        }
        return true;
    }
    int indexInAlphabet(char c)
    {
        if ('a' <= c && c <= 'z')
            return c - 'a';
        else
            return c - 'A' + 26;
    }
    string minWindow(string s, string t)
    {
        int n = s.size();
        int m = t.size();
        for (int i = 0; i < m; i++)
        {
            tArr[indexInAlphabet(t[i])]++;
        }
        int l = 0;
        int r = 0;
        sArr[indexInAlphabet(s[0])]++;
        while (r < n)
        {
            if (!sIncludesT())
            {
                r++;
                if (r < n)
                {
                    sArr[indexInAlphabet(s[r])]++;
                }
            }
            if (sIncludesT())
            {
                while (l <= r && sIncludesT())
                {
                    sArr[indexInAlphabet(s[l])]--;
                    l++;
                }
                substrings.insert(make_pair(r - l, s.substr(l - 1, r - (l - 1) + 1)));
            }
        }
        return substrings.empty() ? "" : substrings.begin()->second;
    }
};
