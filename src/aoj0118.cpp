/*
 * AOJ 0118: Property Distribution
 * 题意：m＊n矩阵中，共3种植物。相邻的同种植物块可合并，问合并后共多少块区域。
 * 类型：DFS＋记忆化搜索（／BFS／并查集）
 * 算法：从某点出发，向上下左右4个方向查询，若为同种植物则继续递归，经过的点需要记忆化。
 */

#include <cstdio>
#include <iostream>

using namespace std;

char mat[102][102];
int dx[4] = {0, 1, 0, -1};
int dy[4] = {1, 0, -1, 0};
int m, n;
int ans;

void dfs(int x, int y) {
  char t = mat[x][y];
  mat[x][y] = '.';
  for (int i = 0; i < 4; ++i) {
    int xx = x + dx[i];
    int yy = y + dy[i];
    if (xx >= 0 && xx < m && yy >= 0 && yy < n && mat[xx][yy] == t) {
      dfs(xx, yy);
    }
  }
}

void solve() {
  ans = 0;
  for (int i = 0; i < m; ++i) {
    cin >> mat[i];
  }
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (mat[i][j] != '.') {
        ++ans;
        dfs(i, j);
      }
    }
  }
}

int main() {
  while (cin >> m >> n && n > 0 && m > 0) {
    solve();
    cout << ans << endl;
  }
  return 0;
}
