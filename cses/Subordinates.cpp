#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    map<int, set<int>> s;
    for (int i = 0; i < n - 1; i++)
    {
        int a, b;
        cin >> a >> b;
    }
    cout << s.size() / 2 << endl;
    return 0;
}