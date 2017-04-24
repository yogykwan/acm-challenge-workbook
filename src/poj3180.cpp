/*
 * POJ 3180: The Cow Prom
 * 题意：n头牛顺时针围成圈，某些牛间用绳子沿圈顺时针相连。若一组牛的某一头顺时针或逆时针跳舞，其他某些牛都能顺时针或逆时针移动，则这一组是成功的。问有多少组成功组。
 * 类型：强连通分量
 * 算法：强连通分量中的点意味着可以顺逆同时移动，点数大于1的scc即为答案。
 */

#include <cstdio>
#include <cstring>
#include <vector>

using namespace std;

vector<int> e[10010];
vector<int> re[10010];
vector<int> id;
bool vis[10010];

int tot;
int cnt[10010];


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
  ++cnt[tot];
  for (vector<int>::iterator it = re[i].begin(); it != re[i].end(); ++it) {
    if (!vis[*it]) {
      RDfs(*it);
    }
  }
}

int main() {
  int n, m;
  scanf("%d%d", &n, &m);
  while (m--) {
    int i, j;
    scanf("%d%d", &i, &j);
    e[i].push_back(j);
    re[j].push_back(i);
  }

  memset(vis, 0, sizeof(vis));
  for (int i = 1; i <= n; ++i) {
    if (!vis[i]) Dfs(i);
  }

  memset(vis, 0, sizeof(vis));
  for (vector<int>::iterator it = id.end() - 1; it >= id.begin(); --it) {
    if (!vis[*it]) {
      RDfs(*it);
      ++tot;
    }
  }

  int ans = 0;
  for (int i = 0; i < tot; ++i) {
    if (cnt[i] > 1) {
      ++ans;
    }
  }
  printf("%d\n", ans);

  return 0;
}
