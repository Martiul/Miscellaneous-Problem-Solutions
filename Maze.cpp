#include <iostream>
#include <queue>
#include <cstring>
#include <stdio.h>
#define MAXN 10005
using namespace std;

char grid[21][21];
int dist[21][21];

int main()
{
    int t,r,c;
    int y,x,dist_here;
    queue <pair <int,int> > q;
    cin >> t;

    for (int i = 0; i < t; i++) {
        cin >> r >> c;

        // Get input and set dist array
        for (int j = 0; j < r; j++) {
            for (int k = 0; k < c; k++) {
                cin >> grid[j][k];
                dist[j][k] = MAXN;
            }
        }

        q.push(make_pair(0,0));
        if (grid[0][0] != '*')
            dist[0][0] = 1;

        while (!q.empty()) {
            y = q.front().first;
            x = q.front().second;
            q.pop();

            // This square should be -1
            if (grid[y][x] == '*')
                dist[y][x] = -1;

            // Not out of bounds or at a wall
            if (0 <= y && y < r && 0 <= x && x < c && grid[y][x] != '*') {
                dist_here = dist[y][x];

                // '-'
                if (grid[y][x] == '-' || grid[y][x] == '+') {
                    if (x != 0 && dist_here+1 < dist[y][x-1]) {
                        q.push(make_pair(y,x-1));
                        dist[y][x-1] = dist_here+1;
                    }
                    if (x != c-1 && dist_here+1 < dist[y][x+1]) {
                        q.push(make_pair(y,x+1));
                        dist[y][x+1] = dist_here+1;
                    }
                }
                // '|'
                if (grid[y][x] == '|' || grid[y][x] == '+') {
                    if (y != 0 && dist_here+1 < dist[y-1][x]) {
                        q.push(make_pair(y-1,x));
                        dist[y-1][x] = dist[y][x]+1;
                    }
                    if (y != r-1 && dist_here+1 < dist[y+1][x]) {
                        q.push(make_pair(y+1,x));
                        dist[y+1][x] = dist_here+1;
                    }
                }
            }
        }
        if (dist[r-1][c-1] == MAXN)
            cout << -1 << endl;
        else
            cout << dist[r-1][c-1] << endl;
    }
}
