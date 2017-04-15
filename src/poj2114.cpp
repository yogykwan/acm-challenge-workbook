/*
 * POJ 2114: Boatherds
 * 题意：给出一棵树及每边边权，求是否存在距离为k的两点。
 * 类型：树分治
 * 算法：树形dp得到每个子树的大小，按照最大子树最小的原则同时得到重心。得到每个点到重心的距离，排序后两点法求得是否存在跨重心路径为目标长度。若无则递归求解每棵子树。
 */


#include <algorithm>
#include <cstring>
#include <vector>
#include <map>
#include <set>
#include <cstdio>

using namespace std;

typedef pair<int, int> pii;

vector<pii> e[10010];

int path[110];
bool ans[110];
bool center[10010];
bool all;

int n, m;

vector<int> len;
map<int, set<int> > ms;

int cnt[10010];

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

void GetLen(int u, int p, int cur, int rt) {
  len.push_back(cur);
  if (ms.find(cur) == ms.end()) {
    ms[cur] = set<int>();
  }
  ms[cur].insert(rt);

  for (vector<pii>::iterator it = e[u].begin(); it != e[u].end(); ++it) {
    int v = it->first;
    if (v == p || center[v]) continue;
    int w = it->second;
    GetLen(v, u, cur + w, rt);
  }
}

void Gao(int u) {
  if (all) return;
  int p = 0;

  int nt = CalSub(u, p);
  int c = u, large = n + 1;

  GetCenter(u, p, nt, c, large);
  center[c] = true;

  len.clear();
  ms.clear();
  for (vector<pii>::iterator it = e[c].begin(); it != e[c].end(); ++it) {
    int v = it->first;
    if (center[v]) continue;
    int w = it->second;
    GetLen(v, c, w, v);
  }
  sort(len.begin(), len.end());
  vector<int>::iterator end_unique = unique(len.begin(), len.end());
  len.erase(end_unique, len.end());
  int nl = len.size();

  for (int i = 0; i < m; ++i) {
    if (ans[i]) continue;
    if (find(len.begin(), len.end(), path[i]) != len.end()) {
      ans[i] = true;
      continue;
    }
    if (path[i] % 2 == 0 && find(len.begin(), len.end(), path[i] >> 1) != len.end() && ms[path[i] >> 1].size() > 1) {
      ans[i] = true;
      continue;
    }
    int p1, p2;
    p1 = 0;
    p2 = nl - 1;
    while (p1 < p2) {
      if (len[p1] + len[p2] == path[i]) {
        if (ms[len[p1]].size() > 1 || ms[len[p2]].size() > 1 || *ms[len[p1]].begin() != *ms[len[p2]].begin()) {
          ans[i] = true;
          break;
        } else {
          ++p1;
          --p2;
        }
      } else if (len[p1] + len[p2] < path[i]) {
        ++p1;
      } else {
        --p2;
      }
    }
  }

  int sum = 0;
  for (int i = 0; i < m; ++i) {
    sum += ans[i];
  }
  if (sum == m) {
    all = true;
    return;
  }

  for (vector<pii>::iterator it = e[c].begin(); it != e[c].end(); ++it) {
    int v = it->first;
    if (center[v]) continue;
    Gao(v);
  }
}

int main() {
//  freopen("/Users/yogy/acm-challenge-workbook/db.in", "r", stdin);
  while (scanf("%d", &n) != EOF && n) {
    for (int i = 1; i <= n; ++i) e[i].clear();
    for (int i = 1; i <= n; ++i) {
      int d, c;
      while (1) {
        scanf("%d", &d);
        if (!d) break;
        scanf("%d", &c);
        e[i].push_back(make_pair(d, c));
        e[d].push_back(make_pair(i, c));
      }
    }
    m = 0;
    while (1) {
      int q;
      scanf("%d", &q);
      if (!q) break;
      path[m++] = q;
    }
    memset(center, 0, sizeof(center));
    all = false;
    memset(ans, 0, sizeof(ans));
    Gao(1);
    for (int i = 0; i < m; ++i) {
      printf("%s\n", ans[i] ? "AYE" : "NAY");
    }
    printf(".\n");
  }

  return 0;
}
