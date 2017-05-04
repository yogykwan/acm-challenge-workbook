/*
 * POJ 2724: Purifying Machine
 * 题意：奶酪用二进制编号，有一台二进制机器可通过二进制数或带有一位*的正则匹配1块或2块奶酪。先给出一些机器操作序列污染了一批奶酪，求现在要不影响未污染的奶酪并且把所有被污染的奶酪净化需要的最少操作数。
 * 类型：二分匹配
 * 算法：二进制只有一位不同的数可建边，边表示带*的操作。由于建边的两个数二进制中1的个数必为一奇一偶，所以图为二分图。匈牙利算法求得最大二分匹配，被污染的奶酪数减去最大匹配即为答案。
 */

#include <cstdio>
#include <cstring>

using namespace std;

bool odd[1030];
bool infect[1030];
bool vis[1030];
int rec[1030];
int n, m;

bool Dfs(int u) {
  for (int i = 0; i < n; ++i) {
    int v = u ^(1 << i);
    if (infect[v] && !vis[v]) {
      vis[v] = 1;
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
  for (int i = (1 << n) - 1; i >= 0; --i) {
    if (infect[i] && odd[i]) {
      memset(vis, 0, sizeof(vis));
      if (Dfs(i)) ++ans;
    }
  }
  return ans;
}

int main() {
  for (int i = 0; i < 1024; ++i) {
    int j = i, cnt = 0;
    while (j) {
      if (j & 1) ++cnt;
      j >>= 1;
    }
    if (cnt & 1) odd[i] = 1;
  }
  while (scanf("%d%d", &n, &m) != EOF && n) {
    memset(infect, 0, sizeof(infect));
    for (int i = 0; i < m; ++i) {
      char op[12];
      scanf("%s", op);
      int s = -1, t = 0;
      for (int j = 0; j < n; ++j) {
        t <<= 1;
        if (op[j] == '1') {
          t |= 1;
        } else if (op[j] == '*') {
          s = j;
        }
      }
      infect[t] = 1;
      if (s != -1) {
        infect[1 << (n - 1 - s) | t] = 1;
      }
    }
    int ans = 0;
    for (int i = (1 << n) - 1; i >= 0; --i) {
      if (infect[i]) ++ans;
    }
    ans -= Hungary();
    printf("%d\n", ans);
  }
  return 0;
}