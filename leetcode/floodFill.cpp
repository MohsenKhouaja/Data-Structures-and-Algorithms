#include <bits/stdc++.h>
using namespace std;
class Solution {
public:
    vector<vector<int>> floodFill(vector<vector<int>>& image, int sr, int sc, int color) {
        int n = image.size();
        int m = image[0].size();
        int originalColor = image[sr][sc];
        vector<int> dx={1,0,-1,0};
        vector<int> dy={0,1,0,-1};
        queue<pair<int,int>> q;
        q.push(make_pair(sr,sc));
        vector<vector<int>> visited(n,vector<int>(m,false)) ;
        while(!q.empty())
        {
            pair<int,int> current= q.front();
            q.pop();
            visited[current.first][current.second]=true;
            image[current.first][current.second]=color;
            for(int i=0; i<4;i++)
            {
                bool b = current.first+dx[i]<n && current.first+dx[i]>=0 && current.second+dy[i]<m && current.second+dy[i]>=0;
                pair<int,int> newp= make_pair(current.first+dx[i],current.second+dy[i]);
                if(b && image[newp.first][newp.second]==originalColor && !visited[newp.first][newp.second]){
                    image[newp.first][newp.second]=color;
                    visited[newp.first][newp.second]=true;
                    q.push(newp);
                }
            }
        }
        return image;

    }
};