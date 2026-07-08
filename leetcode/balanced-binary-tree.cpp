// https://leetcode.com/problems/balanced-binary-tree/
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
    bool res = true;
    bool isBalanced(TreeNode *root)
    {
        maxDepth(root);
        return res;
    }
    int maxDepth(TreeNode *root)
    {
        if (root == nullptr)
            return 0;
        int l = maxDepth(root->left);
        int r = maxDepth(root->right);
        if (abs(l - r) > 1)
            res = false;
        int depth = 1 + max(l, r);
        return depth;
    }
};