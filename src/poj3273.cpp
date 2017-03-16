/*
 * POJ 3273: Monthly Expense
 * 题意：给出n天的花费，将它们划分到m个月里，求最大月花费可能的最小值。
 * 类型：二分搜索+贪心
 * 算法：二分搜索，最小化月费最大值。为保证每月都不大于最大花费且划分月数最少，遍历时贪心合并尽量多的日子进月。若求得的划分月小于m则更新上届，否则更新下届。
 */

#include <cstdio>
#include <algorithm>
#include <iostream>

using namespace std;

int a[100010];

int main() {
  int m, n;
  int mv, lv, rv;
  lv = 0;
  rv = 0;
  scanf("%d%d", &n, &m);
  for (int i = 0; i < n; ++i) {
    scanf("%d", &a[i]);
    rv += a[i];
    lv = max(lv, a[i]);
  }
  --lv;
  while (lv + 1 < rv) {
    mv = (lv + rv) >> 1;
    int cnt = 0;
    for (int i = 0; i < n; ++i) {
      int tmp = a[i];
      while (i + 1 < n && tmp + a[i + 1] <= mv) {
        tmp += a[++i];
      }
      ++cnt;
    }
    if (cnt <= m) {
      rv = mv;
    } else {
      lv = mv;
    }
  }
  printf("%d\n", rv);
  return 0;
}