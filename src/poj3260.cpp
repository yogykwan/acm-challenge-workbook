/*
 * POJ 3260: The Fewest Coins
 * 题意：n种面值的货币，给出一个人拥有的货币情况。给出物体总价，购买可以通过付款和找零实现，求交易中被流通货币数最小的方案。
 * 类型：数论+背包DP+二进制
 * 算法：找回的钱不会超过maxv*maxv，否则付钱的部分序列和等于找回的部分序列和，导致矛盾。付钱是多重背包（每种货币的数量转为二进制降低复杂度），还钱是完全背包，用相减为总价的个数和更新答案。
 */

#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

const int INF = 0x3f3f3f3f;

int dc[122 * 122];
int dp[100010 + 122 * 122];
int v[110], c[110];
int n, m;
int mv;

void multiple_pack() {
  memset(dp, 0x3f, sizeof(dp));
  dp[0] = 0;
  int up = m + mv * mv;
  for (int i = 0; i < n; ++i) {
    int num = 0;
    int cnt;
    for (int k = 1; num < c[i]; k <<= 1) {
      if (num + k > c[i]) cnt = c[i] - num;
      else cnt = k;
      for (int j = up; j >= cnt * v[i]; --j) {
        dp[j] = min(dp[j], dp[j - cnt * v[i]] + cnt);
      }
      num += cnt;
    }
  }
}

void complete_pack() {
  memset(dc, 0x3f, sizeof(dc));
  dc[0] = 0;
  int up = mv * mv;
  for (int i = 0; i < n; ++i) {
    for (int j = v[i]; j <= up; ++j) {
      dc[j] = min(dc[j], dc[j - v[i]] + 1);
    }
  }
}

int main() {
  scanf("%d%d", &n, &m);
  mv = 0;
  for (int i = 0; i < n; ++i) {
    scanf("%d", &v[i]);
    mv = max(mv, v[i]);
  }
  for (int i = 0; i < n; ++i) {
    scanf("%d", &c[i]);
  }
  multiple_pack();
  complete_pack();
  int ans = INF;

  for (int i = mv * mv; i >= 0; --i) {
    ans = min(ans, dc[i] + dp[i + m]);
  }
  if (ans >= INF) printf("-1\n");
  else printf("%d\n", ans);
  return 0;
}


