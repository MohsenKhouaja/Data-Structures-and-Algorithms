// https://leetcode.com/problems/maximum-depth-of-binary-tree/description/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;

// Definition for a binary tree node.
struct TreeNode
{
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
};


class Solution
{
public:
    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        stack<pair<TreeNode *, int>> q;
        q.push(make_pair(root, 1));
        int mx = 1;
        while (!q.empty())
        {
            TreeNode *current = q.top().first;
            int depth = q.top().second;
            mx = max(mx, depth);
            q.pop();
            if (current->left != nullptr)
            {
                q.push(make_pair(current->left, depth+1));
            }
            if (current->right != nullptr)
            {
                q.push(make_pair(current->right, depth+1));
            }
        }
        return mx;
    }
};