#include <bits/stdc++.h>
using namespace std;
map<int, int> res;

int numberOfSubordinates(int root, vector<vector<int>> &graph)
{
    int number = graph[root].size();
    for (int i = 0; i < graph[root].size(); i++)
    {
        number += numberOfSubordinates(graph[root][i], graph);
    }
    res[root] = number;
    return number;
}

void printGraph(const vector<vector<int>> &graph)
{
    cout << "Graph:" << endl;
    for (int i = 0; i < graph.size(); i++)
    {
        cout << "  " << i << " -> [";
        for (int j = 0; j < graph[i].size(); j++)
        {
            cout << graph[i][j];
            if (j + 1 < graph[i].size())
                cout << ", ";
        }
        cout << "]" << endl;
    }
    cout << endl;
}

void solve()
{
    int n;
    cin >> n;
    vector<vector<int>> graph(n + 1);
    for (int i = 0; i < n - 1; i++)
    {
        int x;
        cin >> x;
        graph[x].push_back(i + 2);
    }
    //   printGraph(graph);
    res[1] = numberOfSubordinates(1, graph);
    for (auto elm : res)
    {
        cout << elm.second << " ";
    }
}

int main()
{
    int t = 1;
    //    cin >> t;
    while (t--)
    {
        solve();
    }
    return 0;
}
