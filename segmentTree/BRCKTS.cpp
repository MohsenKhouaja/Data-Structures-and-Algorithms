// https://www.spoj.com/problems/BRCKTS/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<int, bool> pib;
const int N = 2e5 + 1;
int n;
int a[N];
ll tree[4 * N];
ll neutral_element;

ll merge(ll x, ll y)
{
    neutral_element = 0;
    return x + y;
}
void build(int i = 0, int l = 0, int r = n - 1)
{
    if (l == r)
    {
        tree[i] = a[l];
        return;
    }
    int mid = (l + r) / 2;
    build(2 * i + 1, l, mid);
    build(2 * i + 2, mid + 1, r);
    tree[i] = merge(tree[2 * i + 1], tree[2 * i + 2]);
}
ll query(int l, int r, int i = 0, int ns = 0, int ne = n - 1)
{
    if (r < ns || l > ne)
    {
        return neutral_element;
    }
    if (l <= ns && r >= ne)
    {
        return tree[i];
    }
    else
    {
        ll mid = ((ns + ne) / 2);
        return merge(query(l, r, 2 * i + 1, ns, mid), query(l, r, 2 * i + 2, mid + 1, ne));
    }
}
void update(int index, ll value, int i = 0, int ns = 0, int ne = n - 1)
{
    if (index < ns || index > ne)
    {
        return;
    }
    if (ne == ns)
    {
        tree[i] = value;
        return;
    }
    int mid = ((ns + ne) / 2);
    update(index, value, 2 * i + 1, ns, mid);
    update(index, value, 2 * i + 2, mid + 1, ne);
    tree[i] = merge(tree[2 * i + 1], tree[2 * i + 2]);
}
int main()
{
    ios::sync_with_stdio(0);
    cin.tie(0);
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        char c;
        cin >> c;
        if (c == '(')
        {
            a[i] = 1;
        }
        else
        {
            a[i] = -1;
        }
    }
    build();
    int q;
    cin >> q;
    for (int i = 0; i < q; i++)
    {
        int x;
        cin >> x;
        if (x == 0)
        {
        }
        else
        {
            update(x - 1, (a[x - 1] == 1 ? 1 : -1));
        }
    }
    return 0;
}