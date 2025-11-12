// https://www.spoj.com/problems/KGSS/

#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef pair<ll, ll> pll;
const int N = 2e5 + 1;
int n;
int a[N];
vector<pll> tree(4 * N, make_pair(0, 0));
ll neutral_element;

pll merge(pll x, pll y)
{
    neutral_element = 0;
    return make_pair(max(x.first, y.first), max(x.first + y.first, max(x.second, y.second)));
}
void build(int i = 0, int l = 0, int r = n - 1)
{
    if (l == r)
    {
        tree[i] = make_pair(a[l], a[l]);
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
        return make_pair(0, 0);
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
        tree[i] = make_pair(value, value);
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
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    int q;
    cin >> q;
    ::n = n;
    build();
    while (q--)
    {
        char type;
        cin >> type;
        if (type == 'Q')
        {
            int l, r;
            cin >> l >> r;
            --l;
            --r;
            cout << query(l, r).second << '\n';
        }
        else if (type == 'U')
        {
            int idx;
            ll val;
            cin >> idx >> val;
            --idx;
            update(idx, val);
        }
    }

    return 0;
}