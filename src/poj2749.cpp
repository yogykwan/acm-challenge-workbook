/*
 * POJ 2749: Building roads
 * 题意：n头牛在各自牛棚里，建两个中心结点st，让某些牛连接s，某些连接t。某些牛必须连接相同的中心，某些牛必须连接不同的中心。最终使得牛与牛之间最远距离最近的方案中，该最远距离是多少。
 * 类型：2-SAT+二分
 * 算法：二分最远距离，将讨厌和喜欢关系按异或建边。然后牛与牛之间两两枚举，st、ts、ss、tt四种情况是否可行，不可行则建对立边。求解2-SAT更新二分上届。
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;

vector<int> e[1010];
vector<int> re[1010];
vector<int> id;
bool vis[1010];

int tot;
int tp[1010];

int d[505][2];
int d1[2], d2[2];
int st;
int sx[2], sy[2];
int x[505], y[505];

int hate[1010][2];
int like[1010][2];

void Dfs(int i) {
  vis[i] = 1;
  for (vector<int>::iterator it = e[i].begin(); it != e[i].end(); ++it) {
    if (!vis[*it]) {
      Dfs(*it);
    }
  }
  id.push_back(i);
}

void RDfs(int i) {
  vis[i] = 1;
  tp[i] = tot;
  for (vector<int>::iterator it = re[i].begin(); it != re[i].end(); ++it) {
    if (!vis[*it]) {
      RDfs(*it);
    }
  }
}

bool Scc(int n) {
  id.clear();
  memset(vis, 0, sizeof(vis));
  for (int i = 0; i < n << 1; ++i) {
    if (!vis[i]) Dfs(i);
  }

  tot = 0;
  memset(vis, 0, sizeof(vis));
  for (vector<int>::iterator it = id.end() - 1; it >= id.begin(); --it) {
    if (!vis[*it]) {
      RDfs(*it);
      ++tot;
    }
  }

  bool ok = true;
  for (int i = 0; i < n; ++i) {
    if (tp[i] == tp[i + n]) {
      ok = false;
      break;
    }
  }
  return ok;
}

void AddEdge(int i, int j) {
  e[i].push_back(j);
  re[j].push_back(i);
}


bool Gao(int bound, int n, int a, int b) {
  for (int i = (n << 1) - 1; i >= 0; --i) {
    e[i].clear();
    re[i].clear();
  }
  for (int i = 0; i < a; ++i) {
    AddEdge(hate[i][0], hate[i][1] + n);
    AddEdge(hate[i][0] + n, hate[i][1]);
    AddEdge(hate[i][1], hate[i][0] + n);
    AddEdge(hate[i][1] + n, hate[i][0]);
  }
  for (int i = 0; i < b; ++i) {
    AddEdge(like[i][0], like[i][1]);
    AddEdge(like[i][0] + n, like[i][1] + n);
    AddEdge(like[i][1], like[i][0]);
    AddEdge(like[i][1] + n, like[i][0] + n);
  }

  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < n; ++j) {
      if (i == j) continue;
      if (d[i][0] + d[j][0] > bound) {
        AddEdge(i, j + n);
      }
      if (d[i][0] + d[j][1] + st > bound) {
        AddEdge(i, j);
      }
      if (d[i][1] + d[j][1] > bound) {
        AddEdge(i + n, j);
      }
      if (d[i][1] + d[j][0] + st > bound) {
        AddEdge(i + n, j + n);
      }
    }
  }
  return Scc(n);
}

int ABS(int x) {
  return x < 0 ? -x : x;
}

int Manhattan(int x1, int y1, int x2, int y2) {
  return ABS(x1 - x2) + ABS(y1 - y2);
}

int main() {
  int n, a, b;
  scanf("%d%d%d", &n, &a, &b);
  scanf("%d%d%d%d", &sx[0], &sy[0], &sx[1], &sy[1]);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &x[i], &y[i]);
  }
  for (int i = 0; i < a; ++i) {
    scanf("%d%d", &hate[i][0], &hate[i][1]);
    --hate[i][0];
    --hate[i][1];
  }
  for (int i = 0; i < b; ++i) {
    scanf("%d%d", &like[i][0], &like[i][1]);
    --like[i][0];
    --like[i][1];
  }

  st = Manhattan(sx[0], sy[0], sx[1], sy[1]);
  for (int i = 0; i < n; ++i) {
    for (int j = 0; j < 2; ++j) {
      d[i][j] = Manhattan(x[i], y[i], sx[j], sy[j]);
      if (d[i][j] >= d1[j]) {
        d2[j] = d1[j];
        d1[j] = d[i][j];
      } else if (d[i][j] > d2[j]){
        d2[j] = d[i][j];
      }
    }
  }

  int l, r, m;
  l = 0;
  r = max(max(d1[0] + d2[0], d1[1] + d2[1]), d1[0] + d1[1] + st);
  if (!Gao(r, n, a, b)) {
    printf("-1\n");
    return 0;
  }
  while (l + 1 < r) {
    m = (l + r) >> 1;
    if(Gao(m, n, a, b)) {
      r = m;
    } else {
      l = m;
    }
  }
  printf("%d\n", r);
  return 0;
}
