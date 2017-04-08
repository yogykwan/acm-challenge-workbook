/*
 * POJ 3688: Cheat in the Game
 * 题意：一堆石头有若干个，一叠数字牌。两人轮流抽牌，按照牌上的数取石头，不够则重抽。牌全部抽完还未决出胜负则游戏重新开始。求初始石头的数量为多少时，能保证先手若干局后一定能赢。
 * 类型：博弈DP
 * 算法：d[0/1][w]表示已经玩了奇数／偶数轮后，总共能取走w个石头的情况是否能发生。最后枚举所有奇数张存在，偶数张不存在的w。
 */

#include <cstdio>
#include <algorithm>

using namespace std;

int a[10];

int main() {
  int n;
  while (scanf("%d", &n) != EOF && n) {
    bool ans = 1;
    for (int i = 0; i < n; ++i) scanf("%d", &a[i]);
    if (n % 2 == 0) {
      sort(a, a + n);
      int i;
      for (i = 0; i < n; i += 2) {
        if (a[i] != a[i + 1]) break;
      }
      if (i == n) ans = 0;
    }
    printf("%d\n", ans);
  }
  return 0;
}
