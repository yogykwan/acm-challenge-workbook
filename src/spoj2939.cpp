/*
 * SPOJ 2939: Query on a tree V
 * 题意：给出一棵树，初始每个点都为黑色。给出两种操作，将某点颜色反转，或者询问某个点与离它最近的白点的距离。
 * 类型：树分治+LCA
 * 算法：预处理出所有的重心。为方便白转黑，对每个子树根用最小堆维护子树内白点到根的距离。查询离某结点的最近白点，遍历结点所在子树，用LCA求该点到子树根的距离，再加上堆内维护的子树的最近白点距离。
 */


#include <algorithm>
#include <cstring>
#include <vector>
#include <cstdio>
#include <queue>

using namespace std;

const int INF = 0x3f3f3f3f;

typedef pair<int, int> pii;

vector<int> e[100010];
bool center[100010];
int pa[100010];

priority_queue<pii, vector<pii>, greater<pii> > ws[100010];

int n, m;

int cnt[100010];

bool color[100010];

int CalSub(int u, int p) {
  int ans = 1;
  for (vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = *it;
    if (v == p || center[v]) continue;
    ans += CalSub(v, u);
  }
  return cnt[u] = ans;
}

void GetCenter(int u, int p, int nt, int &c, int &large) {
  int ans = 0, sum = 0;
  for (vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = *it;
    if (v == p || center[v]) continue;
    ans = max(ans, cnt[v]);
    sum += cnt[v];

    GetCenter(v, u, nt, c, large);
  }
  ans = max(nt - 1 - sum, ans);
  if (ans < large) {
    c = u;
    large = ans;
  }
}

void InitTree(int u, int p) {
  int nt = CalSub(u, p);
  int c = u, large = n + 1;

  GetCenter(u, p, nt, c, large);
  center[c] = true;
  pa[c] = p;

  for (vector<int>::iterator it = e[c].begin(); it != e[c].end(); ++it) {
    int v = *it;
    if (center[v]) continue;
    InitTree(v, c);
  }
}


int dep[100010];
int ans[100010][18];

void InitLsa(int u, int p, int step) {
  dep[u] = step;
  ans[u][0] = p;
  for (int k = 1; k < 18 && ans[u][k - 1]; ++k) {
    ans[u][k] = ans[ans[u][k - 1]][k - 1];
  }
  for (vector<int>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = *it;
    if (v == p) continue;
    InitLsa(v, u, step + 1);
  }
}

int GetLsa(int u, int v) {
  if (dep[u] > dep[v]) {
    int t = u;
    u = v;
    v = t;
  }
  for (int k = 0; k < 18 && dep[v] != dep[u]; ++k) {
    if (((dep[v] - dep[u]) >> k) & 1) {
      v = ans[v][k];
    }
  }
  if (u == v) return u;

  for (int k = 17; k >= 0; --k) {
    if (ans[u][k] != ans[v][k]) {
      u = ans[u][k];
      v = ans[v][k];
    }
  }
  return ans[u][0];
}

int GetDist(int u, int v) {
  int lca = GetLsa(u, v);
  return dep[u] + dep[v] - 2 * dep[lca];
}

int Query(int u) {
  int ans = INF;
  int p = u;
  while (u) {
    while (!ws[u].empty()) {
      if (!color[ws[u].top().second]) {
        ws[u].pop();
      } else {
        ans = min(ans, ws[u].top().first + GetDist(u, p));
        break;
      }
    }
    u = pa[u];
  }
  return ans;
}

void Update(int u) {
  int p = u;
  if (color[u]) {
    while (u) {
      ws[u].push(make_pair(GetDist(p, u), p));
      u = pa[u];
    }
  }
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  scanf("%d", &n);

  for (int i = 1; i < n; ++i) {
    int u, v;
    scanf("%d%d", &u, &v);
    e[u].push_back(v);
    e[v].push_back(u);
  }

  InitTree(1, 0);

  InitLsa(1, 0, 1);

  scanf("%d", &m);
  while (m--) {
    int op, u;
    scanf("%d%d", &op, &u);
    if (op == 0) {
      color[u] = !color[u];
      Update(u);
    } else {
      int ans = Query(u);
      if (ans == INF) ans = -1;
      printf("%d\n", ans);
    }
  }
  return 0;
}
