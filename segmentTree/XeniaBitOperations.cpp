//https://codeforces.com/group/aSUzJqaRhR/contest/640520/problem/C

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const int N = 2e5 + 1;
ll n;
int a[N];
pll tree[4 * N];
pll neutral_element;

pll merge(pll x, pll y)
{
    neutral_element = make_pair(0, 0);
    if (x.second == 0)
    {
        return make_pair((x.first | y.first), 1 - x.second);
    }
    else
    {
        return make_pair((x.first ^ y.first), 1 - x.second);
    }
}
void build(int i = 0, int l = 0, int r = n - 1)
{
    if (l == r)
    {
        tree[i] = make_pair(a[l], 0);
        return;
    }
    int mid = (l + r) / 2;
    build(2 * i + 1, l, mid);
    build(2 * i + 2, mid + 1, r);
    tree[i] = merge(tree[2 * i + 1], tree[2 * i + 2]);
}
pll query(int l, int r, int i = 0, int ns = 0, int ne = n - 1)
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
        tree[i] = make_pair(value,tree[i].second);
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
    int q;
    cin >> n >> q;
    n = 1 << n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    build();
    for (int i = 0; i < q; i++)
    {
        int p, b;
        cin >> p >> b;
        update(p - 1, b);
        cout<<query(0, n - 1).first<<endl;
    }
    return 0;
}