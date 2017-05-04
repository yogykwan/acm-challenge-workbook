/*
 * POJ 2987: Firing
 * 题意：给出一个有向图，选择一个点，则要选择它的可以到达的所有节点。选择每个点有各自的利益或损失。求最大化的利益，以及此时选择人数的最小值。
 * 类型：最小割
 * 算法：构造源点s汇点t。从s到每个正数点建边，容量为利益。每个负点到t建边，容量为损失的绝对值。其他关系边容量正向无穷，反向0。正数点总和减去最小割即为最大权闭合图答案。因为残余网络不会对0流边处理，所以不会将0流点选入取点集，所以最小割的取法中为被选中的点。
 */

#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>

using namespace std;

typedef long long LL;

const LL INF = 0x3f3f3f3f3f3f3f3fll;

struct E {
  E() {}
  E(int _v, LL _c, int _r): v(_v), c(_c), r(_r) {}
  int v, r;
  LL c;
};

vector<E> e[5010];

void AddEdge(int u, int v, LL c) {
  e[u].push_back(E(v, c, e[v].size()));
  e[v].push_back(E(u, 0, e[u].size() - 1));
}

int level[5010], iter[5010];


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

LL Dfs(int u, int t, LL f) {
  if (u == t) {
    return f;
  }
  for (int &i = iter[u]; i < e[u].size(); ++i) {
    int v = e[u][i].v;
    if (e[u][i].c > 0 && level[v] > level[u]) {
      LL d = Dfs(v, t, min(f, e[u][i].c));
      if (d > 0) {
        e[u][i].c -= d;
        e[v][e[u][i].r].c += d;
        return d;
      }
    }
  }
  return 0;
}

LL Dinic(int s, int t) {
  LL ans = 0;
  while (1) {
    Bfs(s);
    if (level[t] < 0) break;
    memset(iter, 0, sizeof(iter));
    LL f;
    while ((f = Dfs(s, t, INF)) > 0) {
      ans += f;
    }
  }
  return ans;
}

bool vis[5010];
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

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  int s = 0, t = n + 1;
  LL ans = 0;
  for (int i = 1; i <= n; ++i) {
    LL c;
    scanf("%lld", &c);
    if (c > 0) {
      ans += c;
      AddEdge(s, i, c);
    } else if (c < 0) {
      AddEdge(i, t, -c);
    }
  }
  for (int i = 0; i < m; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    AddEdge(u, v, INF);
  }
  ans -= Dinic(s, t);
  GaoCnt(s);
  printf("%d %lld\n", cnt - 1, ans);
  return 0;
}
