/*
 * POJ 3045: Cow Acrobats
 * 题意：每头牛有体重和承重，让牛叠成一纵，每头牛的危险系数是其上总重量减自身承重。求最优的叠法使所有牛中最大的危险系数最小。
 * 类型：贪心+快排
 * 算法：只讨论中间两个，若i在j上优于j在i上，则max(-si,wi-sj)<max(-sj,wj-si)，根据上式编写快排重载关系函数即可。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

struct Cow {
  int s, w;

  bool operator<(const Cow &c) const {
    return max(-s, w - c.s) < max(-c.s, c.w - s);
  }
} cows[50010];

int main() {
  int n;
  scanf("%d", &n);
  for (int i = 0; i < n; ++i) {
    scanf("%d%d", &cows[i].w, &cows[i].s);
  }
  sort(cows, cows + n);

  int ans = -cows[0].s;
  int up = cows[0].w;
  for (int i = 1; i < n; ++i) {
    ans = max(ans, up - cows[i].s);
    up += cows[i].w;
  }
  printf("%d\n", ans);
  return 0;
}