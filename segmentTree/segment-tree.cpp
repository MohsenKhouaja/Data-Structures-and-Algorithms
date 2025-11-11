#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const int N = 2e5 + 1;
int n;
int a[N];
ll tree[4 * N];
ll neutral_element ;

ll merge(ll x, ll y) 
{
    neutral_element =1e9+1  ;
    return min(x,y);
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
    int q;
    cin >> n >> q;
    for (int i = 0; i < n; i++)
    {
        cin >> a[i];
    }
    build();
    for (int i = 0; i < q; i++)
    {
        int t, a, b;
        cin >> t >> a >> b;
        switch (t)
        {
        case 1:
            a--;
            update(a, b);
            break;
 
        default:
            a--;
            b--;
            cout << query(a, b) << endl;
            break;
        }
    }
    return 0;
}