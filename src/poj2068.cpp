/*
 * POJ 3688: Cheat in the Game
 * 题意：m堆石头，2n个人轮流取，每个人单次取的上限。求先手胜负。
 * 类型：博弈DP
 * 算法：d[i][w]表示轮到第i个人还剩w个石头，它可由d[(i+1)%2n][w-k]转移得到，k为1到ai。记忆化dp，解为d[0][m]。
 */

#include <cstdio>
#include <cstring>

using namespace std;

int d[1 << 13][20];
int m[20];
int n;

int dp(int s, int u) {
  if (d[s][u] != -1) return d[s][u];
  if (s == 1) return d[s][u] = 0;
  int v = (u + 1) % n;
  for (int i = 1; i <= m[u] && i < s; ++i) {
    if (dp(s - i, v) == 0) {
      return d[s][u] = 1;
    }
  }
  return d[s][u] = 0;
}

int main() {
  int s;
  while(scanf("%d", &n) != EOF && n) {
    n <<= 1;
    memset(d, -1, sizeof(d));
    scanf("%d", &s);
    for (int i = 0; i < n; ++i) scanf("%d", &m[i]);
    printf("%d\n", dp(s, 0));
  }
  return 0;
}