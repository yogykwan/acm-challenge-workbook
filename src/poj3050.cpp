/*
 * POJ 3050: Hopscotch
 * 题意：给出5*5的数字矩阵，从某点出发，向上下左右移动，总共经过6个点，并将其拼接为整数。求通过不同的起点和行走方式，最终可以得到多少个不同的整数。
 * 类型：DFS
 * 算法：经过一点，记录进路径，向4方未越界的点继续递归。移动5步可得到1个整数，若为新数则结果＋1。
 */


#include <cstdio>
#include <iostream>
#include <cstring>

using namespace std;

int mat[5][5];
int d[6];
int ans;
bool f[1000000];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {-1, 0, 1, 0};

void dfs(int x, int y,int step) {
    d[step] = mat[x][y];
    if(step == 5) {
        int tmp = 0;
        for(int i = 0; i < 6; ++i) {
            tmp = tmp * 10 + d[i];
        }
        if(!f[tmp]) {
            f[tmp] = true;
            ans++;
        }
        return;
    }
    int xx, yy;
    for(int i = 0; i < 4; ++i) {
        xx = x + dx[i];
        yy = y + dy[i];
        if(xx >=0 && xx < 5 && yy >= 0 && yy < 5) {
            dfs(xx, yy, step + 1);
        }
    }
}

void solve() {
    ans = 0;
    memset(f, 0 ,sizeof(f));
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            dfs(i, j, 0);
        }
    }
}

int main() {
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            cin >> mat[i][j];
        }
    }
    solve();
    cout << ans << endl;
    return 0;
}

