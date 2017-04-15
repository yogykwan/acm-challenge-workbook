/*
 * UVa 12161: Ironman Race in Treeland
 * 题意：给出一棵树及每边花费，求总花费不超过k的最长路。
 * 类型：树分治
 * 算法：树形dp得到每个子树的大小，按照最大子树最小的原则同时得到重心，得到每个点到重心的距离和花费。map中保存每个花费的最长路并删除花费大距离不更长的路，合并满足总花费的路并更新最大长度。
 */


#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <cstdio>

using namespace std;

typedef pair<int, int> pii;

vector<pii> e[30010];
bool center[30010];

int n, m;
int ans;

map<int, int> pre;
vector<pii> cur;

int cnt[30010];

int CalSub(int u, int p) {
  int ans = 1;
  for (vector<pii>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = it->first;
    if (v == p || center[v]) continue;
    ans += CalSub(v, u);
  }
  return cnt[u] = ans;
}

void GetCenter(int u, int p, int nt, int &c, int &large) {
  int ans = 0, sum = 0;
  for (vector<pii>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = it->first;
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

void GetLen(int u, int p, int cost, int step) {
  if (cost > m) return;
  cur.push_back(make_pair(cost, step));
  ans = max(ans, step);
  for (vector<pii>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = it->first;
    if (v == p || center[v]) continue;
    GetLen(v, u, cost + it->second, step + 1);
  }
}

void Gao(int u) {
  int p = 0;

  int nt = CalSub(u, p);
  int c = u, large = n + 1;

  GetCenter(u, p, nt, c, large);
  center[c] = true;


  pre.clear();
  for (vector<pii>::iterator it = e[c].begin(); it != e[c].end(); ++it) {
    cur.clear();
    int v = it->first;
    if (center[v]) continue;
    GetLen(v, c, it->second, 1);

    for (vector<pii>::iterator it = cur.begin(); it != cur.end(); ++it) {
      map<int, int>::iterator mit = pre.upper_bound(m - it->first);
      if (mit != pre.begin()) {
        ans = max(ans, (--mit)->second + it->second);
      }
    }

    for (vector<pii>::iterator it = cur.begin(); it != cur.end(); ++it) {
      if (pre.find(it->first) == pre.end() || pre[it->first] < it->second) {
        pre[it->first] = it->second;
      }
      map<int, int>::iterator mit = pre.upper_bound(m - it->first);
      while (mit != pre.end() && it->second >= mit->second) {
        pre.erase(mit++);
      }
    }
  }

  for (vector<pii>::iterator it = e[c].begin(); it != e[c].end(); ++it) {
    int v = it->first;
    if (center[v]) continue;
    Gao(v);
  }
}

int main() {
  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  int T;
  scanf("%d", &T);
  for (int tc = 1; tc <= T; ++tc) {
    scanf("%d%d", &n, &m);
    for (int i = 1; i <= 30000; ++i) {
      e[i].clear();
    }
    for (int i = 0; i < n; ++i) {
      int u, v, c;
      scanf("%d%d%d", &u, &v, &c);
      e[u].push_back(make_pair(v, c));
      e[v].push_back(make_pair(u, c));
    }
    ans = 0;

    memset(center, 0, sizeof(center));
    Gao(1);
    printf("Case %d: %d\n", tc, ans);
  }

  return 0;
}
