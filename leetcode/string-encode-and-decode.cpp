// https://neetcode.io/problems/string-encode-and-decode?list=neetcode150

#include <bits/stdc++.h>
using namespace std;

class Solution
{
public:
    string encode(vector<string> &strs)
    {
        int n = strs.size();
        string s = "";
        for (int i = 0; i < n; i++)
        {
            s += strs[i] + "&&";
        }
        return s;
    }

    vector<string> decode(string s)
    {
        
    }
};
