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
        vector<pair<string, int>>& v =mp[key];
        int n = v.size();
        int l = 0;
        int r = n - 1;
        int mid = -1;
        int ans = -1;
        while (l <= r)
        {
            mid = (l + r) / 2;
            int currentTimestamp = v[mid].second;
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
        return (ans == -1 ? "" : v[ans].first);
    }
};

/**
 * Your TimeMap object will be instantiated and called as such:
 * TimeMap* obj = new TimeMap();
 * obj->set(key,value,timestamp);
 * string param_2 = obj->get(key,timestamp);
 */