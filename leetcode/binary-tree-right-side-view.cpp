// https://leetcode.com/problems/binary-tree-right-side-view/description/
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
    map<int, int> mp;
    vector<int> rightSideView(TreeNode *root)
    {
        traverse(root, 0);
        vector<int> res;
        for (auto elm : mp)
        {
            res.push_back(elm.second);
        }
        return res;
    }
    void traverse(TreeNode *root, int level)
    {
        if (root == nullptr)
        {
            return;
        }
        if (mp.find(level) == mp.end())
        {
            mp[level] = root->val;
        }
        traverse(root->right, level + 1);
        traverse(root->left, level + 1);
    }
};