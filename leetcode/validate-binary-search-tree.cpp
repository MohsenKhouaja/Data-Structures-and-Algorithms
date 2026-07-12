// https://leetcode.com/problems/validate-binary-search-tree/
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

class Solution {
public:
    int kthSmallest(TreeNode* root, int k) {
        
    }
};

class Solution
{
    struct returnType
    {
        long long mx;
        long long mn;
        bool valid;
    };

public:
    bool isValidBST(TreeNode *root) { return isValidBST2(root).valid; }

    returnType isValidBST2(TreeNode *root)
    {
        if (root == nullptr)
        {
            return {LLONG_MIN, LLONG_MAX, true};
        }
        else
        {
            returnType left = isValidBST2(root->left);
            returnType right = isValidBST2(root->right);

            bool bothvalid = left.valid && right.valid;
            bool leftSmaller = left.mx < (root->val);
            bool rightBigger = right.mn > (root->val);
            returnType result = {
                maxx(left.mx, right.mx, root->val),
                minn(left.mn, right.mn, root->val),
                bothvalid && leftSmaller && rightBigger};
            return result;
        }
    }

private:
    long long maxx(long long a, long long b, long long c) { return max(a, max(b, c)); }
    long long minn(long long a, long long b, long long c) { return min(a, min(b, c)); }
};

/*
l'info eli bc ne5aha mellota func(l'info eli bch ne5aha melfo9)
{
    n7adher rohi 9bal menahbet
    nahbet
    n7adher rohi 9bel mantl3
}
*/
