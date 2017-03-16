/*
 * POJ 3258: River Hopscotch
 * 题意：原本n个石头排成一排，最多可以撤掉中间m个石头，通过石头间跳跃从起点到达终点。求单次跳跃距离最小值的最大值。
 * 类型：二分搜索+贪心
 * 算法：二分搜索，最大化距离最小值。为保证单词距离不小于最小距离且撤去石子最少，贪心将小于该距离的边与后面的边合并。最后通过撤去石头的数量判断该值是否是合法上界。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int a[50010];

int main() {
  int t, m, n;
  scanf("%d%d%d", &t, &n, &m);
  for (int i = 1; i <= n; ++i) {
    scanf("%d", &a[i]);
  }
  a[n + 1] = t;
  sort(a, a + n +1);
  int rv, lv, mv;
  lv = rv = t;
  for (int i = 0; i <= n; ++i) {
    a[i] = a[i + 1] - a[i];
    lv = a[i] < lv ? a[i] : lv;
  }

  while (lv + 1 < rv) {
    mv = (lv + rv) >> 1;
    int cnt = 0;
    for(int i = 0; i <=n; ++i) {
      int len = a[i];
      while(len < mv && i < n) {
        ++cnt;
        len += a[++i];
      }
      if(len < mv) ++cnt;
    }
    if (cnt > m) {
      rv = mv;
    } else {
      lv = mv;
    }
  }
  printf("%d\n", lv);

  return 0;
}