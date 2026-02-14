// https://leetcode.com/problems/time-based-key-value-store/description/
#include <bits/stdc++.h>
using namespace std;

class TimeMap
{
    map<string, vector<pair<string, int>>> mp;

public:
    TimeMap() {}
    void set(string key, string value, int timestamp)
    {
        mp[key].push_back(make_pair(value, timestamp));
    }

    string get(string key, int timestamp)
    {
        auto it = mp.find(key);
        if (it == mp.end())
        {
            return "";
        }
        int n = mp[key].size();
        int l = 0;
        int r = n - 1;
        int mid = -1;
        int ans = -1;
        while (l <= r)
        {
            mid = (l + r) / 2;
            int currentTimestamp = mp[key][mid].second;
            if (currentTimestamp <= timestamp)
            {
                l = mid + 1;
                ans = mid;
            }
            else
            {
                r = mid - 1;
            }
        }
        return (ans == -1 ? "" : mp[key][ans].first);
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,mp[key]alue,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */