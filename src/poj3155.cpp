/*
 * POJ 3155: Hard Life
 * 题意：给出一个无向图，子图密度定义为子图内的点之间的边数，除以点的个数。求密度最大的子图。
 * 类型：二分+最小割
 * 算法：假设密度为g，建图时构造源点s汇点t，s到u容量为输入总边数m，u到t容量为m+2g-d[u]，d为点的度数。原无向边变为容量为1的2条有向边。二分出最大密度密度，每次建图求最小割，根据(m*n-min_cut)/2是否大于0更新上下边界。
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

const double INF = 0x3f3f3f3f;
const double EPS = 1e-8;

struct E {
  E() {}

  E(int _v, double _c, int _r) : v(_v), c(_c), r(_r) {}

  int v, r;
  double c;
};

vector<E> e[110];

void AddEdge(int u, int v, double c) {
  e[u].push_back(E(v, c, e[v].size()));
  e[v].push_back(E(u, 0, e[u].size() - 1));
}

int level[110], iter[110];

queue<int> q;

void Bfs(int s) {
  memset(level, -1, sizeof(level));
  while (!q.empty()) q.pop();
  level[s] = 0;
  q.push(s);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (int i = 0; i < e[u].size(); ++i) {
      int v = e[u][i].v;
      if (e[u][i].c > 0 && level[v] < 0) {
        level[v] = level[u] + 1;
        q.push(v);
      }
    }
  }
}

double Dfs(int u, int t, double f) {
  if (u == t) {
    return f;
  }
  for (int &i = iter[u]; i < e[u].size(); ++i) {
    int v = e[u][i].v;
    if (e[u][i].c > 0 && level[v] > level[u]) {
      double d = Dfs(v, t, min(f, e[u][i].c));
      if (d > 0) {
        e[u][i].c -= d;
        e[v][e[u][i].r].c += d;
        return d;
      }
    }
  }
  return 0;
}

double Dinic(int s, int t) {
  double ans = 0;
  while (1) {
    Bfs(s);
    if (level[t] < 0) break;
    memset(iter, 0, sizeof(iter));
    double f;
    while ((f = Dfs(s, t, INF)) > 0) {
      ans += f;
    }
  }
  return ans;
}

bool vis[110];
int cnt;

void GaoCnt(int u) {
  ++cnt;
  vis[u] = 1;
  for (int i = 0; i < e[u].size(); ++i) {
    int v = e[u][i].v;
    if (e[u][i].c > 0 && !vis[v]) {
      GaoCnt(v);
    }
  }
}

int a[1010], b[1010], d[110];
int n, m;

void BuildGraph(double g, int s, int t) {
  for (int i = 0; i <= n + 1; ++i) e[i].clear();
  for (int i = 0; i < m; ++i) {
    AddEdge(a[i], b[i], 1);
    AddEdge(b[i], a[i], 1);
  }
  for (int i = 1; i <= n; ++i) {
    AddEdge(s, i, m);
    AddEdge(i, t, 2 * g - d[i] + m);
  }
}

int main() {
  scanf("%d%d", &n, &m);
  int s = 0, t = n + 1;
  for (int i = 0; i < m; ++i) {
    scanf("%d%d", &a[i], &b[i]);
    ++d[a[i]];
    ++d[b[i]];
  }
  if (m == 0) {
    printf("1\n1\n");
    return 0;
  }

  double l, r, mm, pre;
  l = 0;
  r = m;
  pre = 1.0 / n / n;
  while (r - l >= pre) {
    mm = (l + r) / 2;
    BuildGraph(mm, s, t);
    double hg = (m * n - Dinic(s, t)) / 2;
    (hg > EPS ? l : r) = mm;
  }
  BuildGraph(l, s, t);
  Dinic(s, t);
  GaoCnt(s);
  printf("%d\n", --cnt);
  for (int i = 1; i <= n; ++i) {
    if (vis[i]) printf("%d\n", i);
  }
  return 0;
}
