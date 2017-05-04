/*
 * POJ 2226: Muddy Fields
 * 题意：给出一个矩阵，每个点是.或*。现在有一些宽为1长任意的木条，要用木条覆盖所有的*，但是保留所有的.。求最少使用的木条数量。
 * 类型：二分匹配
 * 算法：分为横竖考虑，将连续的*区域用一个木条表示，并编号。每个*都是一个横和一个竖交点。将横竖木条分列二分图两侧作为点，每个*作为边。则最小顶点覆盖数即为所求，二分图中其值等于最大匹配。
 */

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

vector<int> e[1300];
bool vis[1300];
int rec[1300];
int n1, n2;

bool Dfs(int u) {
  for (vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = *it;
    if (!vis[v]) {
      vis[v] = true;
      if (rec[v] == -1 || Dfs(rec[v])) {
        rec[v] = u;
        return true;
      }
    }
  }
  return false;
}

int Hungary() {
  int ans = 0;
  memset(rec, -1, sizeof(rec));
  for (int i = 0; i < n1; ++i) {
    memset(vis, 0, sizeof(vis));
    if (Dfs(i)) ++ans;
  }
  return ans;
}

struct Line {
  Line() {}

  Line(int _x1, int _x2, int _y) : x1(_x1), x2(_x2), y(_y) {}

  int x1, x2, y;
} heng[1300], shu[1300];

char mat[55][55];

int main() {
  int r, c;
  scanf("%d%d", &r, &c);
  for (int i = 0; i < r; ++i) {
    scanf("%s", mat[i]);
  }

  n1 = n2 = 0;
  for (int i = 0; i < r; ++i) {
    int x1 = -1;
    for (int j = 0; j < c; ++j) {
      if (mat[i][j] == '.') {
        if (x1 != -1) {
          heng[n1++] = Line(x1, j - 1, i);
          x1 = -1;
        }
      } else {
        if (x1 == -1) {
          x1 = j;
        }
      }
    }
    if (x1 != -1) {
      heng[n1++] = Line(x1, c - 1, i);
    }
  }
  for (int i = 0; i < c; ++i) {
    int x1 = -1;
    for (int j = 0; j < r; ++j) {
      if (mat[j][i] == '.') {
        if (x1 != -1) {
          shu[n2++] = Line(x1, j - 1, i);
          x1 = -1;
        }
      } else {
        if (x1 == -1) {
          x1 = j;
        }
      }
    }
    if (x1 != -1) {
      shu[n2++] = Line(x1, r - 1, i);
    }
  }

  for (int i = 0; i < n1; ++i) {
    for (int j = 0; j  < n2; ++j) {
      if (heng[i].y >= shu[j].x1 && heng[i].y <= shu[j].x2 && shu[j].y >= heng[i].x1 && shu[j].y <= heng[i].x2) {
        e[i].push_back(j);
      }
    }
  }

  printf("%d\n", Hungary());

  return 0;
}
