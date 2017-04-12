/*
 * AOJ 0558: Cheese
 * 题意：m*n矩阵内，给出起点、1～N表示N个工厂、障碍、空格。求按顺序遍历1～N的最短路。
 * 类型：BFS＋Queue（／Dijkstra）
 * 算法：从S顺序通过1～N的最短路，可以用BFS求N次相邻序号间最短路的和。
 */

#include <cstdio>
#include <iostream>
#include <queue>
#include <cstring>

using namespace std;

typedef pair<int, int> pii;

int m, n, N;
char mat[1002][1002];
int d[1002][1002];
int sx[10], sy[10];
int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};
int ans;

int bfs(int sx, int sy, int tx, int ty) {
  memset(d, -1, sizeof(d));
  d[sx][sy] = 0;
  queue<pii> q;
  q.push(make_pair(sx, sy));
  int x, y, xx, yy;
  while (!q.empty()) {
    pii cur = q.front();
    q.pop();
    x = cur.first;
    y = cur.second;
    for (int i = 0; i < 4; ++i) {
      xx = x + dx[i];
      yy = y + dy[i];
      if (xx >= 0 && xx < m && yy >= 0 && yy < n && mat[xx][yy] != 'X' && d[xx][yy] == -1) {
        d[xx][yy] = d[x][y] + 1;
        if (xx == tx && yy == ty) {
          return d[xx][yy];
        }
        q.push(make_pair(xx, yy));
      }
    }
  }

}

void solve() {
  ans = 0;
  for (int i = 0; i < m; ++i) {
    cin >> mat[i];
    for (int j = 0; j < n; ++j) {
      if (mat[i][j] == 'S') {
        sx[0] = i;
        sy[0] = j;
      } else if (mat[i][j] >= '1' && mat[i][j] <= '9') {
        int t = mat[i][j] - '0';
        sx[t] = i;
        sy[t] = j;
      }
    }
  }
  for (int i = 1; i <= N; ++i) {
    int tmp = bfs(sx[i - 1], sy[i - 1], sx[i], sy[i]);
    ans += tmp;
  }
}

int main() {
  cin >> m >> n >> N;
  solve();
  cout << ans << endl;
  return 0;
}
