/*
 * POJ 1740: A New Stone Game
 * 题意：n堆石头，两人轮流选取一堆，先扔掉至少1个，再将剩下的选取任意个或不选，转移到任意其他一个或多个堆。问先手胜负。
 * 类型：NP博弈
 * 算法：若包含相同石头数的堆都为偶数堆，则该状态为必败态。因为此时游戏必然破坏该必败条件，但下一轮一定可以通过从对称的堆里进行相同的操作使必败条件满足。
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
