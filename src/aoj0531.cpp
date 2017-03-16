/*
 * AOJ 0531: Paint Color
 * 题意：在画板上有n个矩形护板，被护板隔离开的区域需要染上不同颜色，求染色数。
 * 类型：离散化+扫描线+BFS
 * 算法：将坐标离散化后，整个画板变成2nx2n的网格。用水平扫描线向上扫描，遇到矩形下边对应列短边-1，遇到上边+1。值为0的短线上方为无护板单元，BFS搜索其组成的森林。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>
#include <iostream>
#include <queue>

using namespace std;

queue<int> q;

int xx[2010], yy[2010];

int mat[2010][2010];
bool vis[2010][2010];

int dx[4] = {-1, 0, 1, 0};
int dy[4] = {0, 1, 0, -1};

struct Rect {
  int x1, x2, y1, y2;
} rect[1010];

struct Line {
  int y, x1, x2;
  int ud;

  bool operator<(const Line &l) const {
    return y < l.y;
  }
} line[2010];

int main() {
  int w, h, n;
  while (scanf("%d%d", &w, &h) != EOF && w) {
    scanf("%d", &n);
    for (int i = 0; i < n; ++i) {
      scanf("%d%d%d%d", &rect[i].x1, &rect[i].y1, &rect[i].x2, &rect[i].y2);
      xx[i << 1] = rect[i].x1;
      xx[i << 1 | 1] = rect[i].x2;
      yy[i << 1] = rect[i].y1;
      yy[i << 1 | 1] = rect[i].y2;
    }

    xx[n << 1] = 0;
    xx[n << 1 | 1] = w;
    yy[n << 1] = 0;
    yy[n << 1 | 1] = h;

    // 离散化

    int cnt = n + n + 2;
    int cntx, cnty;
    sort(xx, xx + cnt);
    sort(yy, yy + cnt);
    cntx = unique(xx, xx + cnt) - xx;
    cnty = unique(yy, yy + cnt) - yy;

    for (int i = 0; i < n; ++i) {
      int x1, y1, x2, y2;
      x1 = lower_bound(xx, xx + cntx, rect[i].x1) - xx;
      x2 = lower_bound(xx, xx + cntx, rect[i].x2) - xx;
      y1 = lower_bound(yy, yy + cnty, rect[i].y1) - yy;
      y2 = lower_bound(yy, yy + cnty, rect[i].y2) - yy;

      line[i << 1].y = y1;
      line[i << 1].ud = 1;
      line[i << 1].x1 = x1;
      line[i << 1].x2 = x2;
      line[i << 1 | 1].y = y2;
      line[i << 1 | 1].ud = -1;
      line[i << 1 | 1].x1 = x1;
      line[i << 1 | 1].x2 = x2;
    }
    sort(line, line + n + n);

    // 扫描线

    memset(mat, 0, sizeof(mat));
    for (int i = 0; i < n + n; ++i) {
      int y = line[i].y;
      for (int j = line[i].x1; j < line[i].x2; ++j) {
        mat[y][j] += line[i].ud;
      }
    }
    for (int i = 1; i < cnty - 1; ++i) {
      for (int j = 0; j < cntx - 1; ++j) {
        mat[i][j] += mat[i - 1][j];
      }
    }

//    for (int i = 0; i < cnty - 1; ++i) {
//      for (int j = 0; j < cntx - 1; ++j) {
//        printf("%d ", mat[i][j]);
//      }
//      printf("\n");
//    }

    // BFS

    int ans = 0;
    memset(vis, 0, sizeof(vis));
    for (int i = 0; i < cnty - 1; ++i) {
      for (int j = 0; j < cntx - 1; ++j) {
        if (mat[i][j] || vis[i][j]) continue;
        ++ans;
        q.push(i * cnt + j);
        while (!q.empty()) {
          int x, y;
          x = q.front() / cnt;
          y = q.front() % cnt;
          q.pop();
          int nx, ny;
          for (int k = 0; k < 4; ++k) {
            nx = x + dx[k];
            ny = y + dy[k];
            if (nx >= 0 && nx < cnty - 1 && ny >= 0 && ny < cntx - 1 && !vis[nx][ny] && !mat[nx][ny]) {
              vis[nx][ny] = 1;
              q.push(nx * cnt + ny);
            }
          }
        }
      }
    }

    printf("%d\n", ans);
  }
  return 0;
}
