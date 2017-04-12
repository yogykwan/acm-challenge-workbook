/*
 * POJ 3537: Crosses and Crosses
 * 题意：一排格子，两人轮流划x，直到出现大于等于连续3个x则胜出。问先手的胜负。
 * 类型：Grundy博弈
 * 算法：枚举某个格子去画x，这时以该点为中心的5个格子都为不可用态（画则必败），所以游戏转变为被这5个点隔开的左右两段长度的2个子游戏。求他们seg的异或，再更新本状态的seg值。
 */

#include <cstdio>
#include <cstring>
using namespace std;

int sg[2010];

int dp(int x) {
  if (x <= 0) return 0;
  if (sg[x] >= 0) return sg[x];
  bool vis[2010] = {0};
  for (int i = 0; i < x; ++i) {
    vis[dp(i - 2) ^ dp(x - i - 3)] = 1;
  }
  int i = 0;
  while (vis[i]) ++i;
  return sg[x] = i;
}

int main() {
  memset(sg, -1, sizeof(sg));
  int n;
  while (scanf("%d", &n) != EOF) {
    if (dp(n)) printf("1\n");
    else printf("2\n");
  }
  return 0;
}