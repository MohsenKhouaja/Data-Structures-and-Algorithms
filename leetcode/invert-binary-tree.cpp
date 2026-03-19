// https://leetcode.com/problems/invert-binary-tree/description/
#pragma GCC optimize("O3,unroll-loops")
#pragma GCC target("avx2")
#include <bits/stdc++.h>
using namespace std;
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
    TreeNode *invertTree(TreeNode *root)
    {
        if (root == nullptr)
        {
            return root;
        }
        queue<TreeNode *> q;
        q.push(root);
        while (!q.empty())
        {
            TreeNode *current = q.front();
            q.pop();
            if (current->left != nullptr || current->right != nullptr)
            {
                TreeNode *temp = current->left;
                current->left = current->right;
                current->right = temp;
                if (current->right != nullptr)
                    q.push(current->right);
                if (current->left != nullptr)
                    q.push(current->left);
            }
        }
        return root;
    }
};