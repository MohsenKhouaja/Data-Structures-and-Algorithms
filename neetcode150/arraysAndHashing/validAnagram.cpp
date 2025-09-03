// https://leetcode.com/problems/valid-anagram/submissions/1757496777/
#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    bool isAnagram(string s, string t)
    {
        if (s.length() != t.length())
            return false;
        map<char, int> letters;
        int n = s.length();
        for (int i = 0; i < n; i++)
        {
            letters[t[i]]--;
            letters[s[i]]++;
        }
        for (const auto elm : letters)
        {
            if (elm.second != 0)
            {
                return false;
            }
        }
        return true;
    }
};