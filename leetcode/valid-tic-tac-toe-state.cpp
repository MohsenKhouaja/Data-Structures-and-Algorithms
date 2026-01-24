#include <bits/stdc++.h>
using namespace std;
bool wins(char c, vector<string> &board)
{
    if (board[0][0] == c && board[1][1] == c && board[2][2] == c)
    {
        return true;
    }
    if (board[0][2] == c && board[1][1] == c && board[0][2] == c)
    {
        return true;
    }
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == to_string(c + c + c))
        {
            return true;
        }
        if (board[i][0] == c && board[i][1] == c && board[i][2] == c)
        {
            return true;
        }
    }
    return false;
}
class Solution
{
public:
    bool validTicTacToe(vector<string> &board)
    {
        int nx = 0;
        int no = 0;
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                if (board[i][j] == 'X')
                {
                    nx++;
                }
                else if (board[i][j] == 'O')
                {
                    no++;
                }
            }
        }
        bool owins = no >= 3 && wins('O', board);
        bool xwins = nx >= 3 && wins('X', board);
        if (xwins && nx <= no)
        {
            return false;
        }
        if (owins && nx > no)
        {
            return false;
        }
        return nx == no || nx == 1 + no;
    }
};