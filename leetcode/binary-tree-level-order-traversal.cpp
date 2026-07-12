// https://leetcode.com/problems/binary-tree-level-order-traversal/description/
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
    map<int, vector<int>> mp;
    vector<vector<int>> levelOrder(TreeNode *root)
    {
        traverse(root, 0);
        vector<vector<int>> res;
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
        mp[level].push_back(root->val);
        traverse(root->left, level + 1);
        traverse(root->right, level + 1);
    }
};