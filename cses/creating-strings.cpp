// https://cses.fi/problemset/task/1622
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int k = 0;
int n = 0;
string s;
set<string> resss;
void strings(string s, multiset<char> st)
{
    if (st.empty())
    {
        resss.insert(s);
        return;
    }
    for (char elm : st)
    {
        multiset<char> st_copy = st;
        st_copy.erase(st_copy.find(elm));
        strings(s + elm, st_copy);
        k++;
    }
}

int main()
{
    cin >> s;
    n = s.length();
    multiset<char> st(s.begin(), s.end());
    strings("", st);
    cout << resss.size() << endl;
    for (const string &str : resss)
    {
        cout << str << endl;
    }
    return 0;
}