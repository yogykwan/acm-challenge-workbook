/*
 * POJ 2032: Square Carpets
 * 题意：mxn的01矩阵，需要用方毯覆盖所有的1，但不能覆盖到0，方毯边长可不同，毯子之间可覆盖但不可折叠。求最少多少块方毯可以覆盖所有1。
 * 类型：DP+贪心+IDA*
 * 算法：DP计算以任意点为左上顶点时最大方形边长，去除被大方形包含的小方形后，找到只能被一个方形覆盖的点，则该方形必选，其他方形放入待选队列DFS。迭代加深A*，评估函数为未被覆盖的点数除以最大方形面积。关键剪枝：由于毯子是从左上到右下枚举，每次需保证上方全部覆盖。
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef pair<int, int> pii;

int a[10][10];
int m, n;

int b[10][10];
int mm;
vector<pii> c[10][10];

bool must[10][10];

pii p[100];
int tot;

int vis[10][10];

int GaoH() {
  int ret = 0;
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (a[i][j] && !vis[i][j]) {
        ++ret;
      }
    }
  }
  return (ret + mm - 1)/ mm;
}

bool Over() {
  for (int i = 0; i < m; ++i) {
    for (int j = 0; j < n; ++j) {
      if (a[i][j] && !vis[i][j]) {
        return false;
      }
    }
  }
  return true;
}

bool Dfs(int dep, int cur, int limit) {
  if (cur == limit) {
    return Over();
  }
  if (cur + GaoH() > limit) {
    return false;
  }
  if (dep == tot) {
    return false;
  }

  int x = p[dep].first, y = p[dep].second;
  for (int i = 0; i < x; ++i) {
    for (int j = 0; j < n; ++j) {
      if (a[i][j] && !vis[i][j]) {
        return false;
      }
    }
  }

  int side = b[x][y];
  for (int i = x; i < x + side; ++i) {
    for (int j = y; j < y + side; ++j) {
      ++vis[i][j];
    }
  }
  if (Dfs(dep + 1, cur + 1, limit)) {
    return true;
  }

  for (int i = x; i < x + side; ++i) {
    for (int j = y; j < y + side; ++j) {
      --vis[i][j];
    }
  }
  return Dfs(dep + 1, cur, limit);
}

int IdaStar() {
  for (int limit = GaoH();; ++limit) {
    if (Dfs(0, 0, limit)) {
      return limit;
    }
  }
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  while (scanf("%d%d", &n, &m) != EOF && n) {
    memset(vis, 0, sizeof(vis));
    memset(b, 0, sizeof(b));
    memset(must, 0, sizeof(must));
    tot = 0;
    mm = 1;
    int ans = 0;

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        scanf("%d", &a[i][j]);
        b[i][j] = a[i][j];
        c[i][j].clear();
      }
    }

    for (int i = m - 2; i >= 0; --i) {
      for (int j = n - 2; j >= 0; --j) {
        if (a[i][j]) {
          b[i][j] += min(b[i + 1][j + 1], min(b[i][j + 1], b[i + 1][j]));
        }
      }
    }

    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        int side = b[x][y];
        mm = max(mm, side);
        for (int i = x; i < x + side; ++i) {
          for (int j = y; j < y + side; ++j) {
            if (i == x && j == y) continue;
            if (i + b[i][j] <= x + side && j + b[i][j] <= y + side) {
              b[i][j] = 0;
            }
          }
        }
      }
    }

    mm = mm * mm;

    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        int side = b[x][y];
        for (int i = x; i < x + side; ++i) {
          for (int j = y; j < y + side; ++j) {
            c[i][j].push_back(make_pair(x, y));
          }
        }
      }
    }

    for (int i = 0; i < m; ++i) {
      for (int j = 0; j < n; ++j) {
        if (a[i][j] && c[i][j].size() == 1) {
          int x = c[i][j][0].first, y = c[i][j][0].second;
          must[x][y] = 1;
        }
      }
    }

    for (int x = 0; x < m; ++x) {
      for (int y = 0; y < n; ++y) {
        int side = b[x][y];
        if (side) {
          if (must[x][y]) {
            ++ans;
            for (int i = x; i < x + side; ++i) {
              for (int j = y; j < y + side; ++j) {
                ++vis[i][j];
              }
            }
          } else {
            p[tot++] = make_pair(x, y);
          }
        }
      }
    }

    ans += IdaStar();
    printf("%d\n", ans);
  }
  return 0;
}
