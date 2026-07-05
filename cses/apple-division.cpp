// https://cses.fi/problemset/task/1623
#include <bits/stdc++.h>
using namespace std;
#define ll long long
int n;
ll mn = 20e9;
int a[20];

void division(ll div1, ll div2, int i)
{
    if (i == n)
    {
        mn = min(mn, abs(div1 - div2));
        return;
    }
    division(div1 + a[i], div2, i + 1);
    division(div1, div2 + a[i], i + 1);
}

int main()
{
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    division(0, 0, 0);
    cout << mn << endl;
    return 0;
}